#include "Dispatcher.h"
#include "Haversine.h" // Used by findClosestUnit
#include "../utils/FileHandler.h"
#include <iostream>
#include <algorithm>
#include <limits>
//#include "include/nlohmann/json.hpp" 
#include "nlohmann/json.hpp"
// Global constant for starting incident IDs (for mock data creation)
static long NEXT_MOCK_INCIDENT_ID = 1001;

// --- Constructor ---
// Initializes the road graph by passing the path to the graph file.
Dispatcher::Dispatcher(const std::string& graph_path) : road_graph(graph_path) {
    // Check if the graph initialized successfully (optional print)
    std::cout << "Dispatcher initialized with graph data." << std::endl;
}

// --- fetchAvailableUnits Definition (Step 1) ---
// Simulates querying the database for available units.
std::vector<Unit> Dispatcher::fetchAvailableUnits() {
    std::vector<Unit> all_units = FileHandler::readAllUnits(UNITS_FILE);
    std::vector<Unit> available;
    
    // Filter units where status is 'available'
    for (const auto& unit : all_units) {
        if (unit.status == "available") {
            available.push_back(unit);
        }
    }
    return available;
}

// --- findClosestUnit Definition (Step 2) ---
// Implements the Nearest Neighbor Search using the Haversine Formula.
Unit Dispatcher::findClosestUnit(double incident_lat, double incident_lon, const std::vector<Unit>& available_units) {
    double minimum_distance = std::numeric_limits<double>::max();
    Unit closest_unit; // Default constructed unit will serve as NULL/sentinel

    for (const auto& unit : available_units) {
        // Calculate the distance using the Haversine formula
        double distance = Haversine::calculateDistance(
            unit.current_latitude, unit.current_longitude, 
            incident_lat, incident_lon
        );

        if (distance < minimum_distance) {
            minimum_distance = distance;
            closest_unit = unit;
        }
    }
    
    // Check if a unit was found
    if (closest_unit.id == 0) {
        throw std::runtime_error("No available units found for dispatch.");
    }

    return closest_unit;
}

// --- updateUnitStatus Definition ---
void Dispatcher::updateUnitStatus(long unit_id, const std::string& new_status) {
    std::vector<Unit> all_units = FileHandler::readAllUnits(UNITS_FILE);
    
    bool updated = false;
    for (auto& unit : all_units) {
        if (unit.id == unit_id) {
            unit.status = new_status;
            updated = true;
            break;
        }
    }
    
    if (updated) {
        FileHandler::saveUnits(all_units, UNITS_FILE);
    }
}

// --- executeDispatch Definition (Core Logic) ---
std::tuple<Unit, std::vector<std::pair<double, double>>> Dispatcher::executeDispatch(
    double incident_lat, 
    double incident_lon, 
    const std::string& details
) {
    // 1. Fetch Available Units
    std::vector<Unit> available_units = fetchAvailableUnits();
    
    // 2. Identify the Closest Unit (Nearest Neighbor Search)
    Unit closest_unit = findClosestUnit(incident_lat, incident_lon, available_units);

    // 3. Calculate the Optimal Route (Dijkstra's Algorithm via Graph)
    std::vector<std::pair<double, double>> route_path = road_graph.findShortestPath(
        closest_unit.current_latitude, closest_unit.current_longitude, 
        incident_lat, incident_lon
    );
    
    // 4. Persistence Update: Change Unit Status to 'dispatched'
    updateUnitStatus(closest_unit.id, "dispatched");
    
    // 5. Persistence Update: Save new incident as 'assigned'
    Incident new_incident(NEXT_MOCK_INCIDENT_ID++, incident_lat, incident_lon, details);
    new_incident.status = "assigned";
    new_incident.assigned_unit_id = closest_unit.id;
    FileHandler::saveNewIncident(new_incident, INCIDENTS_FILE);
    
    // 6. Return result
    return std::make_tuple(closest_unit, route_path);
}

// --- getFullStatusJson Definition (Polling API) ---
std::string Dispatcher::getFullStatusJson() {
    // This function formats ALL unit and incident data into a single JSON string
    
    // STUB for simplicity in output formatting:
    std::vector<Unit> units = FileHandler::readAllUnits(UNITS_FILE);
    std::vector<Incident> incidents = FileHandler::readAllIncidents(INCIDENTS_FILE);
    
    // Use nlohmann::json to build the output string
    nlohmann::json output;
    
    // Build Units JSON Array (STUB)
    nlohmann::json units_json = nlohmann::json::array();
    for (const auto& u : units) {
        units_json.push_back({
            {"id", u.id}, {"name", u.name}, {"type", u.type}, 
            {"current_latitude", u.current_latitude}, 
            {"current_longitude", u.current_longitude}, 
            {"status", u.status}
        });
    }
    output["units"] = units_json;

    // Build Incidents JSON Array (STUB)
    nlohmann::json incidents_json = nlohmann::json::array();
    for (const auto& i : incidents) {
        incidents_json.push_back({
            {"id", i.id}, {"latitude", i.latitude}, {"longitude", i.longitude}, 
            {"details", i.details}, {"status", i.status}, 
            {"assigned_unit_id", i.assigned_unit_id}
        });
    }
    output["incidents"] = incidents_json;

    return output.dump();
}
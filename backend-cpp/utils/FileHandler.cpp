#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using json = nlohmann::json;

// --- Unit I/O ---

std::vector<Unit> FileHandler::readAllUnits(const std::string& path) {
    std::vector<Unit> units;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << path << ". Returning empty list." << std::endl;
        return units; 
    }

    try {
        json j;
        file >> j;
        for (const auto& item : j) {
            units.emplace_back(
                item.value("id", 0L),
                item.value("name", "N/A"),
                item.value("type", "N/A"),
                item.value("current_latitude", 0.0),
                item.value("current_longitude", 0.0),
                item.value("status", "available")
            );
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading or parsing " << path << ": " << e.what() << std::endl;
    }
    return units;
}

void FileHandler::saveUnits(const std::vector<Unit>& units, const std::string& path) {
    json j = json::array();
    for (const auto& unit : units) {
        j.push_back({
            {"id", unit.id},
            {"name", unit.name},
            {"type", unit.type},
            {"current_latitude", unit.current_latitude},
            {"current_longitude", unit.current_longitude},
            {"status", unit.status}
        });
    }
    std::ofstream file(path);
    if (file.is_open()) {
        file << j.dump(4); // Pretty print with 4 spaces
    } else {
        std::cerr << "Error: Could not open " << path << " for writing." << std::endl;
    }
}

// --- Incident I/O (Simplified) ---

void FileHandler::saveNewIncident(const Incident& new_incident, const std::string& path) {
    std::vector<Incident> incidents = readAllIncidents(path);
    
    // Assign a new ID (simple max ID + 1 strategy)
    long next_id = getNextIncidentId(incidents);
    Incident incident_to_save = new_incident;
    incident_to_save.id = next_id;
    
    incidents.push_back(incident_to_save);
    saveIncidents(incidents, path);
}

// Helper to find the next available ID
long FileHandler::getNextIncidentId(const std::vector<Incident>& incidents) {
    if (incidents.empty()) return 1001; // Start ID
    long max_id = 0;
    for (const auto& inc : incidents) {
        if (inc.id > max_id) max_id = inc.id;
    }
    return max_id + 1;
}

// Save all incidents (used for updates)
void FileHandler::saveIncidents(const std::vector<Incident>& incidents, const std::string& path) {
    json j = json::array();
    for (const auto& incident : incidents) {
        j.push_back({
            {"id", incident.id},
            {"latitude", incident.latitude},
            {"longitude", incident.longitude},
            {"details", incident.details},
            {"status", incident.status},
            {"assigned_unit_id", incident.assigned_unit_id}
        });
    }
    std::ofstream file(path);
    if (file.is_open()) {
        file << j.dump(4);
    } else {
        std::cerr << "Error: Could not open " << path << " for writing." << std::endl;
    }
}

std::vector<Incident> FileHandler::readAllIncidents(const std::string& path) {
    std::vector<Incident> incidents;
    std::ifstream file(path);
    if (!file.is_open()) return incidents;

    try {
        json j;
        file >> j;
        for (const auto& item : j) {
            Incident inc;
            inc.id = item.value("id", 0L);
            inc.latitude = item.value("latitude", 0.0);
            inc.longitude = item.value("longitude", 0.0);
            inc.details = item.value("details", "");
            inc.status = item.value("status", "active");
            inc.assigned_unit_id = item.value("assigned_unit_id", 0L);
            incidents.push_back(inc);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading or parsing " << path << ": " << e.what() << std::endl;
    }
    return incidents;
}
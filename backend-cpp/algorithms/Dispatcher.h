// #ifndef DISPATCHER_H
// #define DISPATCHER_H

// #include "../models/Unit.h"
// #include "Graph.h"
// #include <vector>
// #include <tuple>
// #include <string>

// class Dispatcher {
// private:
//     Graph road_graph;
//     const std::string UNITS_FILE = "backend-cpp/data/units.json";
//     const std::string INCIDENTS_FILE = "backend-cpp/data/incidents.json";

//     // Step 1: Fetch Available Units (Reads from JSON file)
//     std::vector<Unit> fetchAvailableUnits(); 

//     // Step 2: Nearest Neighbor Search
//     Unit findClosestUnit(double incident_lat, double incident_lon, const std::vector<Unit>& available_units);
    
//     // Update the unit status and save back to file
//     void updateUnitStatus(long unit_id, const std::string& new_status);

// public:
//     Dispatcher(const std::string& graph_path) : road_graph(graph_path) {}
    
//     [cite_start]// Core function to find the unit and the route (Steps 2 & 3) [cite: 35]
//     std::tuple<Unit, std::vector<std::pair<double, double>>> executeDispatch(
//         double incident_lat, 
//         double incident_lon, 
//         const std::string& details
//     );
    
//     // For Polling API
//     std::string getFullStatusJson();
// };

// #endif // DISPATCHER_H




// #ifndef DISPATCHER_H
// #define DISPATCHER_H

// #include "../models/Unit.h"
// #include "../models/Incident.h" // Needed for saving new incidents
// #include "Graph.h"
// #include <vector>
// #include <tuple>
// #include <string>

// /**
//  * @class Dispatcher
//  * @brief Orchestrates the Intelligent Dispatch logic by coordinating 
//  * file I/O (FileHandler), distance calculation (Haversine via Graph), 
//  * and routing (Dijkstra via Graph).
//  */
// class Dispatcher {
// private:
//     Graph road_graph;
//     // Paths to mock database files
//     const std::string UNITS_FILE = "backend-cpp/data/units.json";
//     const std::string INCIDENTS_FILE = "backend-cpp/data/incidents.json";

//     // Step 1: Fetch Available Units (Reads from JSON file via FileHandler)
//     std::vector<Unit> fetchAvailableUnits(); 

//     // Step 2: Nearest Neighbor Search (Uses Haversine)
//     Unit findClosestUnit(double incident_lat, double incident_lon, const std::vector<Unit>& available_units);
    
//     // Update the unit status and save back to file
//     void updateUnitStatus(long unit_id, const std::string& new_status);

// public:
//     // Constructor initializes the road graph
//     Dispatcher(const std::string& graph_path);
    
//     [cite_start]// Core function: To identify the best available rescue unit and calculate the fastest route[cite: 35].
//     std::tuple<Unit, std::vector<std::pair<double, double>>> executeDispatch(
//         double incident_lat, 
//         double incident_lon, 
//         const std::string& details
//     );
    
//     // For Polling API: Fetches and formats the entire current system status (units + incidents)
//     std::string getFullStatusJson();
// };

// #endif // DISPATCHER_H



#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "../models/Unit.h"
#include "../models/Incident.h" 
#include "Graph.h"
#include <vector>
#include <tuple>
#include <string>

/**
 * @class Dispatcher
 * @brief Orchestrates the Intelligent Dispatch logic by coordinating 
 * file I/O (FileHandler), distance calculation (Haversine via Graph), 
 * and routing (Dijkstra via Graph).
 */
class Dispatcher {
private:
    Graph road_graph;
    // Paths to mock database files
    const std::string UNITS_FILE = "backend-cpp/data/units.json";
    const std::string INCIDENTS_FILE = "backend-cpp/data/incidents.json";

    // Step 1: Fetch Available Units (Reads from JSON file via FileHandler)
    std::vector<Unit> fetchAvailableUnits(); 

    // Step 2: Nearest Neighbor Search (Uses Haversine)
    Unit findClosestUnit(double incident_lat, double incident_lon, const std::vector<Unit>& available_units);
    
    // Update the unit status and save back to file
    void updateUnitStatus(long unit_id, const std::string& new_status);

public:
    // Constructor initializes the road graph
    Dispatcher(const std::string& graph_path);
    
    // Core function: To identify the best available rescue unit and calculate the fastest route. [cite: 35]
    std::tuple<Unit, std::vector<std::pair<double, double>>> executeDispatch(
        double incident_lat, 
        double incident_lon, 
        const std::string& details
    );
    
    // For Polling API: Fetches and formats the entire current system status (units + incidents)
    std::string getFullStatusJson();
};

#endif // DISPATCHER_H
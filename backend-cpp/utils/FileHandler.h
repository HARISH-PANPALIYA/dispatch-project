#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include "../models/Unit.h"
#include "../models/Incident.h"
//#include "../json.hpp" // nlohmann/json
//#include "include/nlohmann/json.hpp" 
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class FileHandler {
private:
    static long getNextIncidentId(const std::vector<Incident>& incidents);

public:
    // Units
    static std::vector<Unit> readAllUnits(const std::string& path);
    static void saveUnits(const std::vector<Unit>& units, const std::string& path);

    // Incidents
    static std::vector<Incident> readAllIncidents(const std::string& path);
    static void saveNewIncident(const Incident& incident, const std::string& path);
    static void saveIncidents(const std::vector<Incident>& incidents, const std::string& path);

    // Graph - Simple read-only utility
    static json readGraphData(const std::string& path);
};

#endif // FILEHANDLER_H
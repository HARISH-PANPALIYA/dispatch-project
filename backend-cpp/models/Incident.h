#ifndef INCIDENT_H
#define INCIDENT_H

#include <string>

class Incident {
public:
    long id;
    double latitude;
    double longitude;
    std::string details;
    std::string status; // "active", "assigned", "resolved"
    long assigned_unit_id;

    Incident() : id(0), latitude(0.0), longitude(0.0), assigned_unit_id(0), status("active") {}

    Incident(long id, double lat, double lon, const std::string& details)
        : id(id), latitude(lat), longitude(lon), details(details), status("active"), assigned_unit_id(0) {}
};

#endif // INCIDENT_H
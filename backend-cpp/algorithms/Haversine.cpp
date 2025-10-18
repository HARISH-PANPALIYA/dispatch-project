// #include "Haversine.h"

// [cite_start]
// // Implementation of the Haversine Formula [cite: 22]
// double Haversine::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
//     // Convert degrees to radians
//     double rLat1 = degToRad(lat1);
//     double rLon1 = degToRad(lon1);
//     double rLat2 = degToRad(lat2);
//     double rLon2 = degToRad(lon2);

//     // Haversine formula
//     double dlat = rLat2 - rLat1;
//     double dlon = rLon2 - rLon1;

//     double a = std::pow(std::sin(dlat / 2.0), 2.0) +
//                std::cos(rLat1) * std::cos(rLat2) *
//                std::pow(std::sin(dlon / 2.0), 2.0);

//     double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

//     // Distance in Kilometers
//     return EARTH_RADIUS_KM * c;
// }



// #include "Haversine.h"
// #include <cmath> // Already included in .h, but good practice for .cpp

// double Haversine::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
//     // Access static utility function and constant using class scope (Haversine::)
//     double rLat1 = Haversine::degToRad(lat1);
//     double rLon1 = Haversine::degToRad(lon1);
//     double rLat2 = Haversine::degToRad(lat2);
//     double rLon2 = Haversine::degToRad(lon2);

//     double dlat = rLat2 - rLat1;
//     double dlon = rLon2 - rLon1;

//     // Haversine formula calculation
//     double a = std::pow(std::sin(dlat / 2.0), 2.0) +
//                std::cos(rLat1) * std::cos(rLat2) *
//                std::pow(std::sin(dlon / 2.0), 2.0);

//     double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

//     [cite_start]// Result is multiplied by the Earth's radius (EARTH_RADIUS_KM) [cite: 22]
//     return Haversine::EARTH_RADIUS_KM * c;
// }



#include "Haversine.h"
#include <cmath>

double Haversine::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // Access static utility function and constant using class scope (Haversine::)
    double rLat1 = Haversine::degToRad(lat1);
    double rLon1 = Haversine::degToRad(lon1);
    double rLat2 = Haversine::degToRad(lat2);
    double rLon2 = Haversine::degToRad(lon2);

    double dlat = rLat2 - rLat1;
    double dlon = rLon2 - rLon1;

    // Haversine formula calculation
    double a = std::pow(std::sin(dlat / 2.0), 2.0) +
               std::cos(rLat1) * std::cos(rLat2) *
               std::pow(std::sin(dlon / 2.0), 2.0);

    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    // Final distance calculation
    return Haversine::EARTH_RADIUS_KM * c;
}
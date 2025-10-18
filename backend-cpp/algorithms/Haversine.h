#ifndef HAVERSINE_H
#define HAVERSINE_H

#include <cmath>

/**
 * @class Haversine
 * @brief Provides a static method to calculate the great-circle distance 
 * between two geographic coordinates using the Haversine formula.
 * * This calculation is essential for finding the "nearest" unit. 
 */
class Haversine {
private:
    // Radius of the Earth in Kilometers (used for distance calculation)
    static constexpr double EARTH_RADIUS_KM = 6371.0; 

    /**
     * @brief Converts degrees to radians.
     */
    static inline double degToRad(double degrees) {
        return degrees * M_PI / 180.0;
    }

public:
    /**
     * @brief Calculates the distance between two points.
     * * @param lat1 Latitude of the first point.
     * @param lon1 Longitude of the first point.
     * @param lat2 Latitude of the second point.
     * @param lon2 Longitude of the second point.
     * @return double Distance in kilometers.
     */
    static double calculateDistance(double lat1, double lon1, double lat2, double lon2);
};

#endif // HAVERSINE_H
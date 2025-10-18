// #ifndef UNIT_H
// #define UNIT_H

// #include <string>

// class Unit {
// public:
//     long id;
//     std::string name;
//     std::string type;
//     double current_latitude;
//     double current_longitude;
//     std::string status; // "available", "dispatched", "on_site"

//     Unit() : id(0), current_latitude(0.0), current_longitude(0.0), status("available") {}

//     Unit(long id, 
//         const std::string& name,
//          double lat,
//           double lon, 
//           const std::string& status,
//           const std:: string& type)
//         : id(id), name(name), current_latitude(lat), current_longitude(lon), status(status),type(type) {}
// };

// #endif // UNIT_H

#ifndef UNIT_H
#define UNIT_H

#include <string>

class Unit {
public:
    long id;
    std::string name;
    std::string type;
    double current_latitude;
    double current_longitude;
    std::string status; // "available", "dispatched", "on_site"

    Unit() : id(0), current_latitude(0.0), current_longitude(0.0), status("available") {}

    // CORRECTED CONSTRUCTOR SIGNATURE (Matches the 6 arguments from FileHandler.cpp)
    // Order: (long id, string name, string type, double lat, double lon, string status)
    Unit(long id, 
         const std::string& name,
         const std::string& type,  // <-- MOVED 'type' HERE
         double lat,
         double lon, 
         const std::string& status)
        : id(id), 
          name(name), 
          type(type),               // <-- INITIALIZE 'type'
          current_latitude(lat), 
          current_longitude(lon), 
          status(status) 
    {}
};

#endif // UNIT_H
// //#include "crow_all.h"
// //#include "crow/include/crow.h"

// #include "crow/include/crow.h" 
// #include "algorithms/Dispatcher.h"
// //#include "json.hpp" 
// #include <iostream>
// #include <string>
// //#include "include/nlohmann/json.hpp" 
// #include "nlohmann/json.hpp"
// // Global Dispatcher instance (Handles all core logic and file I/O)
// // NOTE: Adjust the graph_data.json path if running the executable from a different location.
// Dispatcher dispatcher("backend-cpp/data/graph_data.json"); 

// using json = nlohmann::json;

// int main() {
//     crow::SimpleApp app;

//     // 1. Endpoint for serving the frontend files (Static File Handler)
//     // Serves index.html when root is accessed, and allows access to script.js and style.css
//     CROW_ROUTE(app, "/")
//     ([&](const crow::request& req, crow::response& res) {
//         res.set_static_file_info("frontend/index.html");
//         res.end();
//     });

//     [cite_start]// 2. Core Logic Endpoint: Intelligent Dispatch [cite: 33]
//     CROW_ROUTE(app, "/api/dispatch")
//         .methods("POST"_method)
//         ([&](const crow::request& req) {
        
//         try {
//             auto x = json::parse(req.body);
//             double incident_lat = x.value("latitude", 0.0);
//             double incident_lon = x.value("longitude", 0.0);
//             std::string details = x.value("details", "No details provided.");
            
//             if (incident_lat == 0.0 || incident_lon == 0.0) {
//                 return crow::response(400, "Invalid coordinates.");
//             }

//             [cite_start]// Execute the core OOP logic: Nearest Unit & Optimal Route [cite: 22, 23]
//             auto [closest_unit, route_path] = dispatcher.executeDispatch(
//                 incident_lat, 
//                 incident_lon,
//                 details
//             );

//             // Prepare Response
//             json response;
//             response["unit_id"] = closest_unit.id;
//             response["unit_name"] = closest_unit.name;
            
//             // Format path coordinates for JavaScript visualization
//             json path_json = json::array();
//             for (const auto& coord : route_path) {
//                 path_json.push_back({coord.first, coord.second});
//             }
//             response["path"] = path_json;
            
//             return crow::response(200, response.dump());

//         } catch (const std::exception& e) {
//             std::cerr << "Dispatch Error: " << e.what() << std::endl;
//             return crow::response(500, std::string("{\"error\": \"") + e.what() + "\"}");
//         }
//     });
    
//     // 3. Polling Endpoint: Refresh Map Data
//     CROW_ROUTE(app, "/api/data/refresh")
//         .methods("GET"_method)
//         ([&]() {
//         // The dispatcher handles reading the latest state from the JSON files
//         return crow::response(200, dispatcher.getFullStatusJson());
//     });

//     // Start the server
//     std::cout << "C++ Dispatch Server running on http://localhost:18080" << std::endl;
//     app.port(18080).multithreaded().run();
// }




//#include "crow/include/crow.h" // Fix this include path in your VSCode settings!    [Don't add this ]



// #include "crow.h"
// #include "algorithms/Dispatcher.h"
// #include <iostream>
// #include <string>
// #include "nlohmann/json.hpp" 

// // Global Dispatcher instance (Handles all core logic and file I/O)
// // NOTE: Adjust the graph_data.json path if running the executable from a different location.
// Dispatcher dispatcher("backend-cpp/data/graph_data.json"); 

// using json = nlohmann::json;

// int main() {
//     crow::SimpleApp app;

//     // 1. Endpoint for serving the frontend files (Static File Handler)
//     // Serves index.html when root is accessed, and allows access to script.js and style.css
//     CROW_ROUTE(app, "/")
//     ([&](const crow::request& req, crow::response& res) {
//         res.set_static_file_info("frontend/index.html");
//         res.end();
//     });

//     // 2. Core Logic Endpoint: Intelligent Dispatch
//     CROW_ROUTE(app, "/api/dispatch")
//         .methods("POST"_method)
//         ([&](const crow::request& req) {
        
//         try {
//             auto x = json::parse(req.body);
//             double incident_lat = x.value("latitude", 0.0);
//             double incident_lon = x.value("longitude", 0.0);
//             std::string details = x.value("details", "No details provided.");
            
//             if (incident_lat == 0.0 || incident_lon == 0.0) {
//                 return crow::response(400, "Invalid coordinates.");
//             }

//             // Execute the core OOP logic: Nearest Unit & Optimal Route
//             auto [closest_unit, route_path] = dispatcher.executeDispatch(
//                 incident_lat, 
//                 incident_lon,
//                 details
//             );

//             // Prepare Response
//             json response;
//             response["unit_id"] = closest_unit.id;
//             response["unit_name"] = closest_unit.name;
            
//             // Format path coordinates for JavaScript visualization
//             json path_json = json::array();
//             for (const auto& coord : route_path) {
//                 path_json.push_back({coord.first, coord.second});
//             }
//             response["path"] = path_json;
            
//             return crow::response(200, response.dump());

//         } catch (const std::exception& e) {
//             std::cerr << "Dispatch Error: " << e.what() << std::endl;
//             // The following line was confusing the compiler, ensure it's simple
//             return crow::response(500, std::string("{\"error\": \"") + e.what() + "\"}");
//         }
//     });
    
//     // 3. Polling Endpoint: Refresh Map Data
//     CROW_ROUTE(app, "/api/data/refresh")
//         .methods("GET"_method)
//         ([&]() {
//         // The dispatcher handles reading the latest state from the JSON files
//         return crow::response(200, dispatcher.getFullStatusJson());
//     });

//     // Start the server
//     std::cout << "C++ Dispatch Server running on http://localhost:18080" << std::endl;
//     app.port(18080).multithreaded().run();
// }







// #include "crow.h"
// #include "algorithms/Dispatcher.h"
// #include <iostream>
// #include <string>
// #include "nlohmann/json.hpp" 

// // Global Dispatcher instance (Handles all core logic and file I/O)
// // NOTE: Adjust the graph_data.json path if running the executable from a different location.
// Dispatcher dispatcher("backend-cpp/data/graph_data.json"); 

// using json = nlohmann::json;

// int main() {
//     crow::SimpleApp app;

//     // 1. Endpoint for serving the frontend files (Static File Handler for index.html)
//     CROW_ROUTE(app, "/")
//     ([&](const crow::request& req, crow::response& res) {
//         res.set_static_file_info("frontend/index.html");
//         res.end();
//     });

//     // =========================================================================
//     // NEW ROUTE ADDED TO SERVE STATIC ASSETS (script.js, style.css, etc.)
//     // This catches requests for files that aren't APIs or the root index.
//     // =========================================================================
//     CROW_ROUTE(app, "/<path>") 
//     ([&](const crow::request& req, crow::response& res, const std::string& filename) {
//         // Construct the full path to the asset in the 'frontend' directory
//         std::string full_path = "frontend/" + filename;

//         // Use set_static_file_info to automatically determine file type and serve it
//         res.set_static_file_info(full_path); 

//         // If the file was not found by set_static_file_info, Crow sets the status to 404.
//         // We ensure a simple end to the response.
//         res.end();
//     });
//     // =========================================================================

//     // 2. Core Logic Endpoint: Intelligent Dispatch
//     CROW_ROUTE(app, "/api/dispatch")
//         .methods("POST"_method)
//         ([&](const crow::request& req) {
        
//         try {
//             auto x = json::parse(req.body);
//             double incident_lat = x.value("latitude", 0.0);
//             double incident_lon = x.value("longitude", 0.0);
//             std::string details = x.value("details", "No details provided.");
            
//             if (incident_lat == 0.0 || incident_lon == 0.0) {
//                 return crow::response(400, "Invalid coordinates.");
//             }

//             // Execute the core OOP logic: Nearest Unit & Optimal Route
//             auto [closest_unit, route_path] = dispatcher.executeDispatch(
//                 incident_lat, 
//                 incident_lon,
//                 details
//             );

//             // Prepare Response
//             json response;
//             response["unit_id"] = closest_unit.id;
//             response["unit_name"] = closest_unit.name;
            
//             // Format path coordinates for JavaScript visualization
//             json path_json = json::array();
//             for (const auto& coord : route_path) {
//                 path_json.push_back({coord.first, coord.second});
//             }
//             response["path"] = path_json;
            
//             return crow::response(200, response.dump());

//         } catch (const std::exception& e) {
//             std::cerr << "Dispatch Error: " << e.what() << std::endl;
//             // Return a clean 500 error response
//             return crow::response(500, std::string("{\"error\": \"") + e.what() + "\"}");
//         }
//     });
    
//     // 3. Polling Endpoint: Refresh Map Data
//     CROW_ROUTE(app, "/api/data/refresh")
//         .methods("GET"_method)
//         ([&]() {
//         // The dispatcher handles reading the latest state from the JSON files
//         return crow::response(200, dispatcher.getFullStatusJson());
//     });

//     // Start the server
//     std::cout << "C++ Dispatch Server running on http://localhost:18080" << std::endl;
//     app.port(18080).multithreaded().run();
// }




#include "crow.h"
#include "algorithms/Dispatcher.h"
#include <iostream>
#include <string>
#include "nlohmann/json.hpp" 

// Global Dispatcher instance (Handles all core logic and file I/O)
// NOTE: Adjust the graph_data.json path if running the executable from a different location.
Dispatcher dispatcher("backend-cpp/data/graph_data.json"); 

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;

    // 1. Root Endpoint: Serves index.html
    CROW_ROUTE(app, "/")
    ([&](const crow::request& req, crow::response& res) {
        res.set_static_file_info("frontend/index.html");
        res.end();
    });

    // 2. Core Logic Endpoint: Intelligent Dispatch (Keep specific APIs BEFORE generic routes)
    CROW_ROUTE(app, "/api/dispatch")
        .methods("POST"_method)
        ([&](const crow::request& req) {
        
        try {
            auto x = json::parse(req.body);
            double incident_lat = x.value("latitude", 0.0);
            double incident_lon = x.value("longitude", 0.0);
            std::string details = x.value("details", "No details provided.");
            
            if (incident_lat == 0.0 || incident_lon == 0.0) {
                return crow::response(400, "Invalid coordinates.");
            }

            // Execute the core OOP logic: Nearest Unit & Optimal Route
            auto [closest_unit, route_path] = dispatcher.executeDispatch(
                incident_lat, 
                incident_lon,
                details
            );

            // Prepare Response
            json response;
            response["unit_id"] = closest_unit.id;
            response["unit_name"] = closest_unit.name;
            
            // Format path coordinates for JavaScript visualization
            json path_json = json::array();
            for (const auto& coord : route_path) {
                path_json.push_back({coord.first, coord.second});
            }
            response["path"] = path_json;
            
            return crow::response(200, response.dump());

        } catch (const std::exception& e) {
            std::cerr << "Dispatch Error: " << e.what() << std::endl;
            // Return a clean 500 error response
            return crow::response(500, std::string("{\"error\": \"") + e.what() + "\"}");
        }
    });
    
    // 3. Polling Endpoint: Refresh Map Data (Keep specific APIs BEFORE generic routes)
    CROW_ROUTE(app, "/api/data/refresh")
        .methods("GET"_method)
        ([&]() {
        // The dispatcher handles reading the latest state from the JSON files
        return crow::response(200, dispatcher.getFullStatusJson());
    });

    // =========================================================================
    // CRITICAL FIX: MOVE STATIC ASSET ROUTE TO THE END 
    // This CATCH-ALL route MUST come last to avoid overriding the /api/ routes.
    // =========================================================================
    CROW_ROUTE(app, "/<path>") 
    ([&](const crow::request& req, crow::response& res, const std::string& filename) {
        // Construct the full path to the asset in the 'frontend' directory
        std::string full_path = "frontend/" + filename;

        // Use set_static_file_info to automatically determine file type and serve it
        res.set_static_file_info(full_path); 

        // We ensure a simple end to the response.
        res.end();
    });
    // =========================================================================

    // Start the server
    std::cout << "C++ Dispatch Server running on http://localhost:18080" << std::endl;
    app.port(18080).multithreaded().run();
}
# cmake_minimum_required(VERSION 3.10)
# project(DispatchProject)

# # Set C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Define source files
# set(SOURCE_FILES
#     main.cpp
#     algorithms/Haversine.cpp
#     algorithms/Graph.cpp
#     algorithms/Dijkstra.cpp
#     algorithms/Dispatcher.cpp
#     utils/FileHandler.cpp
# )

# # --- External Library Configuration ---
# # You need to define how to find and link the Crow library here.
# # Assuming a standard installation or local submodule:
# # find_package(CROW REQUIRED) 
# # target_link_libraries(DispatchProject CROW::CROW)

# # If linking a local Crow header and using simple HTTP for static files (no SSL, etc.)
# # and assuming you have a way to include the necessary headers.

# # --- Project Executable ---
# add_executable(DispatchProject ${SOURCE_FILES})

# # Link necessary dependencies (assuming Crow and nlohmann/json are handled via headers/submodules)
# # For the `main.cpp` server logic to find the static frontend files:
# target_include_directories(DispatchProject PUBLIC 
#     "${CMAKE_CURRENT_SOURCE_DIR}"
# )




cmake_minimum_required(VERSION 3.10)
project(DispatchProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source files (Unchanged)
set(SOURCE_FILES
    main.cpp
    algorithms/Haversine.cpp
    # ... add all other .cpp files ...
    algorithms/Graph.cpp
    algorithms/Dispatcher.cpp
    utils/FileHandler.cpp
)

# --- Project Executable ---
add_executable(DispatchProject ${SOURCE_FILES})
if (WIN32)
 target_link_libraries(DispatchProject 
        ws2_32  Iphlpapi Mswsock) 
endif()

# Export to Sheets


# --- Include Directories Configuration ---
target_include_directories(DispatchProject PUBLIC 
    # 1. Project source directories (for finding your .h files)
    "${CMAKE_CURRENT_SOURCE_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/models"
    "${CMAKE_CURRENT_SOURCE_DIR}/algorithms"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils"

    # 2. CROW Headers: Path to the directory containing 'crow.h'
    # Base: F:\dispatch-project\backend-cpp\crow\include
    "${CMAKE_CURRENT_SOURCE_DIR}/crow/include"

    # 3. Nlohmann/JSON Headers: Path to the directory containing 'nlohmann' folder
    # Base: F:\dispatch-project\backend-cpp\json-develop\include
    "${CMAKE_CURRENT_SOURCE_DIR}/json-develop/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/asio-master/asio-master/asio/include"
)
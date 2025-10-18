🚨 Emergency Dispatch Simulation System
1. Configure the Build Environment (One-time setup): This creates the necessary build files, linking the C++ libraries (including ws2_32 for Windows networking)
      cd backend-cpp
      cmake -S . -B build -G "MinGW Makefiles"
2.  Compile the Executable
       cmake --build build -j
3. Run the Server
       cd ..
        .\backend-cpp\build\DispatchProject.exe


/dispatch-project/
├── backend-cpp/              # C++ Source Code Root
│   ├── build/                # (IGNORED) Compiled files and CMake cache
│   ├── algorithms/           # Dijkstra's logic, Graph, Dispatcher implementation
│   ├── models/               # Data structures (Unit, Node, Edge)
│   ├── data/                 # JSON data files (graph_data.json, units.json)
│   ├── CMakeLists.txt        # Build instructions
│   └── main.cpp              # Server entry point and API routes
├── frontend/                 # Web Application Files
│   ├── index.html            # Main page
│   ├── script.js             # Frontend logic and API calls
│   └── style.css             # Styling
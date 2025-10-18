🚨 Emergency Dispatch Simulation System
1. Configure the Build Environment (One-time setup): This creates the necessary build files, linking the C++ libraries (including ws2_32 for Windows networking)
      cd backend-cpp
      cmake -S . -B build -G "MinGW Makefiles"
2.  Compile the Executable
       cmake --build build -j
3. Run the Server
       cd ..
        .\backend-cpp\build\DispatchProject.exe

# Required libraries (must be installed globally)

## For Linux:
## libglfw3
## libglew-dev

## For Windows, I have yet to personally get vcpkg working, but theoretically one could use that and then run CMake.
## If that doesn't work, you can use Windows Subsystem for Linux. Everything should run fine.

# Generate build files and run:

        cmake -S . -B build/
        cd build/
        make
## Or for recompilation:

        cmake ..
        make
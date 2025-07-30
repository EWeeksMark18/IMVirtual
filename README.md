# Required libraries (must be installed globally)

## For Linux:
You must install libglfw3-dev, libglfw3, and libglew-dev with your package manager. 
For my debian based distro:

        sudo apt install libglfw3-dev libglfw3 libglew-dev

Legacy OpenGL should be installed by default on most Linux systems. If not for some reason, install that.

## For Windows
For this project, I recommend using vcpkg to install the packages glfw3, glew, and opengl respectively.

        .\vcpkg install glfw3 glew opengl

Also be sure to integrate with CMake:

        .\vcpkg integrate install

# Generate build files and run:
## On Linux

        cmake -S . -B build/
        cd build/
        make

### Or for recompilation (while in the build folder):

        cmake ..
        make

## On Windows
I ran into some strange issues with vcpkg and glfw3. So on Windows, run this:

        cmake -S . -B \build\ -DCMAKE_TOOLCHAIN_FILE=<your-path-to-vcpkg>\scripts\buildsystems\vcpkg.cmake

This creates a visual studio solution that you can easily build. On my Windows 11 laptop, the GUI looks a little weird,
so expect me to work on that in the future.

## Locating and running .imx programs. 
I added an example program called 'basic.imx' in the /vasm_programs/ folder.
Drag that into your build folder, and type its name/file path into the input box above the 'Run CPU' button.
You will then see the program load data into the registers and data section (the latter of which still needs some work, mind you). 
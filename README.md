# Jolt
C++ / OpenGL game engine
## Installation
* Clone repo with `git clone --recursive https://github.com/junnys6018/Jolt` 
* Premake files are provided to generate project files for any supported toolset. 
* Shell scripts are provided to generate visual studio project files for Windows and makefiles for Linux 
### Windows
1. Install visual studio 2019
2. Run `scripts/GenerateWindowsProjects.bat` to generate visual studio project files 
### Linux
1. Install required dependencies with `sudo apt-get install g++ make xorg-dev`
2. cd to `scripts` directory
3. Run `GenerateLinuxProjects.sh` to generate makefiles

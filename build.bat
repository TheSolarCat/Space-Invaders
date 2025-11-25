@echo off
REM Set up Visual Studio environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

REM Navigate to build directory
cd /d "C:\Users\myz\Documents\Projects\Space Invaders"
if exist build rmdir /s /q build
mkdir build
cd build

REM Configure with CMake
"C:\Program Files\CMake\bin\cmake.exe" .. -G "Visual Studio 16 2019" -DSFML_DIR="C:\Users\myz\Documents\Projects\Space Invaders\SFML-2.5.1\lib\cmake\SFML"

REM Build
"C:\Program Files\CMake\bin\cmake.exe" --build . --config Release

echo.
echo Build complete! Check for SpaceInvaders.exe in the Release folder
pause

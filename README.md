# light-effects
An application for allowing keyboard control over Philips HUE lights.

## Prerequisites
* Have visual studio installed
* Have cmake 3 installed

## Initial Setup
1. Clone this repo
2. cd into the repo
3. Run `mkdir build`
4. Run `clone https://github.com/PhilipsHue/EDK.git`
5. cd into build
6. Run `cmake ..`
7. Run `cmake --build .`
8. Run application. If in VS Code, the launch.json is already configured, otherwise it is build/Debug/LightEffects.exe

## Future build
1. Run `cmake build --build .` from root of repo
2. Run application.
@echo OFF

cmake -B "build"

CD build
cmake --build .

pause
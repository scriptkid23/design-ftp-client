@echo OFF

cmake -B "build"

CD build
cmake --build .

echo Compiler succeeded
pause
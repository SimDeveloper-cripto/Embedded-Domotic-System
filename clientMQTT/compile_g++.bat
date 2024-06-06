@echo off

g++ -o bin/main -Wall clientMQTT.cpp main.cpp -lmosquittopp -lmosquitto

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable generated in /bin folder.
) else (
    echo [ ERROR ] Encountered compilation errors. 
)

pause
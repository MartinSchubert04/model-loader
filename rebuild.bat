@echo off
setlocal

REM ---- REMOVE BUILD DIR ----
IF EXIST build (
    rmdir /s /q build
)

REM 
./build.bat

endlocal

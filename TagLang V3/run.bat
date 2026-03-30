@echo off
:: Chay mot file .tl bat ky
:: Usage: run.bat <file.tl>

if "%1"=="" (
    echo Usage: run.bat ^<file.tl^>
    echo Vi du: run.bat examples\05_showcase.tl
    pause
    exit /b 1
)

if not exist taglang.exe (
    echo [ERROR] Chua build! Chay build.bat truoc.
    pause
    exit /b 1
)

taglang.exe %1 -o _tmp_run.cpp
if %ERRORLEVEL% NEQ 0 ( pause & exit /b 1 )

g++ _tmp_run.cpp -o _tmp_run.exe -lm
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Loi bien dich C++!
    if exist _tmp_run.cpp del _tmp_run.cpp
    pause
    exit /b 1
)

echo.
echo === KET QUA ===
_tmp_run.exe
echo ===============
echo.

if exist _tmp_run.cpp del _tmp_run.cpp
if exist _tmp_run.exe del _tmp_run.exe

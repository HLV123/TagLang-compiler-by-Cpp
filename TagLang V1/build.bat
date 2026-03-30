@echo off
echo ================================================
echo   TagLang Compiler - Build Script (Windows)
echo ================================================

where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] g++ khong tim thay!
    echo Vui long cai MinGW hoac MSYS2.
    echo Huong dan: xem HUONG_DAN.txt
    pause
    exit /b 1
)

echo [1/2] Dang bien dich TagLang compiler...
g++ -std=c++17 -O2 src\main.cpp -o taglang.exe

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Bien dich that bai!
    pause
    exit /b 1
)

echo [2/2] Thanh cong! File taglang.exe da duoc tao.
echo.
echo === Chay thu cac vi du ===
echo.

echo --- Vi du 1: Hello World ---
taglang.exe examples\01_hello.tl -o _tmp.cpp
g++ _tmp.cpp -o _tmp.exe -lm
_tmp.exe
echo.

echo --- Vi du 2: Tinh toan ---
taglang.exe examples\02_calc.tl -o _tmp.cpp
g++ _tmp.cpp -o _tmp.exe -lm
_tmp.exe
echo.

echo --- Vi du 3: Logic ---
taglang.exe examples\03_logic.tl -o _tmp.cpp
g++ _tmp.cpp -o _tmp.exe -lm
_tmp.exe
echo.

echo --- Vi du 4: Full Demo ---
taglang.exe examples\04_full_demo.tl -o _tmp.cpp
g++ _tmp.cpp -o _tmp.exe -lm
_tmp.exe
echo.

echo --- Vi du 5: Showcase (tat ca 5 label) ---
taglang.exe examples\05_showcase.tl -o _tmp.cpp
g++ _tmp.cpp -o _tmp.exe -lm
_tmp.exe
echo.

if exist _tmp.cpp del _tmp.cpp
if exist _tmp.exe del _tmp.exe

echo ================================================
echo   Tat ca vi du da chay xong!
echo   Su dung: taglang.exe ^<file.tl^> -o out.cpp
echo ================================================
pause

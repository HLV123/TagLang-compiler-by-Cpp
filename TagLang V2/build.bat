@echo off
echo ================================================
echo   TagLang Compiler v2.0 - Build Script
echo   13 Labels
echo ================================================

where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] g++ khong tim thay! Xem HUONG_DAN.txt
    pause
    exit /b 1
)

echo [1/2] Dang bien dich TagLang compiler...
g++ -std=c++17 -O2 src\main.cpp -o taglang.exe
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build that bai!
    pause
    exit /b 1
)
echo [2/2] Thanh cong! taglang.exe da san sang.
echo.
echo === Chay thu cac vi du ===
echo.

echo --- Vi du 5: Showcase ---
taglang.exe examples\05_showcase.tl -o _tmp.cpp
g++ -std=c++17 _tmp.cpp -o _tmp.exe -lm
_tmp.exe
echo.

echo --- Vi du 6: Tat ca 13 Label ---
taglang.exe examples\06_labels.tl -o _tmp.cpp
g++ -std=c++17 _tmp.cpp -o _tmp.exe -lm
_tmp.exe
echo.

if exist _tmp.cpp del _tmp.cpp
if exist _tmp.exe del _tmp.exe

echo ================================================
echo   Tat ca label da chay xong!
echo   Su dung: run.bat [file.tl]
echo ================================================
pause

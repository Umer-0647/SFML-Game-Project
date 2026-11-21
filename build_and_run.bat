@echo off
REM ==========================================================
REM  One-click build + run for the Minesweeper SFML project.
REM  Put this file in the project folder (next to main.cpp)
REM  and double-click it, or run:  build_and_run.bat
REM ==========================================================
setlocal
cd /d "%~dp0"

REM --- Where SFML is installed (same path the .vcxproj uses) ---
set "SFML=C:\SFML\SFML-2.6.2"

if not exist "%SFML%\include\SFML\Graphics.hpp" (
    echo [ERROR] SFML not found at %SFML%
    echo Edit the SFML= line at the top of this file.
    pause
    exit /b 1
)

REM --- Load the Visual Studio C++ compiler (cl.exe) if it isn't loaded yet ---
where cl >nul 2>nul
if not errorlevel 1 goto compile
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -property installationPath`) do set "VSDIR=%%i"
call "%VSDIR%\VC\Auxiliary\Build\vcvars64.bat" >nul

:compile
echo Compiling ALL .cpp files into one Minesweeper.exe ...
cl /nologo /std:c++20 /EHsc /MD /W3 *.cpp /I "%SFML%\include" /Fe:Minesweeper.exe ^
   /link /LIBPATH:"%SFML%\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib sfml-audio.lib
if errorlevel 1 (
    echo.
    echo [ERROR] Build failed - read the errors above.
    pause
    exit /b 1
)

REM --- SFML's DLLs must sit next to the .exe or Windows can't start it ---
copy /y "%SFML%\bin\*.dll" . >nul

if not exist "assets\font.ttf"  echo [WARNING] assets\font.ttf is missing - menu text will be invisible.
if not exist "assets\tiles.png" echo [WARNING] assets\tiles.png is missing - board tiles will be blank.
if not exist "assets\minesweeper_explosion.wav" echo [WARNING] assets\minesweeper_explosion.wav is missing - no explosion sound.

echo Starting the game...
Minesweeper.exe

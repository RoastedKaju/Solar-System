@echo off
SETLOCAL

REM setup vcpkg path
set VCPKG_EXE=vendor\VCPKG\vcpkg.exe

REM check if vcpkg exists
if not exist %VCPKG_EXE% (
	echo [ERROR] vcpkg.exe not found, please run "vendor/VCPKG/bootstrap-vcpkg.bat" first
	pause
	exit /B 1
)

REM install dependencies
echo Installing dependencies....
%VCPKG_EXE% install glfw3 glew fmt glm assimp imgui[core,glfw-binding,opengl3-binding]

if %errorlevel% neq 0 (
	echo [ERROR] Installation failed.
	pause
	exit /B 1
)

echo [SUCCESS] Dependencies installed successfully
ENDLOCAL
PAUSE
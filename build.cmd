REM run as Administrator
@echo off
cd /d %~dp0
set DOWNLOAD_DIR=%USERPROFILE%\Downloads
set DOWNLOAD_DIR_LINUX=%DOWNLOAD_DIR:\=/%
SET PATH=%DOWNLOAD_DIR%\PortableGit\bin;%DOWNLOAD_DIR%\mingw64\bin;%DOWNLOAD_DIR%\cmake-3.22.0-rc1-windows-x86_64\bin;%PATH%
cmake.exe -G"MinGW Makefiles" -DCMAKE_C_COMPILER="%DOWNLOAD_DIR_LINUX%/LLVM-13.0.0-win64/bin/clang.exe" -B./build
cd build

:rebuild_and_startapp
cls
mingw32-make.exe
taskkill /f /im app.exe /FI "STATUS eq RUNNING"
app.exe
pause
GOTO rebuild_and_startapp


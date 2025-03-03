@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

:: 设置默认参数
set BUILD_TYPE=Release
set GENERATOR="Visual Studio 16 2019"
set BUILD_DIR=build
set INSTALL_DIR=install
set DO_BUILD=0
set DO_TEST=0
set DO_INSTALL=0
set DO_CLEAN=0

:: 如果没有参数，显示帮助信息
if "%1"=="" goto :show_help

:: 解析命令行参数
:parse_args
if "%1"=="" goto :done_parsing
if /i "%1"=="-debug" (
    set BUILD_TYPE=Debug
)else if /i "%1"=="-RelWithDebInfo" (
    set BUILD_TYPE=RelWithDebInfo
)else if /i "%1"=="-clean" (
    set DO_CLEAN=1
) else if /i "%1"=="-build" (
    set DO_BUILD=1
) else if /i "%1"=="-test" (
    set DO_TEST=1
) else if /i "%1"=="-install" (
    set DO_INSTALL=1
) else if /i "%1"=="-all" (
    set DO_BUILD=1
    set DO_TEST=1
    set DO_INSTALL=1
) else if /i "%1"=="-h" (
    goto :show_help
) else if /i "%1"=="-help" (
    goto :show_help
) else (
    echo Unknown parameter: %1
    goto :show_help
)
shift
goto :parse_args

:done_parsing
:: 清理构建目录
if %DO_CLEAN%==1 (
    echo Cleaning build directory...
    if exist %BUILD_DIR% rd /s /q %BUILD_DIR%
    if exist %INSTALL_DIR% rd /s /q %INSTALL_DIR%
)

:: 创建并进入构建目录
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
cd %BUILD_DIR%

:: 运行CMake配置
echo Configuring project (%BUILD_TYPE%)...
cmake -G %GENERATOR% -A x64 ^
    -DBUILD_TESTING=ON ^
    -DBUILD_EXAMPLES=ON ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    -DCMAKE_INSTALL_PREFIX=../%INSTALL_DIR% ^
    ..

:: 构建
if %DO_BUILD%==1 (
    echo Building project...
    cmake --build . --config %BUILD_TYPE% --parallel
    if errorlevel 1 (
        echo Build failed!
        exit /b 1
    )
)

:: 运行测试
if %DO_TEST%==1 (
    echo Running tests...
    ctest -C %BUILD_TYPE% --output-on-failure --verbose
    if errorlevel 1 (
        echo Tests failed!
        exit /b 1
    )
)

:: 安装
if %DO_INSTALL%==1 (
    echo Installing...
    cmake --install . --config %BUILD_TYPE%
    if errorlevel 1 (
        echo Installation failed!
        exit /b 1
    )
)

cd ..
echo Done!
exit /b 0

:show_help
echo Usage: build.bat [options]
echo Options:
echo   -debug        Build with Debug configuration (default: Release)
echo   -clean        Clean build directory
echo   -build        Build project
echo   -test         Run tests
echo   -install      Install project
echo   -all          Build + Test + Install
echo   -h, -help     Show this help message
exit /b 1

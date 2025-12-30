@echo off
:: 1. Navigate to the specific directory
:: %USERNAME% automatically gets the current user's name
set "TARGET_PATH=C:\Users\%USERNAME%\Documents\BareMetal-C"

if exist "%TARGET_PATH%" (
    cd /d "%TARGET_PATH%"
    echo Changed directory to: %TARGET_PATH%
) else (
    echo Error: Directory not found: %TARGET_PATH%
    pause
    exit /b 1
)

:: 2. Launch Docker
:: %cd% is the Windows Batch equivalent of ${PWD}
docker run --name baremetal-c --rm -it -v "%cd%:/student" ghcr.io/kongkrit/baremetal-c

:: Keep the window open if Docker exits (optional, remove 'pause' if you want it to close immediately)
:: pause
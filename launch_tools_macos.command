#!/bin/bash

# 1b. Navigate to the specific directory
# $USER dynamically fetches the current user's name
TARGET_PATH="/Users/$USER/Documents/BareMetal-C"

# Check if directory exists before trying to enter it
if [ -d "$TARGET_PATH" ]; then
    cd "$TARGET_PATH"
    echo "Changed directory to: $TARGET_PATH"
else
    echo "Error: Directory not found: $TARGET_PATH"
    exit 1
fi

# 2. Launch Docker
# "${PWD}" ensures the path is handled correctly even if it has spaces
docker run --name baremetal-c-prompt --rm -it -v "${PWD}:/student" kongkrit/baremetal-c

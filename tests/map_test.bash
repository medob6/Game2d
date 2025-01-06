#!/bin/bash

# Directory containing the map files
MAP_DIR="./maps"

# Check if the directory exists
if [ ! -d "$MAP_DIR" ]; then
    echo "Error: Maps directory not found!"
    exit 1
fi

# Loop over each .ber map file in the directory
for map_file in "$MAP_DIR"/*.ber; do
    if [ -f "$map_file" ]; then
        echo "Testing map: $map_file"
        
        # Run the solong program with the map file and capture the output
        ./solong "$map_file"
        
        # Check the exit status of the solong program
        if [ $? -eq 0 ]; then
            echo "Map $map_file: Passed"
        else
            echo "Map $map_file: Failed"
        fi
        
        echo "----------------------------"
    fi
done

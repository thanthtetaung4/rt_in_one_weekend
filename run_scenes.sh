#!/bin/bash

echo "Building ray tracer with MLX support..."
make clean && make

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful! Choose how to run scenes:"
    echo "1. Select a specific scene"
    echo "2. Run all scenes"
    echo ""
    echo "Note: Press ESC key to close the windows"
    echo ""

    read -p "Enter your choice (1 or 2): " choice

    case $choice in
        1)
            echo "Available scenes:"
            ls -1 scenes/*.rt | nl
            echo ""
            read -p "Enter scene number: " scene_num
            scene_file=$(ls scenes/*.rt | sed -n "${scene_num}p")
            if [ -n "$scene_file" ]; then
                echo "Running $scene_file..."
                ./rt "$scene_file"
            else
                echo "Invalid scene number"
                exit 1
            fi
            ;;
        2)
            echo "Running all scenes..."
            echo "Scenes will open with 2 second intervals"
            for scene in scenes/*.rt; do
                echo "Running $scene..."
                ./rt "$scene" &
                sleep 2
            done
            wait
            ;;
        *)
            echo "Invalid choice. Exiting."
            exit 1
            ;;
    esac
else
    echo "Build failed!"
    exit 1
fi

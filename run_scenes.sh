#!/bin/bash

echo "Building ray tracer with MLX support..."
make clean && make

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful! Choose which scene to run:"
    echo "1. Main scene (spheres, cylinders, plane with lighting)"
    echo "2. Box scene (closed box with objects inside)"
    echo "3. Pipe scene (camera inside infinite cylinder with floating objects)"
    echo "4. Run all scenes (will open three windows)"
    echo ""
    echo "Note: Press ESC key to close the windows"
    echo ""

    read -p "Enter your choice (1, 2, 3, or 4): " choice

    case $choice in
        1)
            echo "Running main scene..."
            ./rt
            ;;
        2)
            echo "Running box scene..."
            ./rt_box
            ;;
        3)
            echo "Running pipe scene..."
            ./rt_pipe
            ;;
        4)
            echo "Running all scenes..."
            echo "Main scene will open first, then box scene, then pipe scene"
            ./rt &
            sleep 2
            ./rt_box &
            sleep 2
            ./rt_pipe
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

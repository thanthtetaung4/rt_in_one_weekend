#!/bin/bash

echo "Building ray tracer with MLX support..."
make clean && make

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful! Choose which scene to run:"
    echo "1. Main scene (spheres, cylinders, plane with lighting)"
    echo "2. Box scene (closed box with objects inside)"
    echo "3. Run both scenes (will open two windows)"
    echo ""
    echo "Note: Press ESC key to close the windows"
    echo ""

    read -p "Enter your choice (1, 2, or 3): " choice

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
            echo "Running both scenes..."
            echo "Main scene will open first, then box scene"
            ./rt &
            sleep 2
            ./rt_box
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

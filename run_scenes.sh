#!/bin/bash

echo "Rendering original scene..."
./rt
echo "Original scene rendered as image.ppm"

echo "Rendering box scene..."
./rt_box
echo "Box scene rendered as box_scene.ppm"

echo "Both scenes have been rendered!"
echo "Files created:"
echo "  - image.ppm (original scene with ground plane)"
echo "  - box_scene.ppm (box scene with 4 black walls)"
echo ""
echo "You can view these PPM files with any image viewer that supports PPM format."

#!/bin/bash
g++ src/main.cpp src/core/Renderer.cpp \
    -Isrc \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o traffic_sim

echo "Done! Run with: ./traffic_sim"
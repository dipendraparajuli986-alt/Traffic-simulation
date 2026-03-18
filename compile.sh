#!/bin/bash
g++ src/main.cpp src/core/Renderer.cpp \
    -Isrc \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o traffic_sim

echo "Yes Boss on your servicce : To run program type -> ./traffic_sim"
#!/bin/bash

cmake --build ./build --target MyExecutable -- -o build/
valgrind --leak-check=full build/MyExecutable
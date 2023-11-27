#! /bin/bash
touch example/main.cpp; cmake -S . -B example/build; cd example/build; make; ./example "$@"; cd ../..
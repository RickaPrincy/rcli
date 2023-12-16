#! /bin/bash
cd example; cmake -S . -B build; cd build; make; ./example "$@"; cd ../..
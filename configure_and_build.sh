#! /bin/bash
cmake -DRCLI_VERSION_BUILD=ON -S . -B build; cd build; make; cd ..

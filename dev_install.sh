#! /bin/bash
cmake -DRCLI_INSTALL=ON -S . -B build
cd build; sudo make install; cd ..
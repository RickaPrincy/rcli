#! /bin/bash
sudo cmake -DRCLI_INSTALL=ON -S . -B build
cd build; make install; cd ..
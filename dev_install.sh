#! /bin/bash
sudo cmake -DRCLI_VERSION_BUILD=ON -DRCLI_INSTALL=ON -S . -B build
cd build; make install; cd ..
#! /bin/bash
git clone -b v1.5.2 http://github.com/RickaPrincy/rcli.git
cd rcli
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cd build
sudo make install
cd ../..
rm -rf rcli

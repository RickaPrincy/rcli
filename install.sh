#! /bin/bash
git clone http://github.com/RickaPrincy/rcli.git
cd rcli
cmake -DCMAKE_BUILD_TYPE=Release -DRCLI_INSTALL=ON -S . -B build
cd build
sudo make install
cd ../..
rm -rf rcli
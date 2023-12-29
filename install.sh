#! /bin/bash
git clone http://github.com/RickaPrincy/RCli.git
cd RCli
cmake -DCMAKE_BUILD_TYPE=Release -DRCLI_INSTALL=ON -S . -B build
cd build
sudo make install
cd ../..
rm -rf RCli
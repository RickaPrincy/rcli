#! /bin/bash
git clone http://github.com/RickaPrincy/RCli.git
cd RCli
sudo cmake -DRCLI_INSTALL=ON -S . -B build
cd build
make install
cd ../..
rm -rf RCli
#! /bin/bash
git clone -b v2.0.0 https://github.com/RickaPrincy/rcli.git 
cd rcli 
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
sudo make install
cd ../..
rm -rf rcli 

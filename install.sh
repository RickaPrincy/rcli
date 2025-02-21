#! /bin/bash
git clone -b 2.0.0 {{GIT_URL}} 
cd 2.0.0 
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
sudo make install
cd ../..
rm -rf rcli 

#!/bin/bash
SHA_PGKBUILD_LINE=12
release_path=()

cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cd build 
make
cd ..

mkdir -p release
cd release

create_tar_release(){
    local RELEASE_NAME="$1"
    local PKGBUILD_PATH="$2"

    # create tar release and configure hash
    tar -czvf "${RELEASE_NAME}.tar.gz" "${RELEASE_NAME}"
    hash_value=$(sha256sum "${RELEASE_NAME}.tar.gz" | awk '{print $1}')
    new_shaline="sha256sums=(\"${hash_value}\")"
    sed -i "${SHA_PGKBUILD_LINE}s/.*/${new_shaline}/" "${PKGBUILD_PATH}" 
}

create_lib_release(){

    local RELEASE_NAME=rcli@2.0.1
    release_path+=("${RELEASE_NAME}")
    
    mkdir -p "${RELEASE_NAME}"
    mkdir -p "${RELEASE_NAME}/lib"
    mkdir -p "${RELEASE_NAME}/include"
    mkdir -p "${RELEASE_NAME}/lib/cmake"
    
    cp -r ../build/lib "${RELEASE_NAME}"
    cp -r ../build/cmake "${RELEASE_NAME}/lib/cmake/rcli"
    cp -r ../include/rcli "${RELEASE_NAME}/include/rcli"

    create_tar_release "${RELEASE_NAME}" "../PKGBUILD"
}

create_lib_release

git add --all
git commit -m "release: rcli@2.0.1"
git tag -a v2.0.1 -m "rcli v2.0.1"

#!/usr/bin/env bash
# Builds every file attached to a GitHub release into dist/.
#
#   tools/package_release.sh
#
# The version comes from include/rcli/version.hpp (the same source CMake uses).
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"

version=$(sed -n 's/^#define RCLI_VERSION_\(MAJOR\|MINOR\|PATCH\) \([0-9]*\)$/\2/p' \
	include/rcli/version.hpp | paste -sd.)
name="rcli-${version}"
dist="$root/dist"
work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT

echo "packaging rcli v${version}"

# the committed single header must match include/
python3 tools/amalgamate.py --check

rm -rf "$dist"
mkdir -p "$dist"

# 1. the single header, directly downloadable
cp single_include/rcli/rcli.hpp "$dist/rcli.hpp"

# 2. single header + license
mkdir -p "$work/$name-single-header/rcli"
cp single_include/rcli/rcli.hpp "$work/$name-single-header/rcli/"
cp License.txt "$work/$name-single-header/"
(cd "$work" && zip -qr "$dist/$name-single-header.zip" "$name-single-header")

# 3. installed layout (include/ + share/cmake/ for find_package), no build needed:
#    extract it anywhere and point CMAKE_PREFIX_PATH to it
cmake -S . -B "$work/build" -DRCLI_BUILD_TESTS=OFF -DRCLI_BUILD_EXAMPLES=OFF \
	-DRCLI_INSTALL=ON >/dev/null
cmake --install "$work/build" --prefix "$work/$name" >/dev/null
cp License.txt "$work/$name/"
(cd "$work" && zip -qr "$dist/$name.zip" "$name" && tar -czf "$dist/$name.tar.gz" "$name")

(cd "$dist" && sha256sum -- * >SHA256SUMS)

echo "release files in dist/:"
(cd "$dist" && ls -1)

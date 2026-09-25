# Author: RickaPrincy <rckprincy@gmail.com>
pkgname=rcli
pkgver=2.1.0
pkgrel=1
pkgdesc="Header-only library to build command line applications in C++17"
arch=('any')
url="https://github.com/RickaPrincy/rcli"
license=('MIT')
makedepends=('cmake')
source=("$pkgname-$pkgver.tar.gz::$url/archive/refs/tags/v$pkgver.tar.gz")
# after a new release tag: updpkgsums
sha256sums=('c6e0f120547272c87ba8ccb795c73dd4c24243974f3e86d4a0e9e3da0756109e')

build() {
    cmake -S "$pkgname-$pkgver" -B build \
        -DCMAKE_INSTALL_PREFIX=/usr \
        -DRCLI_BUILD_TESTS=OFF \
        -DRCLI_BUILD_EXAMPLES=OFF \
        -DRCLI_INSTALL=ON
}

package() {
    DESTDIR="$pkgdir" cmake --install build
    install -Dm644 "$pkgname-$pkgver/License.txt" "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}

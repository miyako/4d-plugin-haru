#!/bin/bash
# Builds the static libraries the Xcode project links from a/, as universal
# (arm64 + x86_64) archives, from pinned official source releases:
#   libpng 1.6.59          -> libpng16.a  (private to libhpdf: the plugin includes no png.h)
#   libharu RELEASE_2_3_0  -> libhpdf.a   (= include/hpdf_mac.h, include/hpdf_fontdef.h; its
#                                          hpdf_version.h still says "2.3.0RC2", like the committed one;
#                                          compiled with the committed include/hpdf_config.h)
# zlib comes from the SDK (libz.tbd), so it is not built here.
#
# The committed headers in include/ are shared with the Windows build and are
# not modified. include/hpdf.h is the Windows variant (wchar_t file names);
# macOS compiles against include/hpdf_mac.h, which matches libharu 2.3.0
# apart from the Windows calling convention.
#
# usage: scripts/build-macos-deps.sh [output-dir]   (default: a/)
# WORK (default build/deps) holds downloads and builds; a rerun reuses them.
# Needs: Xcode command line tools, curl, cmake.

set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="${1:-$ROOT/a}"
case "$OUT" in /*) ;; *) OUT="$ROOT/$OUT" ;; esac
WORK="${WORK:-$ROOT/build/deps}"
MIN="${MACOSX_DEPLOYMENT_TARGET:-11.5}"
JOBS="$(sysctl -n hw.ncpu)"

PNG_URL=https://github.com/pnggroup/libpng/archive/refs/tags/v1.6.59.tar.gz
PNG_SHA=2540302a1844ad2b2b501977abecfa850f265f97b78f065a712ab4074a89f5b5
HARU_URL=https://github.com/libharu/libharu/archive/refs/tags/RELEASE_2_3_0.tar.gz
HARU_SHA=8f9e68cc5d5f7d53d1bc61a1ed876add1faf4f91070dbc360d8b259f46d9a4d2

# keep Homebrew headers and libraries out of the build
unset CPATH LIBRARY_PATH C_INCLUDE_PATH CPLUS_INCLUDE_PATH PKG_CONFIG_PATH || true
export PKG_CONFIG_LIBDIR=/nonexistent
export MACOSX_DEPLOYMENT_TARGET="$MIN"

mkdir -p "$WORK/dl" "$OUT"

# fetch <url> <sha256> <file>: download with retries, verify the checksum
fetch() {
  local f="$WORK/dl/$3" i
  if [ -f "$f" ] && echo "$2  $f" | shasum -a 256 -c - >/dev/null 2>&1; then
    return 0
  fi
  for i in 1 2 3; do
    curl -fsSL --retry 3 -o "$f.tmp" "$1" && break
    [ "$i" = 3 ] && { echo "::error::download failed: $1"; return 1; }
    echo "download $1 failed, retrying"; sleep 10
  done
  echo "$2  $f.tmp" | shasum -a 256 -c - || { echo "::error::checksum mismatch: $1"; rm -f "$f.tmp"; return 1; }
  mv "$f.tmp" "$f"
}

# unpack <archive> <dest dir>: fresh extraction into dest
unpack() {
  rm -rf "${2:?}"; mkdir -p "$2"
  tar -xzf "$WORK/dl/$1" -C "$2" --strip-components 1
}

fetch "$PNG_URL"  "$PNG_SHA"  libpng-1.6.59.tar.gz
fetch "$HARU_URL" "$HARU_SHA" libharu-2.3.0.tar.gz

PNGP="$WORK/png-prefix"

# libpng: CMake builds both archs in one pass. Hardware (NEON/SSE) code is
# off so one configuration serves both slices; libhpdf only decodes PNGs
# embedded in a PDF.
if [ ! -f "$PNGP/lib/libpng16.a" ]; then
  echo "::group::libpng"
  unpack libpng-1.6.59.tar.gz "$WORK/libpng"
  rm -rf "$WORK/libpng-build"
  cmake -S "$WORK/libpng" -B "$WORK/libpng-build" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="$PNGP" \
    -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET="$MIN" \
    -DPNG_SHARED=OFF -DPNG_STATIC=ON -DPNG_FRAMEWORK=OFF \
    -DPNG_TESTS=OFF -DPNG_TOOLS=OFF -DPNG_HARDWARE_OPTIMIZATIONS=OFF
  cmake --build "$WORK/libpng-build" -j "$JOBS"
  cmake --install "$WORK/libpng-build"
  echo "::endgroup::"
fi
cp "$PNGP/lib/libpng16.a" "$OUT/libpng16.a"

# libharu: its 2.3.0 CMake files predate current CMake, so compile src/*.c
# directly (clang emits fat objects; Apple's libtool archives them), with the
# committed hpdf_config.h (LIBHPDF_HAVE_LIBPNG, LIBHPDF_HAVE_LIBZ).
if [ ! -f "$WORK/libharu-build/libhpdf.a" ]; then
  echo "::group::libharu"
  unpack libharu-2.3.0.tar.gz "$WORK/libharu"
  cp "$ROOT/include/hpdf_config.h" "$WORK/libharu/include/hpdf_config.h"
  rm -rf "$WORK/libharu-build"; mkdir -p "$WORK/libharu-build"
  for f in "$WORK"/libharu/src/*.c; do
    clang -arch arm64 -arch x86_64 -mmacosx-version-min="$MIN" -O2 -DNDEBUG -fPIC \
      -Werror=implicit-function-declaration -Werror=implicit-int \
      -I"$WORK/libharu/include" -I"$PNGP/include" \
      -c "$f" -o "$WORK/libharu-build/$(basename "${f%.c}").o"
  done
  libtool -static -o "$WORK/libharu-build/libhpdf.a" "$WORK"/libharu-build/*.o
  echo "::endgroup::"
fi
cp "$WORK/libharu-build/libhpdf.a" "$OUT/libhpdf.a"

# every output must carry both slices
for L in libpng16 libhpdf; do
  for A in arm64 x86_64; do
    lipo "$OUT/$L.a" -verify_arch "$A" || { echo "::error::$L.a lacks $A"; exit 1; }
  done
  echo "$L.a: $(lipo -archs "$OUT/$L.a")"
done

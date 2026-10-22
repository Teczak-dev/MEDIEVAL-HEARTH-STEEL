#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MODE="${1:-debug}"

case "$MODE" in
  debug)
    CONFIG="debug_arm64"
    OUTPUT="$ROOT_DIR/bin/Debug/MedievalHearthSteel"
    ;;
  release)
    CONFIG="release_arm64"
    OUTPUT="$ROOT_DIR/bin/Release/MedievalHearthSteel"
    ;;
  clean)
    make -C "$ROOT_DIR" clean config=debug_arm64
    make -C "$ROOT_DIR" clean config=release_arm64
    exit 0
    ;;
  *)
    printf 'Usage: %s [debug|release|clean]\n' "$0" >&2
    exit 2
    ;;
esac

make -C "$ROOT_DIR" clean config="$CONFIG"
(
  cd "$ROOT_DIR/build"
  ./premake5.osx gmake
  ./premake5.osx ecc
)
make -C "$ROOT_DIR" config="$CONFIG" -j"$(sysctl -n hw.logicalcpu)"

printf 'Built %s: %s\n' "$MODE" "$OUTPUT"

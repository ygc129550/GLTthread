#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"

usage() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  clean          Remove build directory and exit"
    echo "  --static       Build static library"
    echo "  --shared       Build shared library"
    echo "  --tests        Build test programs"
    echo "  --all          Build everything (default when no target specified)"
    echo "  -h, --help     Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                  # Build all (default)"
    echo "  $0 --static         # Static library only"
    echo "  $0 --shared --tests # Shared library + tests"
    echo "  $0 clean            # Clean build directory"
}

DO_CLEAN=false
HAS_TARGET=false
BUILD_STATIC=OFF
BUILD_SHARED=OFF
BUILD_TESTS=OFF

# First pass: parse all arguments
for arg in "$@"; do
    case "$arg" in
        clean)    DO_CLEAN=true ;;
        --static) HAS_TARGET=true; BUILD_STATIC=ON ;;
        --shared) HAS_TARGET=true; BUILD_SHARED=ON ;;
        --tests)  HAS_TARGET=true; BUILD_TESTS=ON ;;
        --all)    HAS_TARGET=true; BUILD_STATIC=ON; BUILD_SHARED=ON; BUILD_TESTS=ON ;;
        -h|--help) usage; exit 0 ;;
        *) echo "Unknown option: $arg"; usage; exit 1 ;;
    esac
done

# Default to all if no target specified
if ! $HAS_TARGET; then
    BUILD_STATIC=ON
    BUILD_SHARED=ON
    BUILD_TESTS=ON
fi

if $DO_CLEAN; then
    echo "==> Cleaning build directory..."
    rm -rf "${BUILD_DIR}"
    echo "==> Done."
    exit 0
fi

echo "==> Configuring (static=${BUILD_STATIC}, shared=${BUILD_SHARED}, tests=${BUILD_TESTS})..."
cmake -S "${SCRIPT_DIR}" -B "${BUILD_DIR}" \
    -DGLUEDS_BUILD_STATIC="${BUILD_STATIC}" \
    -DGLUEDS_BUILD_SHARED="${BUILD_SHARED}" \
    -DGLUEDS_BUILD_TESTS="${BUILD_TESTS}"

echo "==> Building (parallel)..."
cmake --build "${BUILD_DIR}" -j "$(nproc)"

echo ""
echo "==> Build complete. Outputs in ${BUILD_DIR}"

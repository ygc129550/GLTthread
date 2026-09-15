#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"

echo "==> Configuring..."
cmake -S "${SCRIPT_DIR}" -B "${BUILD_DIR}"

echo "==> Building..."
cmake --build "${BUILD_DIR}"

echo "==> Done. Binary: ${BUILD_DIR}/glthread_test"

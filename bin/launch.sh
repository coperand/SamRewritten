#!/bin/bash

SCRIPT_PATH=$(dirname "$(realpath "$0")")
export LD_LIBRARY_PATH=${SCRIPT_PATH}

# Workaround waiting for a fix https://github.com/lloyd/yajl/issues/222
export LC_NUMERIC=en_US.UTF-8

cd "${SCRIPT_PATH}"/..
"${SCRIPT_PATH}"/samrewritten "$@"

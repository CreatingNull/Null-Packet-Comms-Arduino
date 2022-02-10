#!/bin/sh
# Put required C code for testing on path
# Call using source env.sh
# Not required in workflow execution.
# ========================================================

export CPLUS_INCLUDE_PATH="${PWD}/googletest/googletest/include/"
export LIBRARY_PATH="${PWD}/googletest/googletest/"

# ========================================================

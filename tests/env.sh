# Put required C code for testing on path
# ========================================================

GTEST_INCLUDE="${PWD}/googletest/googletest/include/"
GTEST_LIB="${PWD}/googletest/googletest/"

# ========================================================

export CPLUS_INCLUDE_PATH="$GTEST_INCLUDE"
export LIBRARY_PATH="$GTEST_LIB:$LIBRARY_PATH"

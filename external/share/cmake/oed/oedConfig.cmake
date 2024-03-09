cmake_minimum_required(VERSION 3.5)
project(oed LANGUAGES C CXX Fortran)

# include("${CMAKE_CURRENT_LIST_DIR}/OEDTargets.cmake")

# Set the include directory
set(OED_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../include")

# Set the library path
set(OED_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/../../../lib/liboed.a")

# You can set this if you want to make it easy to link to the library
set(OED_LIBRARIES "${OED_LIBRARY}")
set(OED_INCLUDE_DIRS "${OED_INCLUDE_DIR}")

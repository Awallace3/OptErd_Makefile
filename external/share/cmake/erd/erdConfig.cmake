cmake_minimum_required(VERSION 3.5)
project(erd LANGUAGES C CXX Fortran)

# include("${CMAKE_CURRENT_LIST_DIR}/CIntTargets.cmake")

# Set the include directory
set(ERD_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../include")

# Set the library path
set(ERD_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/../../../lib/liberd.a")

# You can set this if you want to make it easy to link to the library
set(ERD_LIBRARIES "${ERD_LIBRARY}")
set(ERD_INCLUDE_DIRS "${ERD_INCLUDE_DIR}")

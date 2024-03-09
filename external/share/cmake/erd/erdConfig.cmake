cmake_minimum_required(VERSION 3.5)
project(erd LANGUAGES C CXX Fortran)

# include("${CMAKE_CURRENT_LIST_DIR}/CIntTargets.cmake")

# Set the include directory
set(CInt_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../include")

# Set the library path
set(CInt_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/../../../lib/liberd.a")

# You can set this if you want to make it easy to link to the library
set(CInt_LIBRARIES "${ERD_LIBRARY}")
set(CInt_INCLUDE_DIRS "${ERD_INCLUDE_DIR}")
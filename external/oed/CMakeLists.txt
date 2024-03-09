cmake_minimum_required(VERSION 3.10)
project(OEDLibrary LANGUAGES C Fortran)

# Collect Fortran and C source files
file(GLOB SRC "*.f" "*.F" "*.c")

# Set the output library name based on the architecture
set(arch "default" CACHE STRING "Choose the architecture: mic or default")
if(arch STREQUAL "mic")
    # For "mic" architecture, output files are prefixed with "mic/"
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "mic")
endif()

# Compiler flags
set(CMAKE_Fortran_FLAGS "${FFLAGS}")
set(CMAKE_C_FLAGS "${CFLAGS}")

# Create a static library from the source files
add_library(oed STATIC ${SRC})
set_target_properties(oed PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "../../lib")

# Post-build command to copy the library to a different directory
add_custom_command(TARGET oed POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:oed> ${CMAKE_SOURCE_DIR}/../../lib)

# Clean extra files (Note: CMake's clean target generally handles cleaning up most build artifacts)
set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "*.o;*~;*.a")



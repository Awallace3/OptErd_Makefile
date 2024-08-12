cmake_minimum_required(VERSION 3.10)
project(ERDLibrary LANGUAGES C Fortran)

# Collect source files
file(GLOB SRC "*.c" "*.f" "*.F")

# Set compiler flags
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CFLAGS} -D__ALIGNLEN__=${alignlen} -O3 --std=gnu99 -fopenmp -fPIC")
elseif (CMAKE_C_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_C_FLAGS "${CFLAGS} -D__ALIGNLEN__=${alignlen} -O3 -qopenmp -fPIC")
endif()
set(CMAKE_Fortran_FLAGS "${FFLAGS}")

# Option for architecture, default to non-MIC
set(arch "default" CACHE STRING "Choose the architecture: mic or default")

if(arch STREQUAL "mic")
    set(ERDLIB "liberd_mic.a")
    # Special handling for MIC architecture sources
    # Note: This approach assumes the MIC-specific sources will be compiled separately
    # Adjust as necessary for your project's structure and requirements
    set(OBJ_DIR "mic")
    foreach(SRC_FILE IN LISTS SRC)
        get_filename_component(SRC_NAME ${SRC_FILE} NAME)
        set_property(SOURCE ${SRC_FILE} PROPERTY OBJECT_OUTPUTS "mic/${SRC_NAME}.o")
    endforeach()
else()
    set(ERDLIB "liberd.a")
    set(OBJ_DIR ".")
endif()

# Create a static library from sources
add_library(erd STATIC ${SRC})
set_target_properties(erd PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "../../lib")

# Custom command to copy erd_profile.h after build
add_custom_command(TARGET erd POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/erd_profile.h" "${CMAKE_CURRENT_SOURCE_DIR}/../../include")

# Handling clean
set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${OBJ_DIR}/*.o;*~;*.a")

# Specify the public headers for the libcint library
file(GLOB PUBLIC_HEADERS "*.h")

# Define where to install the headers
install(FILES ${PUBLIC_HEADERS} DESTINATION include)

install(TARGETS erd
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

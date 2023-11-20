cmake_minimum_required(VERSION 3.25)
project(kohibc LANGUAGES C CXX)
include(GNUInstallDirs)

# Options
option(KOHI_USE_VOLK_LOADER "Use VOLK Meta loader" OFF)
message("KOHI_USE_VOLK_LOADER: ${KOHI_USE_VOLK_LOADER}")

# Settings
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# Global compiler settings
# if(MSVC)
#     add_compile_options(/Zc:preprocessor) # for __VA_ARGS__ handling
# endif()

add_subdirectory(external)
add_subdirectory(engine)
add_subdirectory(testbed)
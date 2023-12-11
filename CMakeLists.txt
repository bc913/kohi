cmake_minimum_required(VERSION 3.25)
project(kohibc LANGUAGES C)

# ---------
# Options
# ---------
option(KOHI_USE_VOLK_LOADER "Use VOLK Meta loader" OFF)
message("KOHI_USE_VOLK_LOADER: ${KOHI_USE_VOLK_LOADER}")

option(AUTO_LOCATE_VULKAN "Attempting to auto locate vulkan using CMake FindVulkan ..." ON)
message(STATUS "AUTO_LOCATE_VULKAN: ${AUTO_LOCATE_VULKAN}")

# ---------
# Includes
# ---------
## Cmake
include(GNUInstallDirs)
## Custom
set(KOHI_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${KOHI_MODULE_PATH} ${CMAKE_MODULE_PATH})
include(HandleVulkanDeps)
include(ResourcesFunctions)

# ---------------
# CMAKE Settings
# ---------------
set(CMAKE_C_STANDARD 17)
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
#set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# ---------------
# Global compiler settings
# ---------------
# if(MSVC)
#     add_compile_options(/Zc:preprocessor) # for __VA_ARGS__ handling
# endif()

# ---------------
# Projects
# ---------------
#add_subdirectory(external)
add_subdirectory(engine)
add_subdirectory(testbed)
add_subdirectory(tests)
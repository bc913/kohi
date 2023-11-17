project(kohi_engine LANGUAGES C)
add_library(${PROJECT_NAME} SHARED "")

# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks
# https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html
# $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:
    #     src/platform/platform_win32.c
    # >


# https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:COMPILE_LANGUAGE
# ----------
# Core
# ----------

if(UNIX)
    find_package(X11 REQUIRED) # FindX11
endif()

set(_CORE_HEADER_FILES)
list(APPEND _CORE_HEADER_FILES
        src/core/logger.h
        src/core/asserts.h
        src/core/application.h
        src/core/kmemory.h
        src/core/event.h
        src/core/input.h
)

set(_CORE_SOURCE_FILES)
list(APPEND _CORE_SOURCE_FILES
    src/core/logger.c
    src/core/application.c
    src/core/kmemory.c
    src/core/event.c
    src/core/input.c
)

# ----------
# Platform
# ----------
set(_PLATFORM_HEADER_FILES)
list(APPEND _PLATFORM_HEADER_FILES
    src/platform/platform.h
)
set(_PLATFORM_SOURCE_FILES)
list(APPEND _PLATFORM_SOURCE_FILES
    src/platform/platform_win32.c
    src/platform/platform_linux.c
)

# ----------
# Containers
# ----------
set(_CONTAINERS_HEADER_FILES)
list(APPEND _CONTAINERS_HEADER_FILES
    src/containers/darray.h
)

set(_CONTAINERS_SOURCE_FILES)
list(APPEND _CONTAINERS_SOURCE_FILES
    src/containers/darray.c
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${_CORE_SOURCE_FILES}
        ${_PLATFORM_SOURCE_FILES}
        ${_CONTAINERS_SOURCE_FILES}
    PUBLIC
        FILE_SET ${PROJECT_NAME}_header_files 
        TYPE HEADERS
        BASE_DIRS src
        FILES
            src/defines.h
            src/entry.h
            src/game_types.h
            ${_CORE_HEADER_FILES}
            ${_PLATFORM_HEADER_FILES}
            ${_CONTAINERS_HEADER_FILES}
)

# ----------
# Definitions
# ----------

target_link_libraries(${PROJECT_NAME} 
                            PRIVATE
                                Vulkan::Headers
                                $<$<PLATFORM_ID:Linux>:
                                    xcb
                                    X11
                                    X11-xcb
                                    # ${X11_LIBRARIES} xcb # to stay in the safe side
                                >
)
message(STATUS "Vulkan Headers Version: ${VulkanHeaders_VERSION}")

target_compile_definitions(
    ${PROJECT_NAME} 
    PUBLIC 
        KEXPORT
    PRIVATE
        $<$<PLATFORM_ID:Linux>: _POSIX_C_SOURCE=199309L> # CLOCK_MONOTONIC
    #     $<$<PLATFORM_ID:Windows>: KPLATFORM_WINDOWS> # not required since 
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET ${PROJECT_NAME}_header_files DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
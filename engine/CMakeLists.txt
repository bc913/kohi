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
        src/core/kstring.h
        src/core/clock.h
)

set(_CORE_SOURCE_FILES)
list(APPEND _CORE_SOURCE_FILES
    src/core/logger.c
    src/core/application.c
    src/core/kmemory.c
    src/core/event.c
    src/core/input.c
    src/core/kstring.c
    src/core/clock.c
)

# ----------
# Platform
# ----------
set(_PLATFORM_HEADER_FILES)
list(APPEND _PLATFORM_HEADER_FILES
    src/platform/platform.h
    src/platform/filesystem.h
)
set(_PLATFORM_SOURCE_FILES)
list(APPEND _PLATFORM_SOURCE_FILES
    src/platform/platform_win32.c
    src/platform/platform_linux.c
    src/platform/platform_macos.m
    src/platform/platform_macos.c
    src/platform/filesystem.c
)

# ----------
# Renderer
# ----------
set(_RENDERER_HEADER_FILES)
list(APPEND _RENDERER_HEADER_FILES
    src/renderer/renderer_types.inl
    src/renderer/renderer_frontend.h
    src/renderer/renderer_backend.h
)

set(_RENDERER_SOURCE_FILES)
list(APPEND _RENDERER_SOURCE_FILES
    src/renderer/renderer_backend.c
    src/renderer/renderer_frontend.c
)

# Vulkan
set(_RENDERER_VULKAN_HEADER_FILES)
list(APPEND _RENDERER_VULKAN_HEADER_FILES
    src/renderer/vulkan/vulkan_backend.h
    src/renderer/vulkan/vulkan_types.inl
    src/renderer/vulkan/vulkan_platform.h
    src/renderer/vulkan/vulkan_device.h
    src/renderer/vulkan/vulkan_swapchain.h
    src/renderer/vulkan/vulkan_image.h
    src/renderer/vulkan/vulkan_renderpass.h
    src/renderer/vulkan/vulkan_command_buffer.h
    src/renderer/vulkan/vulkan_framebuffer.h
    src/renderer/vulkan/vulkan_fence.h
    src/renderer/vulkan/vulkan_utils.h
    src/renderer/vulkan/vulkan_shader_utils.h
    src/renderer/vulkan/shaders/vulkan_object_shader.h
    src/renderer/vulkan/vulkan_pipeline.h
    src/renderer/vulkan/vulkan_buffer.h
)
set(_RENDERER_VULKAN_SOURCE_FILES)
list(APPEND _RENDERER_VULKAN_SOURCE_FILES
    src/renderer/vulkan/vulkan_backend.c
    src/renderer/vulkan/vulkan_device.c
    src/renderer/vulkan/vulkan_swapchain.c
    src/renderer/vulkan/vulkan_image.c
    src/renderer/vulkan/vulkan_renderpass.c
    src/renderer/vulkan/vulkan_command_buffer.c
    src/renderer/vulkan/vulkan_framebuffer.c
    src/renderer/vulkan/vulkan_fence.c
    src/renderer/vulkan/vulkan_utils.c
    src/renderer/vulkan/vulkan_shader_utils.c
    src/renderer/vulkan/shaders/vulkan_object_shader.c
    src/renderer/vulkan/vulkan_pipeline.c
    src/renderer/vulkan/vulkan_buffer.c
)

# TODO: Based on selected renderer backend use cmake generator expressions here
# Send renderers together
list(APPEND _RENDERER_HEADER_FILES ${_RENDERER_VULKAN_HEADER_FILES})
list(APPEND _RENDERER_SOURCE_FILES ${_RENDERER_VULKAN_SOURCE_FILES})

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

# ----------
# Math
# ----------
set(_MATH_HEADER_FILES)
list(APPEND _MATH_HEADER_FILES
    src/math/kmath.h
    src/math/math_types.h
)

set(_MATH_SOURCE_FILES)
list(APPEND _MATH_SOURCE_FILES
    src/math/kmath.c
)

# ----------
# Memory
# ----------
set(_MEMORY_HEADER_FILES)
list(APPEND _MEMORY_HEADER_FILES
    src/memory/linear_allocator.h
)

set(_MEMORY_SOURCE_FILES)
list(APPEND _MEMORY_SOURCE_FILES
    src/memory/linear_allocator.c
)

# ----------
# Resources
# ----------
set(_RESOURCES_HEADER_FILES)
list(APPEND _RESOURCES_HEADER_FILES
    src/resources/resource_types.h
)

# ----------
# Vendor
# ----------
set(_VENDOR_HEADER_FILES)
list(APPEND _VENDOR_HEADER_FILES
    src/vendor/stb_image.h
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${_CORE_SOURCE_FILES}
        ${_PLATFORM_SOURCE_FILES}
        ${_RENDERER_SOURCE_FILES}
        ${_CONTAINERS_SOURCE_FILES}
        ${_MATH_SOURCE_FILES}
        ${_MEMORY_SOURCE_FILES}
        ${_FILESYSTEM_SOURCE_FILES}
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
            ${_RENDERER_HEADER_FILES}
            ${_CONTAINERS_HEADER_FILES}
            ${_MATH_HEADER_FILES}
            ${_MEMORY_HEADER_FILES}
            ${_FILESYSTEM_HEADER_FILES}
            ${_RESOURCES_HEADER_FILES}
            ${_VENDOR_HEADER_FILES}
)

# ----------
# Definitions
# ----------
set(_EXTERNAL_INCLUDE_DIRS)
list(APPEND _EXTERNAL_INCLUDE_DIRS
    PRIVATE
        $<$<BOOL:${AUTO_LOCATE_VULKAN}>:${Vulkan_INCLUDE_DIR}>
)
target_include_directories(${PROJECT_NAME} ${_EXTERNAL_INCLUDE_DIRS})

set(_EXTERNAL_LIBRARIES)
list(APPEND _EXTERNAL_LIBRARIES
    PRIVATE
        $<$<BOOL:${AUTO_LOCATE_VULKAN}>:${Vulkan_LIBRARIES}>
        $<$<PLATFORM_ID:Linux>:
                            xcb
                            X11
                            X11-xcb
                            # ${X11_LIBRARIES} xcb # to stay in the safe side
        >
)
target_link_libraries(${PROJECT_NAME} ${_EXTERNAL_LIBRARIES})


target_compile_definitions(
    ${PROJECT_NAME} 
    PUBLIC 
        KEXPORT
    PRIVATE
        $<$<PLATFORM_ID:Linux>: _POSIX_C_SOURCE=199309L> # CLOCK_MONOTONIC
    #     $<$<PLATFORM_ID:Windows>: KPLATFORM_WINDOWS> # not required since 
)

# ----------
# Pre-Build
# ----------
GENERATE_TEXTURE_TARGET(${PROJECT_NAME})

# ----------
# Post-Build
# ----------
APPEND_GLSL_TO_TARGET(${PROJECT_NAME})

# ----------
# Install
# ----------
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET ${PROJECT_NAME}_header_files DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
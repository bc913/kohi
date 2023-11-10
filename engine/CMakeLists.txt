project(kohi_engine)

add_library(${PROJECT_NAME} SHARED "")

# Core
set(_CORE_HEADER_FILES)
list(APPEND _CORE_HEADER_FILES
        src/core/logger.h
        src/core/asserts.h
)

set(_CORE_SOURCE_FILES)
list(APPEND _CORE_SOURCE_FILES
    src/core/logger.c
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${_CORE_SOURCE_FILES}
    PUBLIC
        FILE_SET ${PROJECT_NAME}_header_files 
        TYPE HEADERS
        BASE_DIRS src
        FILES
            src/defines.h 
            ${_CORE_HEADER_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Headers)
message(STATUS "Vulkan Headers Version: ${VulkanHeaders_VERSION}")

target_compile_definitions(
    ${PROJECT_NAME} 
    PUBLIC "KEXPORT"
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET ${PROJECT_NAME}_header_files DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
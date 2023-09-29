project(kohi_engine)

add_library(${PROJECT_NAME} SHARED "")

target_sources(${PROJECT_NAME}
    PRIVATE
        src/test.c
    PUBLIC
        FILE_SET ${PROJECT_NAME}_header_files 
        TYPE HEADERS
        BASE_DIRS src
        FILES
            src/defines.h
            src/test.h
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
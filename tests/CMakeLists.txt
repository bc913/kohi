project(kohi_tests)
add_executable(${PROJECT_NAME} "")

#--------------------
# Files
#--------------------
set(_TESTS_HEADER_FILES)
list(APPEND _TESTS_HEADER_FILES
    src/expect.h
    src/test_manager.h
)

set(_TESTS_SOURCE_FILES)
list(APPEND _TESTS_SOURCE_FILES
    src/main.c
    src/test_manager.c
)

set(_MEMORY_TESTS_HEADER_FILES)
list(APPEND _MEMORY_TESTS_HEADER_FILES
    src/memory/linear_allocator_tests.h
)

set(_MEMORY_TESTS_SOURCE_FILES)
list(APPEND _MEMORY_TESTS_SOURCE_FILES
    src/memory/linear_allocator_tests.c
)

target_sources(${PROJECT_NAME} 
                    PRIVATE
                        ${_TESTS_SOURCE_FILES}
                        ${_MEMORY_TESTS_SOURCE_FILES}
                    PUBLIC
                        FILE_SET ${PROJECT_NAME}_header_files 
                        TYPE HEADERS
                        BASE_DIRS src
                        FILES
                            ${_TESTS_HEADER_FILES}
                            ${_MEMORY_TESTS_HEADER_FILES}
)

#--------------------
# Dependents
#--------------------
set(_SHARED_LIBS)
list(APPEND _SHARED_LIBS kohi_engine)
target_link_libraries(${PROJECT_NAME} PRIVATE ${_SHARED_LIBS})

# copy the .dll file to the same folder as the executable
if(WIN32) 
    foreach(shared_lib ${_SHARED_LIBS})
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND
                ${CMAKE_COMMAND} -E copy_directory
                $<TARGET_FILE_DIR:${shared_lib}>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM
        )
    endforeach()
endif()


install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET ${PROJECT_NAME}_header_files DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
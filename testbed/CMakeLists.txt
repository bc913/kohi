project(kohi_testbed)
add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PRIVATE src/main.c)

# Dependent shared libs
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
    #PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
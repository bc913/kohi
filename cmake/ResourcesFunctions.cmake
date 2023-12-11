# Generate target for textures to be copied
macro(GENERATE_TEXTURE_TARGET dep_target)
    set(_TEXTURES_RELATIVE_DIR "assets/textures")
    set(_TEXTURE_FILES_FULL_PATH "${CMAKE_SOURCE_DIR}/${_TEXTURES_RELATIVE_DIR}")

    if(EXISTS ${_TEXTURE_FILES_FULL_PATH})

        set(_TEXTURE_FILE_LIST)
        file(GLOB_RECURSE _TEXTURE_FILES "${_TEXTURE_FILES_FULL_PATH}/*.*")
        foreach(texture_file ${_TEXTURE_FILES})
            # TExture files can be copied into project (target) binary dir first
            # as done in APPEND_GLSL_TO_TARGET macro
            list(APPEND _TEXTURE_FILE_LIST ${texture_file})
        endforeach()
        
        add_custom_target(Textures DEPENDS ${_TEXTURE_FILE_LIST})
        add_dependencies(${dep_target} Textures)
        # Copy shader files to target location
        add_custom_command(
            TARGET ${dep_target} 
            PRE_BUILD
            COMMENT "Copying texture files ..."
            COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${dep_target}>/${_TEXTURES_RELATIVE_DIR}
	        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${_TEXTURE_FILES_FULL_PATH}
                $<TARGET_FILE_DIR:${dep_target}>/${_TEXTURES_RELATIVE_DIR}
            VERBATIM
        )

    endif()
endmacro()
if(AUTO_LOCATE_VULKAN)
    # Find package first
    find_package(Vulkan GLOBAL)
    if(NOT Vulkan_FOUND)
        message(FATAL_ERROR "Vulkan SDK NOT found.")
    else()
        message(STATUS "Vulkan SDK ${Vulkan_VERSION} found.")
    endif()
    # Handle shader modules
else()
    message(FATAL_ERROR "Vulkan dependency should be handled to proceed!!!")
endif()
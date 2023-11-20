include(FetchContent)
# --------------------------------
# Dependencies
# --------------------------------

if(${KOHI_USE_VOLK_LOADER})
    FetchContent_Declare(
            vulkan_headers 
            GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git 
            GIT_TAG 85c2334e92e215cce34e8e0ed8b2dce4700f4a50 #sdk-1.3.261.1
    )

    set(VOLK_HEADERS_ONLY ON CACHE BOOL "" FORCE)
    set(VOLK_PULL_IN_VULKAN OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        volk
        GIT_REPOSITORY https://github.com/zeux/volk.git 
        GIT_TAG b3bc21e584f97400b6884cb2a541a56c6a5ddba3 #sdk-1.3.250
    )
    FetchContent_MakeAvailable(volk)
    FetchContent_MakeAvailable(vulkan_headers)
endif()

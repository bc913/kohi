include(FetchContent)

FetchContent_Declare(
        vulkan_headers 
        GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git 
        GIT_TAG 85c2334e92e215cce34e8e0ed8b2dce4700f4a50 #sdk-1.3.261.1
)
FetchContent_MakeAvailable(vulkan_headers)
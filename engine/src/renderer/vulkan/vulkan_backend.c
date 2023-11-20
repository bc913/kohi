#include "vulkan_backend.h"

#include "vulkan_types.inl"

#include "core/logger.h"

// static Vulkan context
static vulkan_context context;

#ifdef K_USE_VOLK_LOADER
b8 initialize_volk() {
    /* This won't compile if the appropriate Vulkan platform define isn't set. */
    void* ptr =
#if defined(_WIN32)
        &vkCreateWin32SurfaceKHR;
#elif defined(__linux__) || defined(__unix__)
        &vkCreateXlibSurfaceKHR;
#elif defined(__APPLE__)
        &vkCreateMacOSSurfaceMVK;
#else
        /* Platform not recogized for testing. */
        NULL;
#endif

    /* Try to initialize volk. This might not work on CI builds, but the
     * above should have compiled at least. */
    VkResult r = volkInitialize();
    if (r != VK_SUCCESS) {
        return FALSE;
    }

    uint32_t version = volkGetInstanceVersion();
    KINFO("Vulkan version %d.%d.%d initialized.",
          VK_VERSION_MAJOR(version),
          VK_VERSION_MINOR(version),
          VK_VERSION_PATCH(version));

    return TRUE;
}
#endif

b8 vulkan_renderer_backend_initialize(renderer_backend* backend, const char* application_name, struct platform_state* plat_state) {
#ifdef K_USE_VOLK_LOADER
    if (!initialize_volk()) {
        KERROR("volk Initialization failed:");
        return FALSE;
    }
#endif

    // TODO: custom allocator.
    context.allocator = 0;

    // Setup Vulkan instance.
    VkApplicationInfo app_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    app_info.apiVersion = VK_API_VERSION_1_2;
    app_info.pApplicationName = application_name;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Kohi Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = 0;
    create_info.ppEnabledExtensionNames = 0;
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = 0;

    VkResult result = vkCreateInstance(&create_info, context.allocator, &context.instance);
    if (result != VK_SUCCESS) {
        KERROR("vkCreateInstance failed with result: %u", result);
        return FALSE;
    }

#ifdef K_USE_VOLK_LOADER
    volkLoadInstance(context.instance);
#endif

    KINFO("Vulkan renderer initialized successfully.");
    return TRUE;
}

void vulkan_renderer_backend_shutdown(renderer_backend* backend) {
}

void vulkan_renderer_backend_on_resized(renderer_backend* backend, u16 width, u16 height) {
}

b8 vulkan_renderer_backend_begin_frame(renderer_backend* backend, f32 delta_time) {
    return TRUE;
}

b8 vulkan_renderer_backend_end_frame(renderer_backend* backend, f32 delta_time) {
    return TRUE;
}
//
//  Renderer.hpp
//  Nevsky Engine
//
//  Created by Дмитрий Логинов on 12.05.2022.
//

#ifndef HelloTriangle_hpp
#define HelloTriangle_hpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class VkRenderer{
public:
    void Run();
    
private:
    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    
    void initWindow();
    void initVulkan();
    void createInstance();
    void setupDebugMessenger();
    
    void mainLoop();
    void cleanup();
    
    bool checkValidationLayerSupport();
    bool checkExtensionsSupport();
    std::vector<const char*> getRequiredExtensions();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                        void* pUserData);
    
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);
    
    static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                              VkDebugUtilsMessengerEXT debugMessenger,
                                              const VkAllocationCallbacks* pAllocator);
  
    static void populateDebugMessangerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
};

#endif

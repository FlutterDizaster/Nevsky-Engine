//
//  HelloTriangle.cpp
//  Nevsky Engine
//
//  Created by Дмитрий Логинов on 12.05.2022.
//

#include "VkRenderer.hpp"

void VkRenderer::Run(){
//    if (!glfwVulkanSupported()) {
//        throw std::runtime_error("Vulkan is not supported on this hardware");
//    }
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void VkRenderer::initWindow(){
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "Nevsky Engine", nullptr, nullptr);
}

void VkRenderer::initVulkan(){
    createInstance();
    setupDebugMessenger();
}

void VkRenderer::createInstance(){
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("Validation layer requested, but not available!");
    }
    
    VkApplicationInfo appInfo{}; // app info required for creating Vk instance
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Nevsky Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{}; // Instance create info also required
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtensions();
    
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
        
        populateDebugMessangerCreateInfo(debugCreateInfo);
        createInfo.pNext= (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    }
    else{
        createInfo.enabledLayerCount = 0;
        
        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

bool VkRenderer::checkValidationLayerSupport(){
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr); //get validation layers count
    
    std::vector<VkLayerProperties> availableLayers(layerCount); //alloc memory for layers list
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data()); //get available validation layers
    
    //check
    for (const char* layerName : validationLayers){
        bool layerFound = false;
        for (const auto& layerProperties : availableLayers){
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            std::cerr << "Validation layer is unavailable: \n\t" << layerName << std::endl;
            return false;
        }
    }
    return true;
}

std::vector<const char*> VkRenderer::getRequiredExtensions(){
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); // get list of extensions req for ...
    
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    
    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    
    return extensions;
}

bool VkRenderer::checkExtensionsSupport(){
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr); //get number of supported extensions
    
    std::vector<VkExtensionProperties> extensions(extensionCount); //alloc memory for extensions list
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()); //get supported extensions
    
    std::cout << "Avaliable extensions: " << std::endl;
    for(const auto& extension : extensions){
        std::cout << "\t" << extension.extensionName << " - version: " << extension.specVersion << std::endl;
    }
    
    return true;
}

void VkRenderer::mainLoop(){
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void VkRenderer::cleanup(){
    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
    
    vkDestroyInstance(instance, nullptr);
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

VKAPI_ATTR VkBool32 VKAPI_CALL VkRenderer::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                    void* pUserData){
    std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
    
    return VK_FALSE;
};

VkResult VkRenderer::CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                      const VkAllocationCallbacks* pAllocator,
                                      VkDebugUtilsMessengerEXT* pDebugMessenger){
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
}

void VkRenderer::setupDebugMessenger(){
    if (!enableValidationLayers) {
        return;
    }
    
    VkDebugUtilsMessengerCreateInfoEXT createInfo {};
    populateDebugMessangerCreateInfo(createInfo);
    
    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void VkRenderer::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

void VkRenderer::populateDebugMessangerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo){
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr; //optional
}

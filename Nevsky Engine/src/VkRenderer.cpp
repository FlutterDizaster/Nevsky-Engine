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
}

void VkRenderer::createInstance(){
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Nevsky Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void VkRenderer::mainLoop(){
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void VkRenderer::cleanup(){
    vkDestroyInstance(instance, nullptr);
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

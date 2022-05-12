//
//  HelloTriangle.cpp
//  Nevsky Engine
//
//  Created by Дмитрий Логинов on 12.05.2022.
//

#include "HelloTriangle.hpp"

void HelloTriangle::Run(){
    if (glfwVulkanSupported()) {
        std::cout << "Vulkan supported!" << std::endl;
    }
    else{
        std::cout << glfwVulkanSupported() << std::endl;
        throw std::runtime_error("Vulkan is not supported on this hardware");
    }
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void HelloTriangle::initWindow(){
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "Nevsky Engine", nullptr, nullptr);
}

void HelloTriangle::initVulkan(){
    createInstance();
}

void HelloTriangle::createInstance(){
    VkApplicationInfo appInfo {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Learning GLFW + VK",
        .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
        .pEngineName = "Nevsky Engine",
        .engineVersion = VK_MAKE_VERSION(0, 0, 1),
        .apiVersion = VK_API_VERSION_1_0
    };
    
    VkInstanceCreateInfo createInfo {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo
    };
    
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    std::cout << "Vk extension count: " << glfwExtensionCount << std::endl;
    std::cout << "Vk extensions: " << glfwExtensions << std::endl;
    
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
    
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Faild to create Vk instance");
    }
}

void HelloTriangle::mainLoop(){
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void HelloTriangle::cleanup(){
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

//
//  HelloTriangle.hpp
//  Nevsky Engine
//
//  Created by Дмитрий Логинов on 12.05.2022.
//

#ifndef HelloTriangle_hpp
#define HelloTriangle_hpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

class HelloTriangle{
public:
    void Run();
    
private:
    GLFWwindow* window;
    VkInstance instance;
    
    void initWindow();
    void initVulkan();
    void createInstance();
    void mainLoop();
    void cleanup();
};

#endif /* HelloTriangle_hpp */

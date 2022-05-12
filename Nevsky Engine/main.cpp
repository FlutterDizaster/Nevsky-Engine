//
//  main.cpp
//  Nevsky Engine
//
//  Created by Дмитрий Логинов on 11.05.2022.
//

#include <iostream>

#include "src/VkRenderer.hpp"

int main() {
    VkRenderer app;
    
    try{
        app.Run();
    }
    catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

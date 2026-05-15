#include <iostream>

#include "NotinOOP.hpp"

int main() {
    try {
        NotinOOP engine;
        engine.run();
    } 
    catch (const std::exception& e) {
        std::cout << "Critical Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

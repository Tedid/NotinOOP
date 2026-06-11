#pragma once

#include <vector>
#include <string>
#include "Objects/Fragrance.hpp"

namespace Utils
{
    // firstRowIdentation should be true if no message is displayed beforehand
    void printFragrancesByName(std::vector<Fragrance> frags, int identationSize = 0, bool firstRowIdentation = false);
    void toLower(std::string &string);
}

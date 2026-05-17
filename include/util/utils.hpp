#pragma once

#include <vector>
#include "Objects/Fragrance.hpp"

namespace Utils
{
    // firstRowIdentation should be true if no message is displayed beforehand
    void printFragrancesByType(std::vector<Fragrance> frags, int identationSize = 0, bool firstRowIdentation = false);
}

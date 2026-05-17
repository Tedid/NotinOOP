#pragma once

#include <vector>
#include "Objects/Fragrance.hpp"

namespace Utils
{
    void printFragrancesByType(std::vector<Fragrance> frags, int identationSize = 0, bool firstRowIdentation = false);
}

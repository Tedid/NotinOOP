#include "util/utils.hpp"
#include <iostream>

namespace Utils
{

    void printFragrancesByType(std::vector<Fragrance> frags)
    {
        if (frags.empty()) {
            std::cout << "No fragrances available." << std::endl;
            return;
        }

        std::cout << "Items ordered: ";
        const char SPACES[16] = "               "; // 15x spaces
        bool spacesNeeded = false;
        while (frags.size() > 0)
        {
            Fragrance temp = frags[0];
            int numberOfFragrances = 0;

            for (int i = frags.size() - 1; i >= 0; i--)
            {
                if (frags[i] == temp)
                {
                    numberOfFragrances++;
                    frags.erase(frags.begin() + i);
                }
            }

            float FragrancePrice = temp.getPrice();

            std::cout << (spacesNeeded ? SPACES : "") << numberOfFragrances << "x " << temp.getName();
            std::cout << " - (€" << numberOfFragrances * FragrancePrice << " (€" << FragrancePrice << " each)" << std::endl;

            spacesNeeded = true;
        }
    }

}

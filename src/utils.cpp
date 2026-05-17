#include "util/utils.hpp"
#include <iostream>
#include <string>

namespace Utils
{

    void printFragrancesByType(std::vector<Fragrance> frags, int identationSize = 0, bool firstRowIdentation = false)
    {
        if (frags.empty())
        {
            std::cout << "No fragrances available." << std::endl;
            return;
        }

        const std::string SPACES = (identationSize, " ");
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

            std::cout << (firstRowIdentation ? SPACES : "") << numberOfFragrances << "x " << temp.getName();
            std::cout << " - (€" << numberOfFragrances * FragrancePrice << " (€" << FragrancePrice << " each)" << std::endl;

            firstRowIdentation = true; // It's not the first row anymore
        }
    }

    void Utils::removeFragranceFromVector(std::vector<Fragrance> frags, const Fragrance &frag)
    {
        for (int i = 0; i < frags.size(); i++)
        {
            if (frag == frags[i])
            {
                frags.erase(frags.begin() + i);
                break;
            }
        }
    }

}

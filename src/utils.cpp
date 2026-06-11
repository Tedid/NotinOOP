#include "util/utils.hpp"
#include <iostream>

namespace Utils
{

    void printFragrancesByType(std::vector<Fragrance> frags, int identationSize, bool firstRowIdentation)
    {
        if (frags.empty())
        {
            std::cout << "No fragrances available." << std::endl;
            return;
        }

        const std::string SPACES(identationSize, ' ');
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

            long FragrancePrice = temp.getPrice();

            std::cout << (firstRowIdentation ? SPACES : "") << numberOfFragrances << "x " << temp.getName();
            std::cout << " - €" << (numberOfFragrances * FragrancePrice) / 100.0 ;

            firstRowIdentation = true; // It's not the first row anymore
        }
    }

    void toLower(std::string &string)
    {
        for (int i = 0; i < string.size(); i++)
        {
            string[i] = std::tolower(string[i]);
        }
    }
}

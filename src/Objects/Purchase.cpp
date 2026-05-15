#include "Objects/Purchase.hpp"

#include <iostream>

Purchase::Purchase(size_t ID, std::vector<Fragrance> frags, PurchaseStatus stat, size_t uID)
{
    purchaseID = ID;
    fragrances = frags;
    status = stat;
    userID = uID;
    finalPrice = 0;
}

size_t Purchase::getPurchaseID() const
{
    return purchaseID;
}

PurchaseStatus Purchase::getStatus() const
{
    return status;
}

size_t Purchase::getUserID() const
{
    return userID;
}

void printFragrancesByType(std::vector<Fragrance> frags)
{
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

void Purchase::show(const std::string &userName) const
{
    std::string statusString;
    switch (status)
    {
    case PurchaseStatus::PENDING:
        statusString = "PENDING";
        break;
    case PurchaseStatus::DELIVERED:
        statusString = "DELIVERED";
        break;
    case PurchaseStatus::CANCELED:
        statusString = "CANCELED";
        break;
    default:
        statusString = "UNKNOWN";
        break;
    }

    std::cout << "Purchase №[" << purchaseID << "] (" << statusString << "):" << std::endl;
    std::cout << "Ordered by: " << userName << std::endl;
    printFragrancesByType(fragrances);
    std::cout << "Summed price: " << finalPrice << std::endl;
}
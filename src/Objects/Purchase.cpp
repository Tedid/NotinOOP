#include "Objects/Purchase.hpp"

#include <iostream>
#include "util/utils.hpp"

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
    Utils::printFragrancesByType(fragrances);
    std::cout << "Summed price: " << finalPrice << std::endl;
}
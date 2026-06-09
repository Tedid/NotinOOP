#include "Objects/Purchase.hpp"

#include <iostream>
#include "util/utils.hpp"

Purchase::Purchase(size_t ID, std::vector<Fragrance> frags, PurchaseStatus stat, size_t uID, float finalPrice)
{
    purchaseID = ID;
    fragrances = frags;
    status = stat;
    userID = uID;
    this->finalPrice = finalPrice;
}

void Purchase::setStatus(PurchaseStatus newStatus)
{
    status = newStatus;
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

float Purchase::getFinalPrice() const
{
    return finalPrice;
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
    case PurchaseStatus::CANCELLED:
        statusString = "CANCELED";
        break;
    default:
        statusString = "UNKNOWN";
        break;
    }

    std::cout << "Purchase №[" << purchaseID << "] (" << statusString << "):" << std::endl;
    std::cout << "Ordered by: " << userName << std::endl;
    std::string message = "Items ordered: ";
    std::cout << message;
    Utils::printFragrancesByType(fragrances, message.size());
    std::cout << "Summed price: " << finalPrice << std::endl;
}

void Purchase::serialize(std::ostream &os) const
{
    os << purchaseID << ":";

    for (int i = 0; i < fragrances.size(); i++)
    {
        os << fragrances[i].getID();
        if (i != fragrances.size() - 1)
        {
            os << " ";
        }
    }

    std::string statusStr;
    switch (status)
    {
    case PurchaseStatus::PENDING:
        statusStr = "PENDING";   
        break;
    case PurchaseStatus::DELIVERED:
        statusStr = "DELIVERED";
        break;
    case PurchaseStatus::CANCELLED:
        statusStr = "CANCELLED";
        break;
    default:
        statusStr = "UNKNOWN";
        break;
    }

    os << ":" << statusStr << ":" << userID << ":" << finalPrice;
}
#pragma once

#include <vector>

#include "Fragrance.hpp"
#include "util/enums.hpp"

class Purchase
{
    size_t purchaseID; // unique
    std::vector<Fragrance> fragrances;
    PurchaseStatus status;
    int userID;
    float finalPrice;

public:
    // will use move for fragrances
    Purchase(size_t id, std::vector<Fragrance> fragrances, PurchaseStatus status, size_t userID, float finalPrice = 0);

    size_t getPurchaseID() const;
    PurchaseStatus getStatus() const;
    size_t getUserID() const;

    void show(const std::string &userName) const;
};
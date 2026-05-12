#pragma once

#include <vector>

#include "Fragrance.hpp"
#include "util/enums.hpp"

class Purchase
{
    size_t purchaseId; // unique
    std::vector<Fragrance> fragrances;
    PurchaseStatus status;
    int userID;

public:
    Purchase(size_t id, std::vector<Fragrance> fragrances, PurchaseStatus status, size_t userID); // will use move for fragrances

    size_t getPurchaseID() const;
    PurchaseStatus getStatus() const;
    size_t getUserID() const;

    void show() const;
};
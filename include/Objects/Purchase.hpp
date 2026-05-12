#pragma once

#include <vector>

#include "Fragrance.hpp"
#include "util/enums.hpp"

class Purchase
{
    int purchaseId;
    std::vector<Fragrance> fragrances;
    PurchaseStatus status;
    int userID;

public:
    Purchase(int id, std::vector<Fragrance> fragrances, PurchaseStatus status, int userID); // will use move for fragrances

    int getPurchaseID() const;
    PurchaseStatus getStatus() const;
    int getUserID() const;

    void show() const;
};
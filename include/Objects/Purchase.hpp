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
    long finalPrice;

public:
    // will use move for fragrances
    Purchase(size_t id, std::vector<Fragrance> fragrances, PurchaseStatus status, size_t userID, long finalPrice = 0);

    void setStatus(PurchaseStatus newStatus);

    size_t getPurchaseID() const;
    std::vector<Fragrance> getFragrances() const;
    PurchaseStatus getStatus() const;
    size_t getUserID() const;
    long getFinalPrice() const;

    void show(const std::string &userName) const;
    void serialize(std::ostream &os) const;
};
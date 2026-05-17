#pragma once

#include <string>

#include "Fragrance.hpp"

class Discount
{
protected:
    size_t discountID; // unique
    float discountPercent;

public:
    Discount(size_t id, float percent);
    virtual ~Discount() = default;
};

class BonusDiscount : public Discount
{
    float bonus;

public:
    BonusDiscount(size_t id, float percent, float bonus);
};

class BrandDiscount : public Discount
{
    std::string brandName;

public:
    BrandDiscount(size_t id, float percent, const std::string &brandName);
};
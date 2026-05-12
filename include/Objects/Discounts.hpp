#pragma once

#include <string>

#include "Fragrance.hpp"

class Discount
{
protected:
    int discountID; // unique
    float discountPercent;

public:
    Discount(int id, float percent);
    virtual ~Discount() = default;

    virtual float apply(const Fragrance &frag) const;
};

class BonusDiscount : public Discount
{
    float bonus;

public:
    BonusDiscount(int id, float percent, float bonus);

    float apply(const Fragrance &frag) const override;
};

class BrandDiscount : public Discount
{
    std::string brandName;

public:
    BrandDiscount(int id, float percent, const std::string &brandName);
    float apply(const Fragrance &frag) const override;
};
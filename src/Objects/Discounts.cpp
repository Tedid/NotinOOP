#include "Objects/Discounts.hpp"

Discount::Discount(size_t id, float percent)
{
    discountID = id;
    discountPercent = percent;
}

BonusDiscount::BonusDiscount(size_t id, float percent, float bon) : Discount(id, percent)
{
    bonus = bon;
}

BrandDiscount::BrandDiscount(size_t id, float percent, const std::string &name) : Discount(id, percent)
{
    brandName = name;
}

#include "Objects/Discounts.hpp"

Discount::Discount()
{
    discountID = 0;
    discountPercent = 0;
}

Discount::Discount(size_t id, float percent)
{
    discountID = id;
    discountPercent = percent;
}

BonusDiscount::BonusDiscount(size_t id, float percent, float bon)
{
    discountID = id;
    discountPercent = percent;
    bonus = bon;
}

BrandDiscount::BrandDiscount(size_t id, float percent, const std::string &name)
{
    discountID = id;
    discountPercent = percent;
    brandName = name;
}

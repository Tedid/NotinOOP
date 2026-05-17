#include "Objects/Discounts.hpp"
#include "util/enums.hpp"

Discount::Discount(size_t id, float percent)
{
    discountID = id;
    discountPercent = percent;
}

DiscountType Discount::getType() const
{
    return DiscountType::DISCOUNT;
}

BonusDiscount::BonusDiscount(size_t id, float percent, float bon) : Discount(id, percent)
{
    bonus = bon;
}

DiscountType BonusDiscount::getType() const
{
    return DiscountType::BONUS_DISCOUNT;
}


BrandDiscount::BrandDiscount(size_t id, float percent, const std::string &name) : Discount(id, percent)
{
    brandName = name;
}

DiscountType BrandDiscount::getType() const
{
    return DiscountType::BRAND_DISCOUNT;
}

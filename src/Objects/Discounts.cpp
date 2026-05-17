#include "Objects/Discounts.hpp"
#include "util/enums.hpp"

#include <iostream>

Discount::Discount(size_t id, float percent)
{
    discountID = id;
    discountPercent = percent;
}

DiscountType Discount::getType() const
{
    return DiscountType::DISCOUNT;
}

void Discount::view() const
{
    std::cout << "Discount №[" << discountID << "]:" << std::endl;
    std::cout << "Discount percent: " << discountPercent << "%" << std::endl;
}

float Discount::getPercent()
{
    return discountPercent;
}

BonusDiscount::BonusDiscount(size_t id, float percent, float bon) : Discount(id, percent)
{
    bonus = bon;
}

DiscountType BonusDiscount::getType() const
{
    return DiscountType::BONUS_DISCOUNT;
}

void BonusDiscount::view() const
{
    std::cout << "Bonus Discount №[" << discountID << "]:" << std::endl;
    std::cout << "Discount percent: " << discountPercent << "%" << std::endl;
    std::cout << "Bonus discount: €" << bonus << std::endl;
}

float BonusDiscount::getBonus()
{
    return bonus;
}

BrandDiscount::BrandDiscount(size_t id, float percent, const std::string &name) : Discount(id, percent)
{
    brandName = name;
}

DiscountType BrandDiscount::getType() const
{
    return DiscountType::BRAND_DISCOUNT;
}

void BrandDiscount::view() const
{
    std::cout << "Brand Discount №[" << discountID << "]:" << std::endl;
    std::cout << "Discount percent: " << discountPercent << "% ";
    std::cout << "for the brand: " << brandName << std::endl;
}

std::string BrandDiscount::getBrandName()
{
    return brandName;
}

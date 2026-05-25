#include "Objects/Discounts.hpp"
#include "util/enums.hpp"

#include <iostream>
#include <sstream>

Discount::Discount(size_t id, int percent)
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
    std::cout << "Discount ID[" << discountID << "]:" << std::endl;
    std::cout << "Discount percent: " << discountPercent << "%" << std::endl;
}

int Discount::getPercent()
{
    return discountPercent;
}

BonusDiscount::BonusDiscount(size_t id, int percent, float bon) : Discount(id, percent)
{
    bonus = bon;
}

size_t Discount::getID() const
{
    return discountID;
}

void Discount::serialize(std::ostream &os) const
{
    os << "D:" << discountID << ":" << discountPercent;
}

void Discount::deserialize(const std::string &str)
{
    std::stringstream ss(str);

    size_t id;
    int percent;
    ss >> id >> percent;

    discountID = id;
    discountPercent = percent;
}

DiscountType BonusDiscount::getType() const
{
    return DiscountType::BONUS_DISCOUNT;
}

void BonusDiscount::view() const
{
    std::cout << "Bonus Discount ID[" << discountID << "]:" << std::endl;
    std::cout << "Discount percent: " << discountPercent << "%" << std::endl;
    std::cout << "Bonus discount: " << bonus << " Euro" << std::endl;
}

float BonusDiscount::getBonus()
{
    return bonus;
}

void BonusDiscount::serialize(std::ostream &os) const
{
    os << "B:" << discountID << ":" << discountPercent << ":" << bonus;
}

void BonusDiscount::deserialize(const std::string &str)
{
    std::stringstream ss(str);

    size_t id;
    int percent;
    float bonus;
    ss >> id >> percent >> bonus;

    discountID = id;
    discountPercent = percent;
    this->bonus = bonus;
}

BrandDiscount::BrandDiscount(size_t id, int percent, const std::string &name) : Discount(id, percent)
{
    brandName = name;
}

DiscountType BrandDiscount::getType() const
{
    return DiscountType::BRAND_DISCOUNT;
}

void BrandDiscount::view() const
{
    std::cout << "Brand Discount ID[" << discountID << "]:" << std::endl;
    std::cout << "Discount percent: " << discountPercent << "% ";
    std::cout << "for the brand: " << brandName << std::endl;
}

std::string BrandDiscount::getBrandName()
{
    return brandName;
}

void BrandDiscount::serialize(std::ostream &os) const
{
    os << "BR:" << discountID << ":" << discountPercent << ":" << brandName;
}

void BrandDiscount::deserialize(const std::string &str)
{
    std::stringstream ss(str);

    size_t id;
    int percent;
    std::string brandName;
    ss >> id >> percent >> brandName;

    discountID = id;
    discountPercent = percent;
    this->brandName = brandName;
}

#pragma once

#include <string>

#include "Fragrance.hpp"
#include "util/enums.hpp"

class Discount
{
protected:
    size_t discountID; // unique
    int discountPercent;

public:
    Discount(size_t id, int percent);

    virtual DiscountType getType() const;
    virtual void view() const;
    int getPercent();
    size_t getID() const;

    virtual void serialize(std::ostream &os) const;

    virtual void deserialize(const std::string &str);

    virtual ~Discount() = default;
};

class BonusDiscount : public Discount
{
    long bonus;

public:
    BonusDiscount(size_t id, int percent, long bonus);

    DiscountType getType() const override;
    void view() const override;
    long getBonus();

    void serialize(std::ostream &os) const override;
    void deserialize(const std::string &str) override;
};

class BrandDiscount : public Discount
{
    std::string brandName;

public:
    BrandDiscount(size_t id, int percent, const std::string &brandName);

    DiscountType getType() const override;
    void view() const override;
    std::string getBrandName();

    void serialize(std::ostream &os) const override;
    void deserialize(const std::string &str) override;
};
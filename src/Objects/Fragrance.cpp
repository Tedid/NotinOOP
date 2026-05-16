#include "Objects/Fragrance.hpp"

Fragrance::Fragrance(size_t ID, const std::string &name, const std::string &brand, float price, const std::vector<size_t> &ingredientIDs, int quantity = 0)
{
    fragranceID = ID;
    this->name = name;
    this->brand = brand;
    this->price = price;
    this->ingredientIDs = ingredientIDs;
    this->quantity = quantity;
}

size_t Fragrance::getID() const
{
    return fragranceID;
}

std::string Fragrance::getName() const
{
    return name;
}

std::string Fragrance::getBrand() const
{
    return brand;
}

float Fragrance::getPrice() const
{
    return price;
}

const std::vector<size_t> &Fragrance::getIngredientIDs() const
{
    return ingredientIDs;
}

int Fragrance::getQuantity() const
{
    return quantity;
}

const std::vector<Review> Fragrance::getReviews() const
{
    return reviews;
}

float Fragrance::getAvgRating() const
{
    int sum = 0;
    int numberOfRatings = getReviews().size();
    for (int i = 0; i <= numberOfRatings; i++)
    {
        sum += getReviews()[i].getRating();
    }
    return sum / numberOfRatings;
}

bool Fragrance::operator==(const Fragrance &other) const
{
    return this->fragranceID == other.fragranceID;
}

bool Fragrance::operator!=(const Fragrance &other) const
{
    return !(*this == other);
}
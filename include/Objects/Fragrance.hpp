#pragma once

#include "Review.hpp"

#include <string>
#include <vector>

class Fragrance{
    int fragranceID;                   // unique
    std::string name;
    std::string brand;
    float price;
    std::vector<int> ingredientIDs;
    int quantity;
    std::vector<Review> reviews;

    public:
    Fragrance(const std::string& name,const std::string& brand, float price,const std::vector<int>& ingredientIDs);

    int getID() const;
    std::string getName() const;
    std::string getBrand() const;
    float getPrice() const;
    const std::vector<int>& getIngredientIDs() const;
    int getQuantity() const;
    const std::vector<Review> getReviews() const;
    float getAvgRating() const;
};
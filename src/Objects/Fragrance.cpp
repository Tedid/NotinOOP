#include "Objects/Fragrance.hpp"

Fragrance::Fragrance(size_t ID, const std::string &name, const std::string &brand, long price, const std::vector<size_t> &ingredientIDs, int quantity)
{
    fragranceID = ID;
    this->name = name;
    this->brand = brand;
    this->price = price;
    this->ingredientIDs = ingredientIDs;
    this->quantity = quantity;
}

void Fragrance::addReview(const Review &review)
{
    reviews.push_back(review);
}

Review Fragrance::removeReview(size_t reviewID)
{
    for (int i = 0; i < reviews.size(); i++)
    {
        if (reviews[i].getReviewID() == reviewID)
        {
            Review removedReview = reviews[i];
            reviews.erase(reviews.begin() + i);
            return removedReview;
        }
    }
    return Review(0, "", 0, "", 0); // Return an empty review if not found
}

void Fragrance::addQuantity(int quantityToAdd)
{
    quantity += quantityToAdd;
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

long Fragrance::getPrice() const
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
    int numberOfRatings = reviews.size();
    if (numberOfRatings == 0)
    {
        return 0.0f;
    }

    int sum = 0;
    for (int i = 0; i < numberOfRatings; i++)
    {
        sum += reviews[i].getRating();
    }
    return (float)sum / numberOfRatings;
}

bool Fragrance::operator==(const Fragrance &other) const
{
    return this->fragranceID == other.fragranceID;
}

bool Fragrance::operator!=(const Fragrance &other) const
{
    return !(*this == other);
}
void Fragrance::serialize(std::ostream &os) const
{
    // variables:
    os << fragranceID << "|" << name << "|" << brand << "|" << price << "|" << quantity << "|";

    // ingredients:
    if (ingredientIDs.empty())
    {
        os << "empty";
    }
    else
    {
        for (int i = 0; i < ingredientIDs.size(); i++)
        {
            os << ingredientIDs[i];
            if (i != ingredientIDs.size() - 1)
            {
                os << " ";
            }
        }
    }

    os << "|";

    // reviews:
    if (reviews.empty())
    {
        os << "empty";
    }
    else
    {
        for (int i = 0; i < reviews.size(); i++)
        {
            // <reviewID fragranceName userID comment rating>
            reviews[i].serialize(os);
            if (i != reviews.size() - 1)
            {
                os << " ";
            }
        }
    }

    os << std::endl;
}

Fragrance Fragrance::deserialize(const std::string &line)
{
    std::stringstream ss(line);
    std::string idStr, name, brand, priceStr, quantityStr, ingredientIDsStr, reviewsStr;
    std::getline(ss, idStr, '|');
    std::getline(ss, name, '|');
    std::getline(ss, brand, '|');
    std::getline(ss, priceStr, '|');
    std::getline(ss, quantityStr, '|');
    std::getline(ss, ingredientIDsStr, '|');
    std::getline(ss, reviewsStr, '|');

    size_t id = std::stoull(idStr);
    long price = std::stoll(priceStr);
    int quantity = std::stoi(quantityStr);

    // Ingredient IDs:
    std::vector<size_t> ingredientIDs;
    std::stringstream ingredientIDsSS(ingredientIDsStr);
    std::string ingredientIDStr;
    while (ingredientIDsSS >> ingredientIDStr)
    {
        if (ingredientIDStr == "empty" || ingredientIDStr.empty())
        {
            break;
        }
        size_t ingredientID = std::stoull(ingredientIDStr);
        ingredientIDs.push_back(ingredientID);
    }

    Fragrance fragrance(id, name, brand, price, ingredientIDs, quantity);

    // Reviews:
    std::stringstream reviewsSS(reviewsStr);
    std::string reviewStr;
    while (std::getline(reviewsSS, reviewStr, ':'))
    {
        if (reviewStr == "empty" || reviewStr.empty())
        {
            break;
        }
        Review review = Review::deserialize(reviewStr);
        fragrance.addReview(review);
    }

    return fragrance;
}

#pragma once

#include <string>

class Review
{
    size_t reviewID;        // unique
    std::string fragranceName;
    size_t userID;
    std::string comment = ""; // <=1000 characters
    int rating = 0;          // between 0 and 5

public:
    Review(size_t ID, const std::string &name, size_t userID, const std::string &comment, int rating);

    size_t getReviewID() const;
    std::string getName() const;
    size_t getUserID() const;
    std::string getComent() const;
    int getRating() const;
};
#pragma once

#include <string>

class Review
{
    int reviewID;        // unique
    std::string fragranceName;
    int userID;
    std::string comment; // <=1000 characters
    int rating;          // between 0 and 5

public:
    Review(const std::string &name, int userID, const std::string &comment, int rating);

    int getReviewID() const;
    std::string getName() const;
    int getUserID() const;
    std::string getComent() const;
    int getRating() const;
};
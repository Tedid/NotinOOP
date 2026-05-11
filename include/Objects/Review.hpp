#pragma once

#include <string>

class Review{
    int reviewID;           // unique
    std::string fragranceName; 
    int userID;
    std::string comment;    // <=1000 characters
    int rating;             // between 0 and 5

    public:
    Review(std::string name, int userID, std::string comment, int rating);
};
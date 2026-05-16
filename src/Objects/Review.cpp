#include "Objects/Review.hpp"

Review::Review(size_t ID, const std::string &name, size_t uID, const std::string &comm, int rat)
{
    reviewID = ID;
    fragranceName = name;
    userID = uID;

    if (comm.size() <= 1000)
    {
        comment = comm;
    }
    else
    {
        // Shouldn't be able to print this (Should be validated when entering info)
        comment = "[Comment too long. Please use up to 1000 characters.]";
    }

    if (rat < 0)
    {
        rating = 0;
    }
    else if (rat > 5)
    {
        rating = 5;
    }
    else
    {
        rating = rat;
    }
}

size_t Review::getReviewID() const
{
    return reviewID;
}

std::string Review::getName() const
{
    return fragranceName;
}

size_t Review::getUserID() const
{
    return userID;
}

std::string Review::getComent() const
{
    return comment;
}

int Review::getRating() const
{
    return rating;
}
#include "Objects/Review.hpp"

Review::Review(const std::string &name, size_t uID, const std::string &comm, int rat)
{
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
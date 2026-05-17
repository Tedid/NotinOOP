#include "Objects/Users.hpp"
#include "util/utils.hpp"

#include <iostream>

User::User(size_t id, const std::string &name, const std::string &pass)
{
    userID = id;
    username = name;
    password = pass;
}

size_t User::getUserID() const
{
    return userID;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

Buyer::Buyer(size_t id, const std::string &name, const std::string &pass, float balance) : User(id, name, pass)
{
    this->balance = balance;
}

void Buyer::addToBalance(float money)
{
    balance += money;
}

void Buyer::addToWishlist(const Fragrance &fragrance)
{
    wishlist.push_back(fragrance);
}

void Buyer::removeFromWishlist(const Fragrance &fragrance)
{
    for (int i = 0; i < wishlist.size(); i++)
    {
        if (fragrance == wishlist[i])
        {
            wishlist.erase(wishlist.begin() + i);
            break;
        }
    }
}

void Buyer::viewWishlist() const
{
    std::string message = "Wishlisted items: ";
    std::cout << message;
    Utils::printFragrancesByType(wishlist, message.size());
}
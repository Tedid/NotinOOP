#include "Objects/Users.hpp"
#include "util/utils.hpp"

#include <iostream>

void Buyer::removeFragranceFromVector(std::vector<Fragrance> frags, const Fragrance &frag)
{
    for (int i = 0; i < frags.size(); i++)
    {
        if (frag == frags[i])
        {
            frags.erase(frags.begin() + i);
            break;
        }
    }
}

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
    removeFragranceFromVector(wishlist, fragrance);
}

void Buyer::viewWishlist() const
{
    std::string message = "Wishlisted items: ";
    std::cout << message;
    Utils::printFragrancesByType(wishlist, message.size());
}

void Buyer::addToCart(const Fragrance &fragrance)
{
    cart.push_back(fragrance);
}

void Buyer::removeFromCart(const Fragrance &fragrance)
{
    removeFragranceFromVector(cart, fragrance);
}

void Buyer::viewCart() const
{
    std::string message = "Items in cart: ";
    std::cout << message;
    Utils::printFragrancesByType(wishlist, message.size());
}

void Buyer::checkout()
{
    // WRITE CHECK FOR SUFFICIENT FUNDS IN ENGINE

    float fragsPrice = 0;
    for (int i = 0; i < cart.size(); i++)
    {
        fragsPrice += cart[i].getPrice();
    }

    int maxDiscountedPrice = fragsPrice;
    int maxDiscountIndex = 0;
    for (int i = 0; i < discounts.size(); i++)
    {
    }
}
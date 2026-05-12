#pragma once

#include <string>
#include <vector>

#include "Fragrance.hpp"
#include "Purchase.hpp"
#include "Discounts.hpp"

class User
{
protected:
    int userID; // unique
    std::string username;
    std::string password;

public:
    User(int id, const std::string &name, const std::string &pass);
    // ensures proper deletion of subclass objects through a User pointer
    virtual ~User() = default;

    int getUserID() const;
    std::string getUsername() const;
    std::string getPassword() const;

    // ensures every subclass has its own help menu
    virtual void showHelp() const = 0;
};

class Buyer : public User
{
    std::vector<Fragrance> &cart;
    std::vector<Purchase> &purchases;
    std::vector<Fragrance> &wishlist;
    float balance;
    std::vector<Discount> &discounts;

public:
    void showHelp() const override;
};
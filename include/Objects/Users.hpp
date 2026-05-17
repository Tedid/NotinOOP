#pragma once

#include <string>
#include <vector>

#include "Fragrance.hpp"
#include "Purchase.hpp"
#include "Discounts.hpp"

class User
{
protected:
    size_t userID; // unique
    std::string username;
    std::string password;

public:
    User(size_t id, const std::string &name, const std::string &pass);
    // ensures proper deletion of subclass objects through a User pointer
    virtual ~User() = default;

    size_t getUserID() const;
    std::string getUsername() const;
    std::string getPassword() const;

    // ensures every subclass has its own help menu
    virtual void showHelp() const = 0;
};

class Buyer : public User
{
    std::vector<Fragrance> cart;
    std::vector<Purchase> purchases;
    std::vector<Fragrance> wishlist;
    float balance;
    std::vector<Discount *> discounts;

    void removeFragranceFromVector(std::vector<Fragrance> &frags, const Fragrance &frag);
    float Buyer::FragrancesDiscountedPrice(const std::vector<Fragrance> &frags, Discount &discount);
    int GetBestDiscountIndex();

public:
    Buyer(size_t id, const std::string &name, const std::string &pass, float balance = 0);

    void addToBalance(float money);

    void addToWishlist(const Fragrance &fragrance);
    void removeFromWishlist(const Fragrance &fragrance);
    void viewWishlist() const;

    void addToCart(const Fragrance &fragrance);
    void removeFromCart(const Fragrance &fragrance);
    void viewCart() const;

    // [Write into NotinOOP.cpp]
    // void checkout();
    // void cancel(size_t purchaseID);

    void viewBought() const;
    void viewPurchases() const;
    void viewDiscounts() const;

    // void Recommend() const;
    // void makeReview(const std::string &fragranceName, int rating, const std::string &comment);

    void showHelp() const override;
};

class Admin : public User
{
public:
    void blockUser(std::string username);
    void removeReview(size_t fragranceID, size_t reviewID);
    void deliver(size_t purchaseID);

    void createFragrance(const std::string &name, const std::string &brand, float price, const std::vector<size_t> &ingredientIDs);
    void addQuantity(const std::string &name, int quantity);
};
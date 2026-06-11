#pragma once

#include <string>
#include <vector>

#include "Fragrance.hpp"
#include "Purchase.hpp"
#include "Discounts.hpp"
#include "util/enums.hpp"

class User
{
protected:
    size_t userID; // unique
    UserType type;
    std::string username;
    std::string password;

public:
    User(size_t id, const std::string &name, const std::string &pass);
    // ensures proper deletion of subclass objects through a User pointer
    virtual ~User() = default;

    size_t getUserID() const;
    UserType getType() const;
    std::string getUsername() const;
    std::string getPassword() const;

    virtual void serialize(std::ostream &os) const = 0;
    // ensures every subclass has its own help menu
    virtual void showHelp() const = 0;
};

class Buyer : public User
{
    std::vector<Fragrance> cart;
    std::vector<Purchase> purchases;
    std::vector<Fragrance> wishlist;
    long balance = 0;
    int reviewsRemoved = 0;
    std::vector<Discount *> discounts;

    void removeFragranceFromVector(std::vector<Fragrance> &frags, const Fragrance &frag);

public:
    Buyer(size_t id, const std::string &name, const std::string &pass, long balance = 0, int reviewsRemoved = 0);

    void addToBalance(long money);

    void addToWishlist(const Fragrance &fragrance);
    void removeFromWishlist(const Fragrance &fragrance);
    void removeAllFromWishlist(const Fragrance &fragrance);
    void viewWishlist() const;

    void addToCart(const Fragrance &fragrance);
    void removeFromCart(const Fragrance &fragrance);
    void removeAllFromCart(const Fragrance &fragrance);
    void viewCart() const;
    void clearCart();

    void addToPurchases(const Purchase &purchase);
    void cancelPurchase(size_t purchaseID);

    void incrementReviewsRemoved();

    void addToDiscounts(Discount *discount);
    void removeDiscount(size_t discountID);

    long getBalance() const;
    int getReviewsRemoved() const;
    std::vector<Fragrance> getCart() const;
    std::vector<Purchase> &getPurchases();
    std::vector<Discount *> getDiscounts() const;
    std::vector<Fragrance> getWishlist() const;

    void viewBought() const;
    void viewPurchases() const;
    void viewDiscounts() const;

    void showHelp() const override;
    void serialize(std::ostream &os) const override;
    static Buyer *deserialize(const std::string &line, const std::vector<Fragrance> &catalogue);
};

class Admin : public User
{
public:
    Admin(size_t id, const std::string &name, const std::string &pass);
    Admin(const std::string &deserializationStr); // ONLY for deserialization

    void showHelp() const override;
    void serialize(std::ostream &os) const override;
};
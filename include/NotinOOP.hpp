#pragma once

#include <vector>
#include <string>

#include "Objects/Users.hpp"
#include "Objects/Fragrance.hpp"
#include "Objects/Purchase.hpp"
#include "Objects/Review.hpp"

class NotinOOP
{
    const size_t DEFAULT_ADMIN_ID = 1000000; // A million
    size_t nextUserID = DEFAULT_ADMIN_ID + 1;
    size_t nextFragranceID = 2000000; // Two million
    size_t nextPurchaseID = 3000000;  // Three million
    size_t nextReviewID = 4000000;    // Four million
    size_t nextDiscountID = 5000000;  // Five million cigarettes

    // Storing pointers because of subclasses:
    std::vector<User *> users;
    std::vector<Fragrance> catalogue;

    User *activeUser = nullptr;

    void processCommand(const std::string &command);

    // User handling:
    void handleRegister(const std::string &name, const std::string &pass);
    void handleRegisterAdmin(const std::string &name, const std::string &pass);
    void handleLogin(const std::string &name, const std::string &pass);
    void handleLogout();

    // Useful functions for buyers:
    Fragrance *findFragranceByName(const std::string &name);
    Discount *getBestDiscount();
    long fragrancesDiscountedPrice(const std::vector<Fragrance> &frags, Discount &discount);
    Discount *generateNewDiscount();

    // Useful functions for admins:
    size_t getLastIngredientID();

    // Buyer handling:
    void handleAddToBalance(long amount);
    void handleViewBalance() const;
    void handleAddToWishlist(const std::string &fragranceName);
    void handleRemoveFromWishlist(const std::string &fragranceName);
    void handleAddToCart(const std::string &fragranceName);
    void handleRemoveFromCart(const std::string &fragranceName);
    void handleViewCart() const;
    void handleViewWishlist() const;
    void handleViewBought() const;
    void handleViewPurchases() const;
    void handleRecommend(const size_t numberOfRecommendations) const;
    void handleCheckout();
    void handleCancelPurchase(int purchaseID);
    void handleMakeReview(const std::string &fragranceName, double rating, const std::string &comment);

    // Admin handling:
    void handleBlockUser(const std::string &username);
    void handleCreateFragrance(const std::string &name, const std::string &brand, long price, const std::vector<size_t> &ingredientsList);
    void handleRemoveFragrance(const std::string &fragranceName);
    void handleAddQuantity(const std::string &fragranceName, int quantity);
    void handleDeliverPurchase(int purchaseID);
    void handleRemoveReview(int fragranceId, int reviewId);
    void printAvailableIngredients() const;

    // File handling:
    void saveData() const;
    void loadData();

public:
    NotinOOP();
    ~NotinOOP();

    void run();
};

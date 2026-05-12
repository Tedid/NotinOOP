#pragma once

#include <vector>
#include <string>

#include "Objects/Users.hpp"
#include "Objects/Fragrance.hpp"
#include "Objects/Purchase.hpp"
#include "Objects/Discounts.hpp"
#include "Objects/Review.hpp"

class NotinOOP{
    //Storing pointers because of subclasses:
    std::vector<User*> users;
    std::vector<Fragrance> catalog;
    std::vector<Purchase> purchases;
    std::vector<Review> reviews;
    //std::vector<Discount*> vouchers;  //I don't think I need to store these  here

    User* activeUser;

    void processCommand(const std::string &command);

    //User handling:
    void handleRegister(const std::string &name, const std::string &pass);
    void handleLogin(const std::string &name, const std::string &pass);

    //Buyer handling:
    void handleAddToBalance(float amount);
    void handleAddToWishlist(const std::string& fragranceName);
    void handleRemoveFromWishlist(const std::string& fragranceName);
    void handleAddToCart(const std::string& fragranceName);
    void handleRemoveFromCart(const std::string& fragranceName);
    void handleViewCart() const;
    void handleViewBought() const;
    void handleViewPurchases() const;
    void handleRecommend();
    void handleCheckout();
    void handleCancelPurchase(int purchaseId);
    void handleMakeReview(const std::string& fragranceName, double rating, const std::string& comment);

    //Admin handling:
    void handleBlockUser(const std::string& username);
    void handleCreateFragrance(const std::string& name, const std::string& brand, float price, const std::string& ingredientsList);
    void handleAddQuantity(const std::string& fragranceName, int quantity);
    void handleDeliverPurchase(int purchaseId);
    void handleRemoveReview(int fragranceId, int reviewId);

};

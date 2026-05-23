#include "NotinOOP.hpp"
#include "util/utils.hpp"

#include <sstream>
#include <iostream>

void NotinOOP::processCommand(const std::string &commandLine)
{
    if (commandLine.empty())
        return;

    std::stringstream ss(commandLine);
    std::string command;
    ss >> command;
    Utils::toLower(command);

    // Basic commands:
    if (command == "register")
    {
        std::string username, password;
        ss >> username >> password;
        handleRegister(username, password);
    }
    else if (command == "login")
    {
        std::string username, password;
        ss >> username >> password;
        handleLogin(username, password);
    }

    if (activeUser != nullptr && activeUser->getType() == UserType::BUYER)
    {
        Buyer *currentBuyer = (Buyer *)activeUser;

        // Buyer commands:
        if (command == "add-to-balance")
        {
            float money;
            ss >> money;

            if (ss.fail() || money < 0)
            {
                std::cout << "Invalid amount of money!" << std::endl;
            }
            else
            {
                handleAddToBalance(money);
            }
        }
        else if (command == "add-to-wishlist")
        {
            std::string fragranceName;
            ss >> fragranceName;
            handleAddToWishlist(fragranceName);
        }
        else if (command == "remove-from-wishlist")
        {
            std::string fragranceName;
            ss >> fragranceName;
            handleRemoveFromWishlist(fragranceName);
        }
        else if (command == "view-cart")
        {
            handleViewCart();
        }
        else if (command == "view-bought")
        {
            handleViewBought();
        }
        else if (command == "view-purchases")
        {
            handleViewPurchases();
        }
        else if (command == "recommend")
        {
            handleRecommend();
        }
        else if (command == "checkout")
        {
            handleCheckout();
        }
        else if (command == "cancel")
        {
            size_t purchaseID;
            ss >> purchaseID;

            if (ss.fail() || purchaseID < 0)
            {
                std::cout << "Invalid ID" << std::endl;
            }
            else
            {
                handleCancelPurchase(purchaseID);
            }
        }
        else if (command == "make-review")
        {
            std::string fragranceName, comment;
            int rating;

            ss >> fragranceName;
            if (ss.fail() || fragranceName.empty())
            {
                std::cout << "Invalid fragrance name!" << std::endl;
                return;
            }

            ss >> rating;
            if (ss.fail() || rating < 0 || rating > 5)
            {
                std::cout << "Invalid rating! [Must be in the range 0-5]" << std::endl;
                return;
            }

            ss >> comment;
            if (ss.fail() || comment.empty() || comment.size() > 1000)
            {
                std::cout << "Invalid comment! [Comment must be <1000 characters long]" << std::endl;
                return;
            }

            handleMakeReview(fragranceName, rating, comment);
        }
    } else if (activeUser != nullptr && activeUser->getType() == UserType::ADMIN)
    {
        if(command == "block-user")
        {
            std::string username;
            ss >> username;
            handleBlockUser(username);
        }
        else if (command == "create-fragrance")
        { 
            std::string name, brand;
            float price = -1;
            std::vector<size_t> ingredientsList;

            ss >> name >> brand >> price;

            if (ss.fail() || name.empty() || brand.empty() || price < 0)
            {
                std::cout << "Invalid arguments format!" << std::endl;
                return;
            }

            size_t ingredientID;
            while (ss >> ingredientID)
            {
                if (ss.fail())
                {
                    std::cout << "Invalid ingredient ID!" << std::endl;
                    return;
                }
                ingredientsList.push_back(ingredientID);
            }

            handleCreateFragrance(name, brand, price, ingredientsList);
        }
        else if (command == "add-quantity")
        {
            std::string fragranceName;
            int quantity;

            ss >> fragranceName >> quantity;

            if (ss.fail() || fragranceName.empty() || quantity <= 0)
            {
                std::cout << "Invalid arguments format!" << std::endl;
                return;
            }

            handleAddQuantity(fragranceName, quantity);
        }
        else if (command == "deliver")
        {
            size_t purchaseID;
            ss >> purchaseID;

            if (ss.fail())
            {
                std::cout << "Invalid ID" << std::endl;
                return;
            }

            handleDeliverPurchase(purchaseID);
        }
        else if (command == "remove-review")
        {
            size_t fragranceId, reviewId;

            ss >> fragranceId >> reviewId;

            if (ss.fail() || fragranceId < 0 || reviewId < 0)
            {
                std::cout << "Invalid IDs" << std::endl;
                return;
            }

            handleRemoveReview(fragranceId, reviewId);
        }
    } else
    {
        std::cout << "You must be logged in to use this command!" << std::endl;
    }
    
}
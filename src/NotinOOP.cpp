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

    if (activeUser == nullptr || activeUser->getType() != UserType::BUYER)
    {
        std::cout << "This command is available only for logged in buyers!" << std::endl;
    }
    else
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
    }
}
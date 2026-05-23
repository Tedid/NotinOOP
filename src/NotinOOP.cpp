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
            const int DEFAULT_RECOMMENDATIONS = 5;
            const int MAX_RECOMMENDATIONS = 100;

            size_t numberOfRecommendations;
            ss >> numberOfRecommendations;
            if (ss.fail() || numberOfRecommendations <= 0 || numberOfRecommendations > MAX_RECOMMENDATIONS)
            {
                std::cout << "Using default value for number of recommendations: " << DEFAULT_RECOMMENDATIONS << std::endl;
                numberOfRecommendations = DEFAULT_RECOMMENDATIONS;
            }

            handleRecommend(numberOfRecommendations);
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
    else if (activeUser != nullptr && activeUser->getType() == UserType::ADMIN)
    {
        if (command == "block-user")
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
    }
    else
    {
        std::cout << "You must be logged in to use this command!" << std::endl;
    }
}

void NotinOOP::handleRegister(const std::string &name, const std::string &pass)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getUsername() == name)
        {
            std::cout << "Username already exists!" << std::endl;
            return;
        }
    }

    Buyer *newBuyer = new Buyer(nextUserID++, name, pass);
    users.push_back(newBuyer);

    std::cout << "Registered successfully! New User ID: " << newBuyer->getUserID() << std::endl;
}

void NotinOOP::handleLogin(const std::string &name, const std::string &pass)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getUsername() == name)
        {
            if (users[i]->getPassword() == pass)
            {
                activeUser = users[i];
                std::cout << "Logged in successfully! User ID: " << activeUser->getUserID() << std::endl;
            }
            else
            {
                std::cout << "Incorrect password!" << std::endl;
            }
            return;
        }
    }

    std::cout << "Username not found!" << std::endl;
}

void NotinOOP::handleAddToBalance(float amount)
{
    Buyer *currentBuyer = (Buyer *)activeUser;

    currentBuyer->addToBalance(amount);
    std::cout << "Balance updated! Current balance: " << currentBuyer->getBalance() << std::endl;
}

void NotinOOP::handleAddToWishlist(const std::string &fragranceName)
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    for (int i = 0; i < catalogue.size(); i++)
    {
        if (catalogue[i].getName() == fragranceName)
        {
            currentBuyer->addToWishlist(catalogue[i]);
            std::cout << "Fragrance added to wishlist!" << std::endl;
            return;
        }
    }
    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleRemoveFromWishlist(const std::string &fragranceName)
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    for (int i = 0; i < catalogue.size(); i++)
    {
        if (catalogue[i].getName() == fragranceName)
        {
            currentBuyer->removeFromWishlist(catalogue[i]);
            std::cout << "Fragrance removed from wishlist!" << std::endl;
            return;
        }
    }
    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleAddToCart(const std::string &fragranceName)
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    for (int i = 0; i < catalogue.size(); i++)
    {
        if (catalogue[i].getName() == fragranceName)
        {
            currentBuyer->addToCart(catalogue[i]);
            std::cout << "Fragrance added to cart!" << std::endl;
            return;
        }
    }
    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleRemoveFromCart(const std::string &fragranceName)
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    for (int i = 0; i < catalogue.size(); i++)
    {
        if (catalogue[i].getName() == fragranceName)
        {
            currentBuyer->removeFromCart(catalogue[i]);
            std::cout << "Fragrance removed from cart!" << std::endl;
            return;
        }
    }
    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleViewCart() const
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    currentBuyer->viewCart();
}

void NotinOOP::handleViewBought() const
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    currentBuyer->viewBought();
}

void NotinOOP::handleViewPurchases() const
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    currentBuyer->viewPurchases();
}

void NotinOOP::handleRecommend(const size_t numberOfRecommendations) const
{
    /*
     It gets the most prominent ingredients from the user's wishlist and
     takes the fragrances from the catalogue that contain them the most:
    */

    Buyer *currentBuyer = (Buyer *)activeUser;
    std::vector<Fragrance> wishlist = currentBuyer->getWishlist();
    std::vector<int> ingredientFrequency(1000, 0); // A thousand ingredients max

    for (int i = 0; i < wishlist.size(); i++)
    {
        const Fragrance &fragrance = wishlist[i];
        const std::vector<size_t> &ingredients = fragrance.getIngredientIDs();
        for (int j = 0; j < ingredients.size(); j++)
        {
            ingredientFrequency[ingredients[j]]++;
        }
    }

    int mostLikedIngredientID = 0;
    for (int i = 1; i < ingredientFrequency.size(); i++)
    {
        if (ingredientFrequency[i] > ingredientFrequency[mostLikedIngredientID])
        {
            mostLikedIngredientID = i;
        }
    }

    int secondMostLikedIngredientID = 0;
    for (int i = 1; i < ingredientFrequency.size(); i++)
    {
        if (i != mostLikedIngredientID && ingredientFrequency[i] > ingredientFrequency[secondMostLikedIngredientID])
        {
            secondMostLikedIngredientID = i;
        }
    }

    int thirdMostLikedIngredientID = 0;
    for (int i = 1; i < ingredientFrequency.size(); i++)
    {
        if (i != mostLikedIngredientID && i != secondMostLikedIngredientID && ingredientFrequency[i] > ingredientFrequency[thirdMostLikedIngredientID])
        {
            thirdMostLikedIngredientID = i;
        }
    }

    std::vector<Fragrance> recommendations;

    bool isReccomendationsFilled = false;

    // First we look for fragrances that contain the 3 most liked ingredients:
    for (int i = 0; i < catalogue.size(); i++)
    {
        const Fragrance &fragrance = catalogue[i];
        const std::vector<size_t> &ingredients = fragrance.getIngredientIDs();
        bool hasMostLiked = false, hasSecondMostLiked = false, hasThirdMostLiked = false;

        for (int j = 0; j < ingredients.size(); j++)
        {
            if (ingredients[j] == mostLikedIngredientID)
            {
                hasMostLiked = true;
            }
            else if (ingredients[j] == secondMostLikedIngredientID)
            {
                hasSecondMostLiked = true;
            }
            else if (ingredients[j] == thirdMostLikedIngredientID)
            {
                hasThirdMostLiked = true;
            }
        }

        if (hasMostLiked && hasSecondMostLiked && hasThirdMostLiked)
        {
            bool isInWishlist = false;
            for (int j = 0; j < wishlist.size(); j++)
            {
                if (wishlist[j] == fragrance)
                {
                    isInWishlist = true;
                    break;
                }
            }

            if (!isInWishlist)
            {
                recommendations.push_back(fragrance);
                if (recommendations.size() == numberOfRecommendations)
                {
                    isReccomendationsFilled = true;
                    break;
                }
            }
        }
    }

    // If we don't have enough recommendations, we look for fragrances that contain 2 of the 3 most liked ingredients:
    if (!isReccomendationsFilled)
    {
        for (int i = 0; i < catalogue.size(); i++)
        {
            const Fragrance &fragrance = catalogue[i];
            const std::vector<size_t> &ingredients = fragrance.getIngredientIDs();
            bool hasMostLiked = false, hasSecondMostLiked = false, hasThirdMostLiked = false;

            for (int j = 0; j < ingredients.size(); j++)
            {
                if (ingredients[j] == mostLikedIngredientID)
                {
                    hasMostLiked = true;
                }
                else if (ingredients[j] == secondMostLikedIngredientID)
                {
                    hasSecondMostLiked = true;
                }
                else if (ingredients[j] == thirdMostLikedIngredientID)
                {
                    hasThirdMostLiked = true;
                }
            }

            if (hasMostLiked && hasSecondMostLiked || hasMostLiked && hasThirdMostLiked || hasSecondMostLiked && hasThirdMostLiked)
            {
                bool isInWishlist = false;
                for (int j = 0; j < wishlist.size(); j++)
                {
                    if (wishlist[j] == fragrance)
                    {
                        isInWishlist = true;
                        break;
                    }
                }

                if (!isInWishlist)
                {
                    recommendations.push_back(fragrance);
                    if (recommendations.size() == numberOfRecommendations)
                    {
                        isReccomendationsFilled = true;
                        break;
                    }
                }
            }
        }
    }

    // If we still don't have enough recommendations, we look for fragrances that contain at least 1 of the 3 most liked ingredients:
    if (!isReccomendationsFilled)
    {
        for (int i = 0; i < catalogue.size(); i++)
        {
            const Fragrance &fragrance = catalogue[i];
            const std::vector<size_t> &ingredients = fragrance.getIngredientIDs();
            bool hasMostLiked = false, hasSecondMostLiked = false, hasThirdMostLiked = false;

            for (int j = 0; j < ingredients.size(); j++)
            {
                if (ingredients[j] == mostLikedIngredientID)
                {
                    hasMostLiked = true;
                }
                else if (ingredients[j] == secondMostLikedIngredientID)
                {
                    hasSecondMostLiked = true;
                }
                else if (ingredients[j] == thirdMostLikedIngredientID)
                {
                    hasThirdMostLiked = true;
                }
            }

            if(hasMostLiked || hasSecondMostLiked || hasThirdMostLiked)
            {
                bool isInWishlist = false;
                for (int j = 0; j < wishlist.size(); j++)
                {
                    if (wishlist[j] == fragrance)
                    {
                        isInWishlist = true;
                        break;
                    }
                }

                if (!isInWishlist)
                {
                    recommendations.push_back(fragrance);
                    if (recommendations.size() == numberOfRecommendations)
                    {
                        break;
                    }
                }
            }
        }
    }

    if (recommendations.empty())
    {
        std::cout << "No recommendations available!" << std::endl;
        return;
    }

    std::string message = "Recommended fragrances: ";
    std::cout << message;
    Utils::printFragrancesByType(recommendations, message.size());
}

void NotinOOP::handleCheckout()
{
}

void NotinOOP::handleCancelPurchase(int purchaseID)
{
}

void NotinOOP::handleMakeReview(const std::string &fragranceName, double rating, const std::string &comment)
{
}

void NotinOOP::handleBlockUser(const std::string &username)
{
}

void NotinOOP::handleCreateFragrance(const std::string &name, const std::string &brand, float price, const std::vector<size_t> &ingredientsList)
{
}

void NotinOOP::handleAddQuantity(const std::string &fragranceName, int quantity)
{
}

void NotinOOP::handleDeliverPurchase(int purchaseID)
{
}

void NotinOOP::handleRemoveReview(int fragranceId, int reviewId)
{
}

NotinOOP::NotinOOP()
{
}

NotinOOP::~NotinOOP()
{
    for (User *user : users)
    {
        delete user;
    }
}

void NotinOOP::run()
{
    std::string commandLine;
    while (std::getline(std::cin, commandLine))
    {
        if (commandLine == "end")
            break;
        processCommand(commandLine);
    }
}
#include "NotinOOP.hpp"
#include "util/utils.hpp"

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

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

    // add [number] of discounts to new users:
    const int NEW_USER_DISCOUNT_NUMBER = 5;
    for (int i = 0; i < NEW_USER_DISCOUNT_NUMBER; i++)
    {
        newBuyer->addToDiscounts(generateNewDiscount());
    }
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

    Fragrance *foundFragrance = findFragranceByName(fragranceName);
    if (foundFragrance != nullptr)
    {
        currentBuyer->addToWishlist(*foundFragrance);
        std::cout << "Fragrance added to wishlist!" << std::endl;
        return;
    }

    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleRemoveFromWishlist(const std::string &fragranceName)
{
    Buyer *currentBuyer = (Buyer *)activeUser;

    Fragrance *foundFragrance = findFragranceByName(fragranceName);
    if (foundFragrance != nullptr)
    {
        currentBuyer->removeFromWishlist(*foundFragrance);
        std::cout << "Fragrance removed from wishlist!" << std::endl;
        return;
    }

    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleAddToCart(const std::string &fragranceName)
{
    Buyer *currentBuyer = (Buyer *)activeUser;

    Fragrance *foundFragrance = findFragranceByName(fragranceName);
    if (foundFragrance != nullptr)
    {
        currentBuyer->addToCart(*foundFragrance);
        std::cout << "Fragrance added to cart!" << std::endl;
        return;
    }

    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleRemoveFromCart(const std::string &fragranceName)
{
    Buyer *currentBuyer = (Buyer *)activeUser;

    Fragrance *foundFragrance = findFragranceByName(fragranceName);
    if (foundFragrance != nullptr)
    {
        currentBuyer->removeFromCart(*foundFragrance);
        std::cout << "Fragrance removed from cart!" << std::endl;
        return;
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

            if (hasMostLiked || hasSecondMostLiked || hasThirdMostLiked)
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

float NotinOOP::fragrancesDiscountedPrice(const std::vector<Fragrance> &frags, Discount &discount)
{
    float totalPrice = 0.0f;

    for (int i = 0; i < frags.size(); i++)
    {
        float currentFragPrice = frags[i].getPrice();

        if (discount.getType() == DiscountType::BRAND_DISCOUNT)
        {
            BrandDiscount *brandDsc = (BrandDiscount *)&discount;
            if (frags[i].getBrand() == brandDsc->getBrandName())
            {
                currentFragPrice -= currentFragPrice * (brandDsc->getPercent() / 100.0f);
            }
        }
        else
        {
            currentFragPrice -= currentFragPrice * (discount.getPercent() / 100.0f);
        }

        totalPrice += currentFragPrice;
    }

    if (discount.getType() == DiscountType::BONUS_DISCOUNT)
    {
        BonusDiscount *bonusDsc = (BonusDiscount *)&discount;
        totalPrice -= bonusDsc->getBonus();
    }

    return (totalPrice < 0.0f) ? 0.0f : totalPrice;
}

Fragrance *NotinOOP::findFragranceByName(const std::string &name)
{
    for (int i = 0; i < catalogue.size(); i++)
    {
        if (catalogue[i].getName() == name)
        {
            return &catalogue[i];
        }
    }
    return nullptr;
}

int NotinOOP::getBestDiscountIndex()
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    std::vector<Discount *> discounts = currentBuyer->getDiscounts();
    std::vector<Fragrance> cart = currentBuyer->getCart();

    if (discounts.empty())
    {
        return -1;
    }

    float fragsPrice = 0.0f;
    for (int i = 0; i < cart.size(); i++)
    {
        fragsPrice += cart[i].getPrice();
    }

    int minDiscountIndex = -1;
    for (int i = 0; i < discounts.size(); i++)
    {
        float currentDiscountPrice = fragrancesDiscountedPrice(cart, *discounts[i]);
        if (currentDiscountPrice < fragsPrice)
        {
            fragsPrice = currentDiscountPrice;
            minDiscountIndex = i;
        }
    }

    return minDiscountIndex;
}

Discount *NotinOOP::generateNewDiscount()
{
    const float DEFAULT_DISCOUNT_PROBABILITY = 0.5f;
    const float BONUS_DISCOUNT_PROBABILITY = 0.3f;
    const float BRAND_DISCOUNT_PROBABILITY = 0.2f;

    float roll = (float)rand() / RAND_MAX; // number from 0 to 1 (RAND_MAX == 32767)

    if (roll < DEFAULT_DISCOUNT_PROBABILITY) // less than 0.5
    {
        // a percentage from 5 to 30: (formula is min + (rand() % (max - min + 1)))
        int percentageDiscount = 5 + (rand() % 26);
        return new Discount(nextDiscountID++, percentageDiscount);
    }
    else if (roll > 1 - BRAND_DISCOUNT_PROBABILITY) // more than 0.8
    {
        // a percentage from 20 to 60:
        int percentageDiscount = 20 + (rand() % 41);

        // will choose a random fragrance brand:
        std::vector<std::string> uniqueBrandNames;
        for (int i = 0; i < catalogue.size(); i++)
        {
            std::string brandName = catalogue[i].getBrand();

            bool isBrandStoredInVector = false;
            for (int j = 0; j < uniqueBrandNames.size(); j++)
            {
                if (uniqueBrandNames[j] == brandName)
                {
                    isBrandStoredInVector = true;
                    break;
                }
            }

            if (!isBrandStoredInVector)
            {
                uniqueBrandNames.push_back(brandName);
            }
        }

        // a number from 0 to uniqueBrandNames.size() - 1:
        int randomBrandIndex = rand() % uniqueBrandNames.size();

        return new BrandDiscount(nextDiscountID++, percentageDiscount, uniqueBrandNames[randomBrandIndex]);
    }
    else // between 0.5 and 0.8
    {
        // a percentage from 5 to 20:
        int percentageDiscount = 5 + (rand() % 16);
        // a price from 10 to 80:
        // (actually from 1000 to 8000 divided by 100)
        float bonusPrice = (1000 + (rand() % 7001)) / 100.0f;

        return new BonusDiscount(nextDiscountID++, percentageDiscount, bonusPrice);
    }
}

void NotinOOP::handleCheckout()
{
    Buyer *currentBuyer = (Buyer *)activeUser;
    std::vector<Fragrance> cart = currentBuyer->getCart();
    std::vector<Discount *> discounts = currentBuyer->getDiscounts();

    if (cart.empty())
    {
        std::cout << "Cart is empty!" << std::endl;
        return;
    }

    float originalPrice = 0.0f;
    for (int i = 0; i < cart.size(); i++)
    {
        originalPrice += cart[i].getPrice();
    }

    float discountedPrice = originalPrice;
    int bestVoucherIndex = getBestDiscountIndex();
    if (bestVoucherIndex != -1)
    {
        discountedPrice = fragrancesDiscountedPrice(cart, *discounts[bestVoucherIndex]);
    }

    if (currentBuyer->getBalance() < discountedPrice)
    {
        std::cout << "Not enough money! Final price: " << discountedPrice << ", current balance: " << currentBuyer->getBalance() << std::endl;
        return;
    }

    if (bestVoucherIndex != -1)
    {
        std::cout << "Original price: €" << originalPrice << ". Applied discount: " << discounts[bestVoucherIndex]->getPercent() << "% off";
        if (discounts[bestVoucherIndex]->getType() == DiscountType::BONUS_DISCOUNT)
        {
            BonusDiscount *bonusDsc = (BonusDiscount *)discounts[bestVoucherIndex];
            std::cout << " + €" << bonusDsc->getBonus() << " off";
        }
        std::cout << std::endl;
        std::cout << "Final price: €" << discountedPrice << std::endl;
    }
    else
    {
        std::cout << "Final price: €" << discountedPrice << std::endl;
    }

    Purchase newPurchase(nextPurchaseID++, cart, PurchaseStatus::PENDING, currentBuyer->getUserID(), discountedPrice);
    currentBuyer->addToPurchases(newPurchase);

    currentBuyer->clearCart();

    currentBuyer->removeDiscount(discounts[bestVoucherIndex]->getID()); // remove used Discount

    currentBuyer->addToBalance(-discountedPrice); // remove money from account

    Discount *newDiscount = generateNewDiscount(); // generate a new discount for the user
    currentBuyer->addToDiscounts(newDiscount);
}

void NotinOOP::handleCancelPurchase(int purchaseID)
{
    Buyer *currentBuyer = (Buyer *)activeUser;

    std::vector<Purchase> purchases = currentBuyer->getPurchases();

    for (int i = 0; i < purchases.size(); i++)
    {
        if (purchases[i].getPurchaseID() == purchaseID)
        {
            if (purchases[i].getStatus() == PurchaseStatus::DELIVERED)
            {
                std::cout << "This purchase is already delivered!" << std::endl;
                return;
            }
            else if (purchases[i].getStatus() == PurchaseStatus::CANCELLED)
            {
                std::cout << "This purchase is already cancelled!" << std::endl;
                return;
            }

            purchases[i].setStatus(PurchaseStatus::CANCELLED);

            Buyer *currentBuyer = (Buyer *)activeUser;
            currentBuyer->addToBalance(purchases[i].getFinalPrice()); // return money to account

            std::cout << "Purchase cancelled successfully!" << std::endl;
            return;
        }
    }
}

void NotinOOP::handleMakeReview(const std::string &fragranceName, double rating, const std::string &comment)
{
    Fragrance *foundFragrance = findFragranceByName(fragranceName);

    if (foundFragrance != nullptr)
    {
        Review newReview(nextReviewID++, fragranceName, activeUser->getUserID(), comment, rating);
        foundFragrance->addReview(newReview);
        std::cout << "Review added successfully to " << fragranceName << "!" << std::endl;
        return;
    }

    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleBlockUser(const std::string &username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getUsername() == username)
        {
            if (users[i]->getType() == UserType::ADMIN)
            {
                std::cout << "You can't block an admin!" << std::endl;
                return;
            }

            while (true)
            {
                std::cout << "This action will delete " << users[i]->getUsername() << "'s account. Are you sure you want to continue? (y/n): ";
                std::string answer;
                std::cin >> answer;
                Utils::toLower(answer);

                if (answer == "y")
                {
                    break;
                }
                else if (answer == "n")
                {
                    std::cout << "User not blocked!" << std::endl;
                    return;
                }
                else
                {
                    std::cout << "Invalid answer! Please type 'y' or 'n'." << std::endl;
                }
            }

            users.erase(users.begin() + i);
            std::cout << "User blocked successfully!" << std::endl;
            return;
        }
    }
    std::cout << "Username not found!" << std::endl;
}

void NotinOOP::handleCreateFragrance(const std::string &name, const std::string &brand, float price, const std::vector<size_t> &ingredientsList)
{
    Fragrance newFragrance(nextFragranceID++, name, brand, price, ingredientsList);
    catalogue.push_back(newFragrance);
    std::cout << "Fragrance created successfully! New Fragrance ID: " << newFragrance.getID() << std::endl;
}

void NotinOOP::handleAddQuantity(const std::string &fragranceName, int quantity)
{
    Fragrance *foundFragrance = findFragranceByName(fragranceName);
    if (foundFragrance != nullptr)
    {
        foundFragrance->addQuantity(quantity);
        std::cout << "Quantity added successfully! Current quantity: " << foundFragrance->getQuantity() << std::endl;
        return;
    }
    std::cout << "Fragrance not found!" << std::endl;
}

void NotinOOP::handleDeliverPurchase(int purchaseID)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getType() == UserType::BUYER)
        {
            Buyer *buyer = (Buyer *)users[i];
            std::vector<Purchase> &purchases = buyer->getPurchases();

            for (int j = 0; j < purchases.size(); j++)
            {
                Purchase &currentPurchase = purchases[j];
                if (currentPurchase.getPurchaseID() == purchaseID)
                {
                    if (currentPurchase.getStatus() == PurchaseStatus::CANCELLED)
                    {
                        std::cout << "This purchase is cancelled and cannot be delivered!" << std::endl;
                        return;
                    }
                    else if (currentPurchase.getStatus() == PurchaseStatus::DELIVERED)
                    {
                        std::cout << "This purchase is already delivered!" << std::endl;
                        return;
                    }

                    currentPurchase.setStatus(PurchaseStatus::DELIVERED);

                    std::cout << "Purchase delivered successfully!" << std::endl;
                    return;
                }
            }
        }
    }

    std::cout << "Purchase ID not found!" << std::endl;
}

void NotinOOP::handleRemoveReview(int fragranceId, int reviewId)
{
}

NotinOOP::NotinOOP()
{
    srand(time(0));
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
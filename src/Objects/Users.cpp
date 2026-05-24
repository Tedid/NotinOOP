#include "Objects/Users.hpp"
#include "util/utils.hpp"

#include <iostream>

void Buyer::removeFragranceFromVector(std::vector<Fragrance> &frags, const Fragrance &frag)
{
    for (size_t i = 0; i < frags.size(); i++)
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

UserType User::getType() const
{
    return type;
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
    type = UserType::BUYER;
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
    Utils::printFragrancesByType(cart, message.size());
}

void Buyer::clearCart()
{
    cart.clear();
}

void Buyer::addToPurchases(const Purchase &purchase)
{
    purchases.push_back(purchase);
}

void Buyer::addToDiscounts(Discount *discount)
{
    discounts.push_back(discount);
}

void Buyer::removeDiscount(size_t discountID)
{
    for (size_t i = 0; i < discounts.size(); i++)
    {
        if (discounts[i]->getID() == discountID)
        {
            discounts.erase(discounts.begin() + i);
            break;
        }
    }
}

// void Buyer::checkout()
// {
//     WRITE CHECK FOR SUFFICIENT FUNDS IN ENGINE

//     PASTE INTO COMMAND HANDLING:
//     if (cart.empty())
//     {
//         std::cout << "Cart is empty!" << std::endl;
//         return;
//     }

//     float finalPrice = 0.0f;
//     for (int i = 0; i < cart.size(); i++)
//     {
//         finalPrice += cart[i].getPrice();
//     }

//     int bestVoucherIndex = GetBestDiscountIndex();
//     if (bestVoucherIndex != -1)
//     {
//         finalPrice = FragrancesDiscountedPrice(cart, *discounts[bestVoucherIndex]);
//     }

//     if (this->balance < finalPrice)
//     {
//         std::cout << "Not enough money for the transaction!" << std::endl;
//         return;
//     }

//     this->balance -= finalPrice;

//     Purchase newPurchase();
// }

void Buyer::viewBought() const
{
    if (purchases.empty())
    {
        std::cout << "There aren't any past puchases";
        return;
    }

    bool areThereDeliveredPurchases = false;
    for (int i = 0; i <= purchases.size(); i++)
    {
        if (purchases[i].getStatus() == PurchaseStatus::DELIVERED)
        {
            areThereDeliveredPurchases = true;
            break;
        }
    }

    if (!areThereDeliveredPurchases)
    {
        std::cout << "There aren't any delivered purchases!";
        return;
    }

    std::string message = "Delivered orders: ";

    for (int i = 0; i <= purchases.size(); i++)
    {
        Purchase currentPurchase = purchases[i];
        if (currentPurchase.getStatus() == PurchaseStatus::DELIVERED)
        {
            currentPurchase.show(username);
        }
    }
}

void Buyer::viewPurchases() const
{
    if (purchases.empty())
    {
        std::cout << "There aren't any past puchases";
        return;
    }

    std::string message = "All orders: ";

    for (int i = 0; i <= purchases.size(); i++)
    {
        purchases[i].show(username);
    }
}

void Buyer::viewDiscounts() const
{
    if (discounts.empty())
    {
        std::cout << "There aren't any discounts!";
        return;
    }

    for (int i = 0; i < discounts.size(); i++)
    {
        Discount currentDiscount = *discounts[i];
        if (currentDiscount.getType() == DiscountType::DISCOUNT)
        {
            currentDiscount.view();
        }
        else if (currentDiscount.getType() == DiscountType::BONUS_DISCOUNT)
        {
            BonusDiscount *bonusDsc = (BonusDiscount *)&currentDiscount;
            bonusDsc->view();
        }
        else if (currentDiscount.getType() == DiscountType::BRAND_DISCOUNT)
        {
            BrandDiscount *brandDsc = (BrandDiscount *)&currentDiscount;
            brandDsc->view();
        }
        else
        {
            std::cout << "Unknown discunt type" << std::endl;
        }

        std::cout << std::endl;
    }
}

float Buyer::getBalance() const
{
    return balance;
}

std::vector<Fragrance> Buyer::getCart() const
{
    return cart;
}

std::vector<Purchase> &Buyer::getPurchases()
{
    return purchases;
}

std::vector<Discount *> Buyer::getDiscounts() const
{
    return discounts;
}

std::vector<Fragrance> Buyer::getWishlist() const
{
    return wishlist;
}

void Buyer::showHelp() const
{
    // Will be written in the end
}

Admin::Admin(size_t id, const std::string &name, const std::string &pass) : User(id, name, pass)
{
    type = UserType::ADMIN;
}

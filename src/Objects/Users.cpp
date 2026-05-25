#include "Objects/Users.hpp"
#include "util/utils.hpp"

#include <iostream>
#include <sstream>

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

Buyer::Buyer(size_t id, const std::string &name, const std::string &pass, float balance, int reviewsRemoved) : User(id, name, pass)
{
    this->balance = balance;
    this->reviewsRemoved = reviewsRemoved;
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

void Buyer::cancelPurchase(size_t purchaseID)
{
    for (size_t i = 0; i < purchases.size(); i++)
    {
        if (purchases[i].getPurchaseID() == purchaseID)
        {
            if (purchases[i].getStatus() == PurchaseStatus::PENDING)
            {
                purchases[i].setStatus(PurchaseStatus::CANCELLED);
                std::cout << "Purchase cancelled successfully!" << std::endl;
                return;
            }
            else
            {
                std::cout << "Only pending purchases can be cancelled!" << std::endl;
                return;
            }
        }
    }

    std::cout << "Purchase not found!" << std::endl;
}

void Buyer::incrementReviewsRemoved()
{
    reviewsRemoved++;
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

void Buyer::viewBought() const
{
    if (purchases.empty())
    {
        std::cout << "There aren't any past puchases" << std::endl;
        return;
    }

    bool areThereDeliveredPurchases = false;
    for (int i = 0; i < purchases.size(); i++)
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

    for (int i = 0; i < purchases.size(); i++)
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
        std::cout << "There aren't any past puchases" << std::endl;
        return;
    }

    std::string message = "All orders: ";

    for (int i = 0; i < purchases.size(); i++)
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

int Buyer::getReviewsRemoved() const
{
    return reviewsRemoved;
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
    std::cout << "Buyer help menu:" << std::endl;
    std::cout << " - add-to-balance <amount> - adds the specified amount to the user's balance" << std::endl;
    std::cout << " - add-to-wishlist <fragrance-name> - adds the fragrance with this name to the user's wishlist" << std::endl;
    std::cout << " - remove-from-wishlist <fragrance-name> - removes the fragrance with this name from the user's wishlist" << std::endl;
    std::cout << " - add-to-cart <fragrance-name> - adds the fragrance with this name to the user's cart" << std::endl;
    std::cout << " - remove-from-cart <fragrance-name> - removes the fragrance with this name from the user's cart" << std::endl;
    std::cout << " - view-cart - shows the contents of the cart" << std::endl;
    std::cout << " - view-bought - shows a list of all successful purchases" << std::endl;
    std::cout << " - view-purchases - shows a list of all purchases (PENDING, DELIVERED, or CANCELED)" << std::endl;
    std::cout << " - recommend <amount> - recommends fragrances based on the most liked note from the wishlist" << std::endl;
    std::cout << " - checkout - completes the purchase, empties the cart, and automatically applies the best discount" << std::endl;
    std::cout << " - cancel <purchase-id> - cancels a created order (only if its status is PENDING)" << std::endl;
    std::cout << " - make-review <fragrance-name> <rating> <comment> - creates a review for the given fragrance" << std::endl;
}

void Buyer::serialize(std::ostream &os) const
{
    // variables:
    os << "B|" << userID << "|" << username << "|" << password << "|" << balance << "|" << reviewsRemoved << "|";

    // wishlist
    if (wishlist.empty())
    {
        os << "empty";
    }
    else
    {
        for (int i = 0; i < wishlist.size(); i++)
        {
            os << wishlist[i].getID();
            if (i != wishlist.size() - 1)
            {
                os << " ";
            }
        }
    }
    os << "|";

    // cart
    if (cart.empty())
    {
        os << "empty";
    }
    else
    {
        for (int i = 0; i < cart.size(); i++)
        {
            os << cart[i].getID();
            if (i != cart.size() - 1)
            {
                os << " ";
            }
        }
    }
    os << "|";

    // discounts
    if (discounts.empty())
    {
        os << "empty";
    }
    else
    {
        for (int i = 0; i < discounts.size(); i++)
        {
            discounts[i]->serialize(os); // <type:ID:percent:bonus/brand>
            if (i != discounts.size() - 1)
            {
                os << " ";
            }
        }
    }

    // purchases
        if (purchases.empty())
        {
            os << "empty";
        }
        else
        {
            for (int i = 0; i < purchases.size(); i++)
            {
                // <purchaseID:<fragranceIDs>:fragranceID:status:userID:finalPrice>
                purchases[i].serialize(os);
                if (i != purchases.size() - 1)
                {
                    os << " ";
                }
            }
        }
}

Admin::Admin(size_t id, const std::string &name, const std::string &pass) : User(id, name, pass)
{
    type = UserType::ADMIN;
}

Admin::Admin(const std::string &str) : User(0, "", "")
{
    std::stringstream ss(str);
    size_t id;
    std::string username, password;

    ss >> id >> username >> password;

    userID = id;
    this->username = username;
    this->password = password;

    type = UserType::ADMIN;
}

void Admin::showHelp() const
{
    std::cout << "Admin help menu:" << std::endl;
    std::cout << " - block-user <username> - blocks the user with the specified username" << std::endl;
    std::cout << " - remove-review <fragrance-id> <review-id> - removes the review with the specified ID from the fragrance" << std::endl;
    std::cout << " - deliver <purchase-id> - marks the purchase with the specified ID as delivered" << std::endl;
    std::cout << " - create-fragrance <name> <brand> <price> <ingredient-id 1> <ingredient-id 2> ... - creates a new fragrance with the specified details" << std::endl;
    std::cout << " - remove-fragrance <fragrance-name> - removes the fragrance with the specified name from the catalogue" << std::endl;
    std::cout << " - add-quantity <fragrance-name> <quantity> - adds the specified quantity to the fragrance with this name" << std::endl;
    std::cout << " - print-ingredients - prints the list of available ingredients and their IDs" << std::endl;
}

void Admin::serialize(std::ostream &os) const
{
    os << "A|" << userID << "|" << username << "|" << password << std::endl;
}

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

};

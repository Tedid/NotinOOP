#pragma once

enum class PurchaseStatus
{
    PENDING,
    DELIVERED,
    CANCELLED
};

enum class DiscountType
{
    DISCOUNT,
    BONUS_DISCOUNT,
    BRAND_DISCOUNT
};

enum class UserType
{
    BUYER,
    ADMIN
};
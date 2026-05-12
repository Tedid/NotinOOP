#pragma once

class Discount{
    int discountID;     //unique
    float discountPercent;

    public:
    Discount(int id, float percent);

    void apply();
};

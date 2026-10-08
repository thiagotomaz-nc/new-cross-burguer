#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <iostream>

using namespace std;

class Product {
private:
    int barCode;
    string description;
    float unitPrice;

public:
    Product();
    Product(int barCode, string description, float unitPrice);

    int getBarCode();
    string getDescription();
    float getUnitPrice();

    void setBarCode(int newBarCode);
    void setDescription(string newDescription);
    void setUnitPrice(float newUnitPrice);

    void show();
};

#endif
#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <iostream>

using namespace std;

class Product {
private:
    int barCode;
    string name;
    float unitPrice;

public:
    Product();
    Product(int barCode, string name, float unitPrice);

    int getBarCode() const;
    string getName() const;
    float getUnitPrice() const;

    void setBarCode(int newBarCode);
    void setName(string newName);
    void setUnitPrice(float newUnitPrice);

    void show() const;
};

#endif
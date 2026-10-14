#include "../models/Product.hpp"

Product::Product() {}

int Product::getBarCode() const {
    return this->barCode;
}

string Product::getName() const {
    return this->name;
}

float Product::getUnitPrice() const {
    return this->unitPrice;
}

void Product::setBarCode(int newBarCode) {
    this->barCode = newBarCode;
}

void Product::setName(string newName) {
    this->name = newName;
}

void Product::setUnitPrice(float newUnitPrice) {
    this->unitPrice = newUnitPrice;
}

void Product::show() const {
    cout << this->barCode
         << "  |  " << this->name 
         << "   | R$ " << this->unitPrice;
}
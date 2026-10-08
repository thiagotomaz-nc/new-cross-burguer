#include "models/Product.hpp"

Product::Product() {
    this->barCode = 0;
    this->description = "";
    this->unitPrice = 0;
}

Product::Product(int barCode, string description, float unitPrice) {
    this->barCode = barCode;
    this->description = description;
    this->unitPrice = unitPrice;
}

int Product::getBarCode() {
    return this->barCode;
}

string Product::getDescription() {
    return this->description;
}

float Product::getUnitPrice() {
    return this->unitPrice;
}

void Product::setBarCode(int newBarCode) {
    this->barCode = newBarCode;
}

void Product::setDescription(string newDescription) {
    this->description = newDescription;
}

void Product::setUnitPrice(float newUnitPrice) {
    this->unitPrice = newUnitPrice;
}

void Product::show() {
    cout << endl;
    cout << "Nome: " << this->description
         << "| Código: " << this->barCode 
         << "| Valor: R$ " << this->unitPrice;

}
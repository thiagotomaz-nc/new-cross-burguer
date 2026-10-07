#include "Product.hpp"

Product::Product(int barCode, string description, double unitPrice, Product * nextProduct){
    this-> barCode = barCode;
    this-> description =description;
    this->unitPrice = unitPrice;
    this->nextProduct = nextProduct;
}

Product::Product(){}

int Product::getBarCode(){
    return this->barCode;
}

void Product::setBarCode(int newBarCode){
    this->barCode = newBarCode;
}

string Product::getDescription(){
    return this->description;
}

void Product::setDescription(string newDescription){
    this->description = newDescription;
}

Product* Product::getNext(){
    return this->nextProduct;
}

void Product::setNext(Product * product){
    this->nextProduct = product;
}  
  
float Product::getUnitPrice(){
    return this->unitPrice;
}

void Product::setUnitPrice(double newUnitPrice){
    this->unitPrice = newUnitPrice;
}

void Product::show(){
    cout<<this->barCode << " | " << this->description << " | " << this->unitPrice<<endl;
}
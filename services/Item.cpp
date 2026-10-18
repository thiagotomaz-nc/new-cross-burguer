#include "../models/Item.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Item::Item() {
    this->quantity = 0;
    this->priceTotalItems = 0.0;
}

void Item::setPriceTotalItem(float unitPrice) {
    if (unitPrice > 0) {
        this->priceTotalItems = this->quantity * unitPrice;
    } else {
        // Se a quantidade for maior que zero e o preço do produto for válido, calcula
        if (this->product.getUnitPrice() > 0 && this->quantity > 0) {
            this->priceTotalItems = this->quantity * this->product.getUnitPrice();
        } else {
            this->priceTotalItems = 0.0;
        }
    }
}

float Item::getPriceTotalItem() {
    return this->priceTotalItems;
}

int Item::getQuantityItem() {
    return this->quantity;
}

void Item::setQuantityItem(int newQuantity) {
    if (newQuantity > 0) {
        this->quantity = newQuantity;
        // Recalcula o total usando o preço do produto já associado ao item
        setPriceTotalItem(this->product.getUnitPrice());  
    } else {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "[" << newQuantity << "] valor invalido. Tente novamente!" << endl;       
        cout << "---------------------------------------------------------\n" << endl;
    }
}

pair<bool, Product> Item::getProductItem() {
    return {true, this->product};
}

void Item::setProductItem(Product newProduct) {
    this->product = newProduct;
    // Recalcula o total ao alterar o produto
    setPriceTotalItem(this->product.getUnitPrice());    
}

void Item::showItems(int numberItem) {
    cout << setfill('0') << setw(DECIMAL_PLACES) << numberItem + 1;
    // Reseta o setfill para espaço em branco para não afundar a formatação da linha
    cout << "     " << setfill('0') << setw(DECIMAL_PLACES) << this->product.getBarCode()  << "           " << this->product.getName() << "  "
         << "R$ " << this->product.getUnitPrice() << " x " << this->quantity << " = "
         << "R$ " << this->priceTotalItems << endl;
}
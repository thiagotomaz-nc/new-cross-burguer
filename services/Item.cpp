#include "../models/Item.hpp"


Item::Item(){}

void Item::setPriceTotalItem(int unitPrice) {
    if (unitPrice > 0) {
        this->priceTotalItems = getQuantityItem() * unitPrice;
    } else {
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<< "Total preco nao alterado. Verifique se o valor é negativo ou se esqueceu de intormar o produto e tente novmente!"<<endl;       
        cout<<"---------------------------------------------------------\n"<<endl;
    }
}

float Item::getPriceTotalItem() {
    return this->priceTotalItems;
}

int Item::getQuantityItem() {
    return this->quantity;
}

void Item::setQuantityItem(int newQuantity) {
    if (newQuantity > 0 ){
        this->quantity = newQuantity;
        this->setPriceTotalItem(this->product.getUnitPrice());  
    }else{
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<< "["<< newQuantity<<"] valor negativo invalido. Tente novmente!"<<endl;       
        cout<<"---------------------------------------------------------\n"<<endl;
    }
     // Recalcula o total ao alterar a quantidade
}

pair<bool, Product> Item::getProductItem() { // retorn o produto adicionado ao item
    return {true, this->product};
}

void Item::setProductItem(Product newProduct) { // tualiza o produto adicionado ao item;
        this->product = newProduct;
        // Recalcula o total ao alterar o produto
        setPriceTotalItem(this->product.getUnitPrice());    
}

   void Item::showItems(int numberItem){
    cout << setfill('0') << setw(DECIMAL_PLACES) << numberItem + 1 << "  " << this->product.getName() << "  "
                 << "R$ " << this->product.getUnitPrice() << " x " << this->quantity << " = "
                 << "R$ " << this->priceTotalItems << endl;
   }
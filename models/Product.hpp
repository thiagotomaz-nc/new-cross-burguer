#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <iostream>
#include <iomanip> 
#include "../enuns/enumStatusProduct.h"

#define DECIMAL_PLACES 4

using namespace std;

class Product {
private:
    int barCode;
    string name;
    float unitPrice;
    StatusProductCategories statusProductCategories;

public:
    Product();
    Product(int barCode, string name, float unitPrice);

    int getBarCode() const;
    string getName() const;
    float getUnitPrice() const;
    StatusProductCategories getStatusProductCategories() const;

    void setStatusProductCategories(StatusProductCategories newStatusProductCategories);
    void setStatusProductCategoriesNumber(int newStatusProductCategories);
    void setBarCode(int newBarCode);
    void setName(string newName);
    void setUnitPrice(float newUnitPrice);

    string statusProductToString(StatusProductCategories status) const;
    
    // const depois da função - garante que não vai modificar nenhuma variável ou propriedade do objeto que a chamou, transformando a função em somente LEITURA;
    // const antes da função - o valor que a função devolve não pode ser modificado;
    void printProduct() const;
};

#endif
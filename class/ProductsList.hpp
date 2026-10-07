#ifndef _PRODUCTS_LIST_HPP_
#define _PRODUCTS_LIST_HPP_

#include <string>
#include <iostream>
#include "Product.hpp"
#include <cctype>

using namespace std;

//lista simplesmente encadeada;
// responsabilidade: Gerenciar os produtos que serão exibidos no menu;
class ProductsList{

    private:
        Product * headProduct = nullptr; // marca qual o inicio do cabeça dos produtos;
        int n_elements = 0;       
        
    public:
        ProductsList();
        
        void addProduto(Product* newProduct);
        void updateProduct(Product* updateproduto, string newDescription, double newPrice);
        void removeProduct(int barCode);

        bool constainsBarCode(int codigoProduto);
        Product* searchProduct(int codigoProduto);
        void searchProductsName(string partName);
        void setNElements(int newNElements);
        int getNElements();
        string toLowerText(string text);

        Product* getHeadProduct();
        void setHeadProduct(Product* nextHeadProduct);

        bool isEmpty(); // lista vazia
        void setLength(int newLength);

        void showProducts(Product * head); // sber onde inicir a lista encadeda;

        ~ProductsList();
};

#endif
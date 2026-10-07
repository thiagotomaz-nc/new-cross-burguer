#ifndef _DRINKS_LIST_HPP_
#define _DRINKS_LIST_HPP_

#include <string>
#include <iostream>
#include "models/Product.hpp"
#include <cctype>

using namespace std;
#define LENGTH_DEFAULT 0
#define SIZE_DEFAULT 10

//lista simplesmente encadeada;
// responsabilidade: Gerenciar os produtos que serão exibidos no menu;
class DrinksList{

    private:
        Product * headProduct = nullptr; // marca qual o inicio do cabeça dos produtos;
        Product product; // ponteiro para o proximo produto da lista encadeada;
        int size ;
        int lenght;


    public:
        DrinksList();
        
        void addProduto(Product  product); 
        void reallocate();
        void updateProduct(Product* updateproduto, string newDescription, double newPrice);
        void removeProduct(int barCode);

        bool constainsBarCode(int codigoProduto);
        Product* searchProduct(int codigoProduto);
        void searchProductsName(string partName);
        void setSize(int newSize);
        int getSize();
        int getLength();
        int setLength(int newLength);
        string toLowerText(string text);

        Product* getHeadProduct();
        void setHeadProduct(Product* nextHeadProduct);

        bool isEmpty(); // lista vazia

        void showProducts(Product * head); // sber onde inicir a lista encadeda;

        ~DrinksList();
};

#endif
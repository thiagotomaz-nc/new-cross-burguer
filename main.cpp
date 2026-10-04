#include <iostream>
#include "class/Product.hpp"
#include "class/ProductsList.hpp"
#include "class/Order.hpp"
#include "class/Item.hpp"

#include <string>

using namespace std;


void AddProduct(ProductsList* productList);
void editProduct(ProductsList* productList);
void deleteProduct(ProductsList* productList);
void searchProductName(ProductsList* productList);
void menu(ProductsList* productList);
void homeOrder();
void menuDividers();

int main(){
    //inicio variaveis
    int response = 0;
    bool continuar = true;
    //cabeçalho que aponta para o primeiro elemento do propduto;    
    // *head = valor que head aponta;
    // head = Endereço apontado pelo ponteiro;
    // &head = Endereço do proprio ponteiro;
    ProductsList productsList;
    
    // Fim variaveis
    
    cout<<endl;
   
    //criar um menu, através dos produtos, podendo inclusive cadastrar novos produtos, editar, excluir (desativas), consultar
    do{
        menuDividers(); 
        cout << "New Cross Burguer" << endl;
        cout<<"====================================="<< endl;
        cout<<"informe uma opcao"<<endl;
        cout<<"1 - Iniciar pedido"<<endl;
        cout<<"2 - Cancelar pedido"<<endl;
        cout<<"3 - Gerenciar Menu"<<endl;
        cout<<"4 - Sair do sistema"<<endl;
        cin>>response;

        switch (response)
        {
        case 3:
            menu(&productsList);
            break;
        case 4:
            /* code */
            cout<<endl;
            cout<<"Saindo do sistema!!!\nAte mais!!"<<endl;
            cout<<endl;
            continuar=false;
            break;
        
        default:
            continue;
            break;
        }
    }while(continuar);

    return 0;
}

void menu(ProductsList* productList){
    int responseMenu=0;

    menuDividers();
    cout<<"Menu - Produtos cadastrados"<<endl;
    cout<<"**********************************************************"<<endl;
    productList->showProducts(productList->getHeadProduct());//lista todos os produtos da lista
    cout<< endl;
    
    cout<<"Informe uma opcao"<<endl;
    cout<<"**********************************************************"<<endl;
    cout<<"1 - Cadastrar um produto"<<endl;
    cout<<"2 - Editar um produto"<<endl;
    cout<<"3 - Remover um produto"<<endl; 
    cout<<"4 - Consultar um produto pelo nome "<<endl;
    cout<<"5 - Voltar ao menu principal"<<endl;
    cin >> responseMenu; 

    switch (responseMenu)
    {
    case 1:
        AddProduct(productList);
        break;
    case 3:
        deleteProduct(productList);
        break;
    case 2:
        editProduct(productList);
        break;
    case 4:
        searchProductName(productList);
        break;    
    default:
        break;
    }
}

void AddProduct(ProductsList* productList){
    char continueClear;
     // cabeça inicia em null, significa que não tem nenhum produto cadastrado na lista encadeada;
    string description;
    int barCode;
    double price;
    
    //Criação do objeto de forma dinamica do objeto da classe produto;
    Product product;
    cin.ignore();

    menuDividers();

    cout<<"Cadastrar produto "<<endl;
    cout<<"**********************************************************"<<endl;
     cout<<"Informe o CODIGO do produto: ";
    cin>>barCode;
    cin.ignore();
    cout<<"Informe o NOME do produto: ";
    getline(cin, description);
    cout<<"Informe o VALOR UNITARIO do produto: ";
    cin>>price;
   

    // validação aqui
    // Objeto criado e instanciado;
    // Não precisa destruir, pois é uma vriavel local que vai ser destruida com o metodo;
    product.setDescription(description);
    product.setBarCode(barCode);
    product.setUnitPrice(price);

    productList->addProduto(&product);

    cout<<"pressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..."<<endl;
    cin >> continueClear;

    if(continueClear == 's' || continueClear == 'S' ){
        system("clear");
    }
        
    menu(productList);          
     
}

void editProduct(ProductsList* productList){
    char continueClear;
     // cabeça inicia em null, significa que não tem nenhum produto cadastrado na lista encadeada;
    string newDescription;
    double newPrice;
    int barCode;
    
    //Criação do objeto de forma dinamica do objeto da classe produto;
    
    cin.ignore();

    menuDividers();

    cout<<"Editar produto "<<endl;
    cout<<"********************************** "<<endl;
    cout<<"Informe o CODIGO do produto: ";
    cin>>barCode;

    cin.ignore();
    Product* updateProductList = productList->searchProduct(barCode);
    
    if (updateProductList != nullptr){
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"Produto "<< updateProductList->getBarCode()<< " selecionado!"<<endl;
        cout<<"**********************************************************"<<endl;
        cout<<"Informe o novo NOME do produto OU tecle [ENTER] para manter o mesmo nome: ";
        getline(cin, newDescription);
        cout<<"Informe o novo VALOR UNITARIO do produto ou digite [0] zero para manter o mesmo valor: ";
        cin >> newPrice;
        //poderia realizar as atualizações pelo updateProduct
        productList->updateProduct(updateProductList,newDescription,newPrice);


    }else{
        cout<<"\n---------------------------------------------------------"<<endl;
        cout<<"Produto não encontrado!"<<endl;
        cout<<"---------------------------------------------------------\n"<<endl;
    }

    cout<<"pressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..."<<endl;
    cin >> continueClear;

    if(continueClear == 's' || continueClear == 'S' ){
        system("clear");
    }
        
    menu(productList);
}

void deleteProduct(ProductsList* productList){
    char continueClear;
    int barCode;
    
    cin.ignore();

    menuDividers();

    cout<<"Deletar produto "<<endl;
    cout<<"********************************** "<<endl;
    cout<<"Informe o CODIGO do produto: ";
    cin>>barCode;

    cin.ignore();
    
    productList->removeProduct(barCode);

    cout<<"pressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..."<<endl;
    cin >> continueClear;

    if(continueClear == 's' || continueClear == 'S' ){
        system("clear");
    }
        
    menu(productList);
}

// Listar todos os produtos que contenham parte de uma palavra
void searchProductName(ProductsList* productList){
    char continueClear;
    string partName;
    
    cin.ignore();

    menuDividers();

    cout<<"Consultar produto "<<endl;
    cout<<"********************************** "<<endl;
    cout<<"Informe o NOME do produto: ";
    getline(cin,partName);

    
    productList->searchProductsName(partName);

    cout<<"pressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..."<<endl;
    cin >> continueClear;

    if(continueClear == 's' || continueClear == 'S' ){
        system("clear");
    }
        
    menu(productList);
}

void menuDividers(){
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<endl;
}
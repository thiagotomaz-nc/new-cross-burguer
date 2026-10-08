#include "models/Product.hpp"
#include "models/Order.hpp"
#include "models/Item.hpp"

#include <iostream>
#include <vector>

using namespace std;

/*
void AddProduct(vector<Product> menu);
void editProduct(vector<Product> menu);
void deleteProduct(vector<Product> menu);
void searchProductName(vector<Product> menu);
void menu(vector<Product> menu);
void searchProductBarCode(vector<Product> menu);  //metodo de busca por codigo de barras
*/

//void homeOrder();
void menuDividers();

void exibirProdutos(vector<Product>& menu);
void AddProduct(vector<Product>& menu);
void menu(vector<Product>& menu);

int main(){
    //inicio variaveis
    int response = 0;
    bool continuar = true;
    Product product;
    vector<Product> Menu;
    //products.add(product);
    
    //cabeçalho que aponta para o primeiro elemento do propduto;    
    // *head = valor que head aponta;
    // head = Endereço apontado pelo ponteiro;
    // &head = Endereço do proprio ponteiro;
    
    
    // Fim variaveis
    
    cout<< endl;
   
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
        cout << "\nDigite a opção desejada: ";
        cin>>response;

        switch (response)
        {
        case 3:
            menu(Menu);
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

void menu(vector<Product>& menu){
    int responseMenu=0;

    menuDividers();
    cout<<"Menu - Produtos cadastrados"<<endl;
    cout<<"**********************************************************"<<endl;
    //lista todos os produtos da lista
    exibirProdutos(menu);
    cout<< "\n\n";
    cout<<"Informe uma opcao"<<endl;
    cout<<"**********************************************************"<<endl;
    cout<<"1 - Cadastrar um produto"<<endl;
    cout<<"2 - Editar um produto"<<endl;
    cout<<"3 - Remover um produto"<<endl; 
    cout<<"4 - Consultar um produto pelo nome "<<endl;
    cout<<"5 - Voltar ao menu principal"<<endl;
    cout << "\nDigite a opção desejada: ";
    cin >> responseMenu; 

    switch (responseMenu)
    {
    case 1:
        AddProduct(menu);
        break;
/*    case 3:
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
        */
    }
}



void AddProduct(vector<Product>& menu){
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

    menu.push_back(product);

    exibirProdutos(menu);

    cout<<"\n\npressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..."<<endl;
    cin >> continueClear;

    if(continueClear == 's' || continueClear == 'S' ){
        system("clear");
    }   
}



/*
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

*/

void exibirProdutos(vector<Product> &menu) {
    for (size_t i = 0; i < menu.size(); i++) {  // size_t é um inteiro positivo (unsigned) usado pelo C++ para tamanhos e índices de vetores
        menu[i].show(); // Em C++ usa-se menu[i] em vez de menu.get(i)
    }   
}

void menuDividers(){
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<endl;
}
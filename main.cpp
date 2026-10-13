#include "models/Product.hpp"
#include "models/Order.hpp"
#include "models/Item.hpp"

#include <iostream>
#include <vector>

using namespace std;

void showProducts(vector<Product>& menu);

// menus
void menuProducts(vector<Product>& menu);
void menuOrder(vector<Order>& orders,vector<Product>& menu);
void menuCancelOrder(vector<Order>& menu);
void menuAddProduct(vector<Product>& menu);
void menuEditProduct(vector<Product>& menu);
void menuDeleteProduct(vector<Product>& menu);
void searchProductName(vector<Product>& menu);
int searchProductBarCode( vector<Product>& menu);
bool productExists(vector<Product>& menu, int barCode);
bool productExistsName(vector<Product>& menu, const string& name);


// orders
void showOrders(vector<Order>& order);
int searchOrderNumber(vector<Order>& order);

//configurações
void deleteTerminal();
void menuDividers();

int main(){
    //inicio variaveis
    int response = 0;
    bool continuar = true;
    Product product;
    vector<Product> menu_products;
    vector<Order> orders;
    
        
    cout<< endl;
   
    //criar um order, através dos produtos, podendo inclusive cadastrar novos produtos, editar, excluir (desativas), consultar
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
        case 1:
            menuOrder(orders,menu_products);
            break;
        case 2:
            menuCancelOrder(orders);
            break;
        case 3:
            menuProducts(menu_products);
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

// =======================================================
// MENU PEDIDOS
// =======================================================
//Menu de gerenciamento dos pedidos
void menuOrder(vector<Order>& orders, vector<Product>& menu) {
    cout << "Digite os produtos e a quantidade que deseja comprar: " << endl;
    cout << "****************************************" << endl;
    int barCode;

     (void)orders;
    (void)menu;
  
    // peguntar sobre o produto;
    // informar o produto completo por código do produto;
    // informar a quantidade 
    // fechar o pedido
    // informar o nome do cliente
    // informar a mesa do cliente
    
    cout << "\nDeseja adicionar um novo produto ao pedido?(s/n): ";
        char confirm;
        cin >> confirm;

        while(confirm == 's' || confirm == 'S') {
            cout << "Informe o CODIGO do produto: ";
            cin >> barCode;

        }

    while(true) {
        
        cout << "Informe o CODIGO do produto: ";
        cin >> barCode;
       
        /*
        item.setBarCode(order[productIndex].getBarCode());
        item.setName(order[productIndex].getName());
        item.setPrice(order[productIndex].getUnitPrice());
        order.addItemToOrder(item);
        orders.push_back(order);
        */
    }
}

// função cancelar Pedido
void menuCancelOrder(vector<Order>& orders ){
    char continueClear;

    // Chama a busca por código, que já pede o código do produto e retorna a posição
    int OrderIndex = searchOrderNumber(orders);
    
    cout << "Cadastrar produto " << endl;
    cout << "**********************************************************" << endl;
    
    // Se o índice for 0 ou maior, o produto existe na lista
    if (OrderIndex >= 0) {
        cout << "\nTem certeza que deseja apagar o produto: " 
             << orders[OrderIndex].getNumberOrder() << "? (s/n): ";
        
        char confirm;
        cin >> confirm;

        if (confirm == 's' || confirm == 'S') {
            // Apaga o produto do vetor usando o iterador
            orders.erase(orders.begin() + OrderIndex);
            cout << "\n---------------------------------------------------------" << endl;
            cout << "Produto removido com sucesso!" << endl;
            cout << "---------------------------------------------------------" << endl;
        } else {
            cout << "\nOperacao cancelada." << endl;
        }
    }

    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S') {
        deleteTerminal();
    }  

}

int searchOrderNumber(vector<Order>& order){
    (void) order;
    return 1;
}

//Listar todos os produtos cadastrados no sistema
void showOrders(vector<Order>& order) {
    if (order.size() > 0){
    cout<< "\nnúmero do pedido | descrição | Valor"<<endl;
    cout<< "-------------------"<<endl;
    for (size_t i = 0; i < order.size(); i++) {  // size_t é um inteiro positivo (unsigned) usado pelo C++ para tamanhos e índices de vetores
        order[i].showOrder();
        cout<<"\n"; // Em C++ usa-se order[i] em vez de order.get(i)
    }
    }else{
        cout<<"\nNenhum produto cadastrado.\n";
    }
}

// =======================================================
// MENU PRODUTOS
// =======================================================
//Menu de gerenciamento dos produtos
void menuProducts(vector<Product>& menu){
    int responseMenu=0;

    menuDividers();
    cout<<"Menu - Produtos cadastrados"<<endl;
    cout<<"**********************************************************"<<endl;
    cout<< "\n";

    cout<<"Informe uma opcao"<<endl;
    cout<<"**********************************************************"<<endl;
    cout<<"1 - Cadastrar um produto"<<endl;
    cout<<"2 - Editar um produto"<<endl;
    cout<<"3 - Remover um produto"<<endl; 
    cout<<"4 - Consultar um produto pelo nome"<<endl;
    cout<<"5 - Consultar lista de produtos cadastrados"<<endl;
    cout<<"6 - Voltar ao order principal"<<endl;
    cout << "\nDigite a opção desejada: ";
    cin >> responseMenu; 

    switch (responseMenu)
    {
    case 1:
        menuAddProduct(menu);
        break;
    case 2:
        menuEditProduct(menu);
        break;
    case 3:
        menuDeleteProduct(menu);
        break;
    case 4:
        searchProductName(menu);
        break;
    case 5:
        menuDividers();
        cout<<"Menu - Produtos cadastrados"<<endl;
        cout<<"**********************************************************"<<endl;
        showProducts(menu);
        cout<< "\n";
        break;  
    default:
        break;
    }
}

//Adicionar um produto ao order
void menuAddProduct(vector<Product>& menu){
    char continueClear;
    string name;
    int barCode;
    double price;
    Product product;

    menuDividers();

    cout << "Cadastrar produto " << endl;
    cout << "**********************************************************" << endl;

    //Loop para garantir a inserção de um código válido e único
    do {
        cout << "Informe o CODIGO do produto: ";
        cin >> barCode;

        if (barCode < 0) {
            cout << "\n---------------------------------------------------------\n";
            cout << "[Erro] O codigo de barras deve ser positivo! Tente novamente.\n";
            cout << "---------------------------------------------------------\n\n";
        } 
        else if (productExists(menu, barCode)) {
            cout << "\n---------------------------------------------------------\n";
            cout << "[Erro] Ja existe um produto cadastrado com o codigo " << barCode << "! Tente novamente.\n";
            cout << "---------------------------------------------------------\n\n";
        }
    } while (barCode < 0 || productExists(menu, barCode));

    // Limpa o \n deixado pelo cin >> barCode antes de entrar no getline
    cin.ignore();

    //Loop para garantir a inserção de um nome válido e único
    do {
        cout << "Informe o NOME do produto: ";
        getline(cin, name);

        if (name.empty() || name.find_first_not_of(" \t\n\r") == string::npos) {
            cout << "\n---------------------------------------------------------\n";
            cout << "[Erro] O nome do produto deve ser diferente de vazio! Tente novamente.\n";
            cout << "---------------------------------------------------------\n\n";
        } else if (productExistsName(menu, name)) {
            cout << "\n---------------------------------------------------------\n";
            cout << "[Erro] Ja existe um produto cadastrado com o nome " << name << "! Tente novamente.\n";
            cout << "---------------------------------------------------------\n\n";
        }
    } while (name.empty() || name.find_first_not_of(" \t\n\r") == string::npos || productExistsName(menu, name));


    //Loop para garantir a inserção de um preço válido (positivo)
    do {
        cout << "Informe o VALOR UNITARIO do produto: ";
        cin >> price;

        if (price < 0) {
            cout << "\n---------------------------------------------------------\n";
            cout << "[Erro] O valor unitario deve ser positivo! Tente novamente.\n";
            cout << "---------------------------------------------------------\n\n";
        } 
    } while (price < 0);

    // Salva os dados no objeto
    product.setName(name);
    product.setBarCode(barCode);
    product.setUnitPrice(price);
    
    // Adiciona o produto ao final do vetor (order)
    menu.push_back(product);

    cout << "\n---------------------------------------------------------" << endl;
    cout << "Produto cadastrado com sucesso!" << endl;
    cout << "---------------------------------------------------------" << endl;

    cout << "\npressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S') {
       deleteTerminal();
    }   
}


//Editar um produto do order
void menuEditProduct(vector<Product>& menu) {
    char continueClear;
    string newName;
    double newPrice;

    // Chama a busca que pede o código e retorna o índice (posição no vetor)
    int productIndex = searchProductBarCode(menu);

    // Valida se o produto foi encontrado (>= 0 inclui o índice 0)
    if (productIndex >= 0) {
        cout << "\n---------------------------------------------------------\n";
        cout << "Produto " << menu[productIndex].getBarCode() << " selecionado!\n";
        cout<< "\nCodigo | Nome | Valor"<<endl;
        cout<< "-------------------"<<endl;
        menu[productIndex].show();  
        cout << "\n---------------------------------------------------------\n";
         
        cin.ignore(); // Limpa o buffer do cin para ler o getline sem pular
        
        cout << "\nInforme o novo NOME do produto OU tecle [ENTER] para manter o mesmo nome: ";
        getline(cin, newName);
        cout << "Informe o novo VALOR UNITARIO do produto ou digite [0] zero para manter o mesmo valor: ";
        cin >> newPrice;
        

        //Atualiza o preço apenas se for digitado um valor maior que zero
        if (!newName.empty()){
             menu[productIndex].setName(newName);
        }
        if (newPrice>0){
            menu[productIndex].setUnitPrice(newPrice);
        }
        

        cout << "\n---------------------------------------------------------" << endl;
        cout << "Produto atualizado com sucesso!" << endl;
        cout << "---------------------------------------------------------" << endl;

        cout<< "\nCodigo | Nome | Valor"<<endl;
        cout<< "-------------------"<<endl;
        menu[productIndex].show();
        cout << "\n\n";

    } else {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "Produto nao encontrado!" << endl;
        cout << "---------------------------------------------------------\n" << endl;
    }

    cout << "pressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S') {
        deleteTerminal();
    }
}


//Deletar um produto do menu
void deleteProduct(vector<Product>& menu) {
    char continueClear;

    // Chama a busca por código, que já pede o código do produto e retorna a posição
    int productIndex = searchProductBarCode(menu);

    // Se o índice for 0 ou maior, o produto existe na lista
    if (productIndex >= 0) {
        cout << "\nTem certeza que deseja apagar o produto: " 
             << menu[productIndex].getName() << "? (s/n): ";
        
        char confirm;
        cin >> confirm;

        if (confirm == 's' || confirm == 'S') {
            // Apaga o produto do vetor usando o iterador
            menu.erase(menu.begin() + productIndex);
            cout << "\n---------------------------------------------------------" << endl;
            cout << "Produto removido com sucesso!" << endl;
            cout << "---------------------------------------------------------" << endl;
            showProducts(menu);
        } else {
            cout << "\nOperacao cancelada." << endl;
        }
    }

    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S') {
        deleteTerminal();
    }   
}

//Listar todos os produtos que contenham parte de uma palavra
void searchProductName( vector<Product>& menu){    
    char continueClear;
    string partName;
    
    cin.ignore();

    menuDividers();

    cout<<"Consultar produto "<<endl;
    cout<<"********************************** "<<endl;
    cout<<"Informe o NOME do produto: ";
    getline(cin,partName);

    bool found = false;
    cout<< "\nCodigo | Nome | Valor"<<endl;
    cout<< "-------------------"<<endl;
    for (size_t i = 0; i < menu.size(); i++) {
        // Verifica se o texto digitado em 'partName' está contido na descrição
        if (menu[i].getName().find(partName) != string::npos) {
            menu[i].show();
            cout << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "\nNenhum produto encontrado com o termo: \"" << partName << "\"\n";
        cout << "---------------------------------------------------------\n" << endl;
    }

    cout<<"\npressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..."<<endl;
    cin >> continueClear;

    if(continueClear == 's' || continueClear == 'S' ){
       deleteTerminal();
    }
        
}

//Listar todos os produtos que contenham esse código de barras
int searchProductBarCode(vector<Product>& menu) {
    int barCode;
    int foundIndex = -1; // Inicializa o índice como -1, indicando que não foi encontrado
    
    menuDividers();
    cout<<"Consultar produto "<<endl;
    cout<<"********************************** "<<endl;
    cout<<"Informe o CODIGO do produto: ";
    cin>>barCode;

    for (size_t i = 0; i < menu.size(); i++) {
        if (menu[i].getBarCode() == barCode) {
            foundIndex = i; // Salva o índice onde o produto está
            break;          // Encontrou, para o loop
        }
    }

    if (foundIndex == -1) {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "\nProduto com o codigo " << barCode << " nao encontrado!" << endl;
        cout << "---------------------------------------------------------\n" << endl;
    }

    return foundIndex; // Retorna o índice do produto encontrado ou -1 se não encontrado
}

//Listar todos os produtos cadastrados no sistema
void showProducts(vector<Product>& menu) {
    if (menu.size() > 0){
    cout<< "\nCodigo | Nome | Valor"<<endl;
    cout<< "-------------------"<<endl;
    for (size_t i = 0; i < menu.size(); i++) {  // size_t é um inteiro positivo (unsigned) usado pelo C++ para tamanhos e índices de vetores
        menu[i].show();
        cout<<"\n"; // Em C++ usa-se order[i] em vez de order.get(i)
    }
    }else{
        cout<<"\nNenhum produto cadastrado.\n";
    }
}

//Verifica se o produto existe no order pelo código de barras, mas sem retornar texto
bool productExists( vector<Product>& menu, int barCode) {
    for (size_t i = 0; i < menu.size(); i++) {
        if (menu[i].getBarCode() == barCode) {
            return true;
        }
    }
    return false;
}

// Nova versão do productExists, mas para NOME (mesmo nome de função, parâmetros diferentes)
bool productExistsName(vector<Product>& menu, const string& name) {
    for (size_t i = 0; i < menu.size(); i++) {
        if (menu[i].getName() == name) { // Compara se os nomes são idênticos
            return true;
        }
    }
    return false;
}

// =======================================================
// CONFIGURÇÕES
// =======================================================
void menuDividers(){
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<endl;
}

void deleteTerminal(){
    system("cls");
}
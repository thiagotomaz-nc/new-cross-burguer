#include "models/Product.hpp"
#include "models/Order.hpp"
#include "models/Item.hpp"
#include "models/OrderHistoryList.hpp"
#include "models/OrderPreparationQueue.hpp"
#include "models/OrderPickupStack.hpp"

#include "enuns/enumStatusOrder.h"

#include <iostream>
#include <vector>

using namespace std;

// menus Produtos
void menuAddProduct(vector<Product> &menu);
void menuEditProduct(vector<Product> &menu);
void menuDeleteProduct(vector<Product> &menu);
void searchProductName(vector<Product> &menu);
int searchProductBarCode(vector<Product> &menu);
int getProductIndex(const vector<Product> &menu, int barCode);
bool productExists(const vector<Product> &menu, int barCode);
bool productExistsName(vector<Product> &menu, const string &name);
void showProducts(vector<Product> &menu);
void menuProducts(vector<Product> &menu);

// Menus historicos
void menuManageOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *orderHistoryList, OrderPreparationQueue &orderPreparationQueue, int *orderNumber);
void menuManagerHistory(OrderHistoryList *orderHistoryList);
void resumeHistory(OrderHistoryList *orderHistoryList);
void menuCancelOrderHistory(OrderHistoryList *orderHistoryList);
void searchOrderByNumber(OrderHistoryList *orderHistoryList);
void searchOrderByName(OrderHistoryList *orderHistoryList);

// orders
void showOrders(vector<Order> &order);
void menuAddOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *orderHistoryList, OrderPreparationQueue &orderPreparationQueue, int *orderNumber);
void menuCancelOrder(vector<Order> &orders);
void menuEditOrder(vector<Order> &orders, vector<Product> &menu);
void menuAddOrderItem(vector<Order> &orders, vector<Product> &menu);
void menuRemoveOrderItem(vector<Order> &orders, vector<Product> &menu);
void closeOrder(vector<Order> &orders, int indexOrder, Order *order, OrderHistoryList *OrderHistoryList, OrderPreparationQueue &orderPreparationQueue);
int searchOrderIndex(vector<Order> &orders);

// Cozinha
void menuKitchen(OrderPreparationQueue *orderPreparationQueue, vector<Order *> &kitchen, OrderPickupStack &orderPickupStack);
void menuPickupStack(OrderPickupStack &orderPickupStack);

// configurações
void deleteTerminal();
void menuDividers();
void messagesSucess(string messsage);
void messagesErrorsWarning(string messsage);

// CADASTROS PRÉVIOS
void previousRegistrations(vector<Order> &orders, vector<Product> &menu, OrderHistoryList &orderHistory, OrderPreparationQueue &orderPreparationQueue);

int main()
{
    // inicio variaveis
    int response = 0, numberOrder = 0;
    bool continuar = true;
    Product product;
    vector<Product> menu_products;
    vector<Order> orders;
    vector<Order *> kitchen;

    OrderHistoryList orderHistoryList;
    OrderPreparationQueue orderPreparationQueue;
    OrderPickupStack orderPickupStack;

    previousRegistrations(orders, menu_products, orderHistoryList, orderPreparationQueue);

    cout << endl;

    // criar um order, através dos produtos, podendo inclusive cadastrar novos produtos, editar, excluir (desativas), consultar
    do
    {
        cout << "\nNew Cross Burguer - HOME" << endl;
        cout << "**********************************************************" << endl;
        cout << "1 - Pedidos" << endl;
        cout << "2 - Produtos da Hamburgueria" << endl;
        cout << "3 - Historico" << endl;
        cout << "4 - Cozinha" << endl;
        cout << "5 - Fila de retirada" << endl;
        cout << "10 - Sair do sistema" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "\nDigite a opcao desejada: ";
        cin >> response;

        switch (response)
        {
        case 1:
            menuManageOrder(orders, menu_products, &orderHistoryList, orderPreparationQueue, &numberOrder);
            break;
        case 2:
            menuProducts(menu_products);
            break;
        case 3:
            menuManagerHistory(&orderHistoryList);            
            break;
        case 4:
            menuKitchen(&orderPreparationQueue, kitchen, orderPickupStack);
            break;
        case 5:
            menuPickupStack(orderPickupStack);
            break;
        case 10:
            cout << endl;
            cout << "Saindo do sistema!!!\nAte mais!!" << endl;
            cout << endl;
            continuar = false;
            break;
        default:
            messagesErrorsWarning("Opcao invalida! Tente novamente.");
            continue;
            break;
        }
    } while (continuar);

    return 0;
}

// =======================================================
// MENU gerenciar PEDIDOS - Editar pedido
// =======================================================
// Menu de gerenciamento dos pedidos
void menuManageOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *orderHistoryList, OrderPreparationQueue &orderPreparationQueue, int *orderNumber)
{

    int responseMenuOrder = 0;

    menuDividers();

    cout << "Menu - Gerenciar Pedidos" << endl;
    cout << "**********************************************************" << endl;
    cout << "1 - Adicionar um pedido" << endl;
    cout << "2 - Cancelar pedido" << endl;
    cout << "3 - Editar pedido" << endl;
    cout << "4 - Fechar um pedido " << endl;
    cout << "5 - Consultar lista de produtos cadastrados" << endl;
    cout << "6 - Exibir pedidos em construcao" << endl;
    cout << "7 - Voltar ao menu principal" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "\nDigite a opcao desejada: ";
    cin >> responseMenuOrder;
    cout << "---------------------------------------------------------" << endl;

    switch (responseMenuOrder)
    {
    case 1:
        menuAddOrder(orders, menu, orderHistoryList, orderPreparationQueue, orderNumber);
        break;
    case 2:
        menuCancelOrder(orders);
        break;
    case 3:
        menuEditOrder(orders, menu);
        break;
    case 4:
    {
        // Procura o pedido pelo NUMERO e retorna o índice correto no vetor 'orders'
        int index = searchOrderIndex(orders);

        if (index >= 0)
        {
            Order *order = &orders[index];
            cout << "\nPedido N. " << order->getNumberOrder() << " selecionado!" << endl;

            // Se já estiver fechado por algum motivo
            if (order->getStatusOrder() == StatusOrder::FECHADO)
            {
                messagesErrorsWarning("Atencao: o pedido N. " + to_string(order->getNumberOrder()) + " ja esta fechado!");
            }
            else
            {
                // Fecha o pedido, move para o histórico e remove do vetor central
                closeOrder(orders, index, order, orderHistoryList, orderPreparationQueue);
            }
        }
        break;
    }
    case 5:
        showProducts(menu);
        break;
    case 6:
        menuDividers();
        cout << "RELATORIO DOS PEDIDOS EM CONSTRUCAO" << endl;
        cout << "**********************************************************" << endl;
        if (orders.size() > 0)
        {

            for (size_t i = 0; i < orders.size(); i++)
            { // size_t é um inteiro positivo (unsigned) usado pelo C++ para tamanhos e índices de vetores
                orders[i].showResumeOrder();
                cout << "\n"; // Em C++ usa-se order[i] em vez de order.get(i)
            }
            cout << "**********************************************************" << endl;
        }
        else
        {
            messagesSucess("Nenhum produto em construção cadastrado.");
        }

        break;
    default:
        break;
    }
}

void menuEditOrder(vector<Order> &orders, vector<Product> &menu)
{

    int responseMenuEditOrder = 0;

    cout << "\nMenu - Editar pedido" << endl;
    cout << "**********************************************************" << endl;
    cout << "1 - Adicionar um item" << endl;
    cout << "2 - Remover um item" << endl;
    cout << "3 - Editar o nome do cliente " << endl;    
    cout << "4 - Editar a mesa " << endl;
    cout << "5 - Sair" << endl;
    cout << "\nDigite a opção desejada: ";
    cin >> responseMenuEditOrder;

    switch (responseMenuEditOrder)
    {
    case 1:
        menuAddOrderItem(orders, menu);
        break;
    case 2:
        menuRemoveOrderItem(orders, menu);
        //  ao remover o item deve colocar ele na pilha de ação e caso o cliente mude ele é recolocado no pedido
        break;
    case 3: // Editar Nome do Cliente
    {
        int orderIndex = searchOrderIndex(orders);
        if (orderIndex < 0) break;

        Order *order = &orders[orderIndex];
        messagesSucess("pedido: " + to_string(order->getNumberOrder()) + " selecionado!");

        cin.ignore();
        string newName = "";
        cout << "\nInforme o novo nome do cliente: ";
        getline(cin, newName);

        if (!newName.empty())
        {
            order->setNameClient(newName);
            messagesSucess("Nome do cliente atualizado com sucesso!");
        }
        else
        {
            messagesErrorsWarning("[Erro] O nome nao pode ser vazio!");
        }
    }
    break;

    case 4: // Editar Mesa
    {
        int orderIndex = searchOrderIndex(orders);
        if (orderIndex < 0) break;

        Order *order = &orders[orderIndex];
        messagesSucess("pedido: " + to_string(order->getNumberOrder()) + " selecionado!");

        int numBerTable = 0;
        cout << "\nInforme o novo numero da mesa: ";
        cin >> numBerTable;

        if (numBerTable > 0)
        {
            order->setNumberTable(numBerTable);
            messagesSucess("Mesa atualizada com sucesso!");
        }
        else
        {
            messagesErrorsWarning("[Erro] Numero de mesa invalido!");
        }
    }   
        break;
    
    default:
        break;
    }
}


// Menu de cadastro de pedidos
void menuAddOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *history, OrderPreparationQueue &orderPreparationQueue, int *orderNumber)
{
    int barCode;
    char confirm;
    int quantity;

    menuDividers();
    cout << "Menu - Cadastrar pedido(s)" << endl;
    cout << "**********************************************************" << endl;

    Order currentOrder;

    // Loop para adicionar todos os itens do pedido
    do
    {
        cout << "Informe o CODIGO do produto: ";
        cin >> barCode;

        if (!productExists(menu, barCode))
        {
            cout << "\nNenhum produto cadastrado com esse codigo.\n";
            cout << "\nDeseja tentar outro codigo? (s/n): ";
            cin >> confirm;
            continue;
        }

        int index = getProductIndex(menu, barCode);

        cout << "\nProduto selecionado: " << endl;
        cout << "\nCodigo | Nome | Valor" << endl;
        cout << "-------------------------------------------" << endl;

        menu[index].show();
        cout << "-------------------------------------------" << endl;
        cout << "\nDigite a quantidade desejada: ";
        cin >> quantity;

        if (quantity > 0)
        {
            Item newItem;
            newItem.setProductItem(menu[index]);
            newItem.setQuantityItem(quantity);
            cout << "\n-------------------------------------------" << endl;
            cout << "-> Subtotal do Item: R$ " << newItem.getPriceTotalItem() << endl;

            currentOrder.addItemToOrder(newItem);
        }
        else
        {
            messagesErrorsWarning("[ERRO] A quantidade deve ser maior que zero!");
            return;
        }
        cout << "-------------------------------------------" << endl;
        cout << "\nDeseja adicionar mais um produto ao pedido?(s/n): ";
        cin >> confirm;
    } while (confirm == 's' || confirm == 'S');

    menuDividers();

    // Lê os dados cadastrais
    string clientName;
    int clientSeat;

    cout << "\nDigite o nome do cliente: ";
    cin >> clientName;
    cout << "Digite o numero da mesa: ";
    cin >> clientSeat;

    // Atribui o número sequencial correto
    // Garante uma sequência exata: 1, 2, 3, 4, 5...
    (*orderNumber)++;

    currentOrder.setNumberOrder(*orderNumber);
    currentOrder.setNameClient(clientName);
    currentOrder.setNumberTable(clientSeat);
    currentOrder.sumTotalPriceToOrder();

    // Chama a função de fechamento do pedido recém-criado
    closeOrder(orders, -1, &currentOrder, history, orderPreparationQueue);

    // Se o usuário optou por NÃO fechar (continua EM_CONSTRUCAO), salva no vetor central
    if (currentOrder.getStatusOrder() == StatusOrder::EM_CONSTRUCAO)
    {
        orders.push_back(currentOrder);
    }

    cout << "\n========================================" << endl;
    cout << " Pedido N. " << currentOrder.getNumberOrder() << " finalizado com sucesso!" << endl;
    cout << " Total: R$ " << currentOrder.getTotalPriceToOrder() << endl;
    cout << " Status: " << currentOrder.statusToString(currentOrder.getStatusOrder()) << endl;
    cout << "========================================\n"
         << endl;
}

// função cancelar Pedido
// Função para cancelar apenas Pedidos em Construção
void menuCancelOrder(vector<Order> &orders)
{
    char continueClear;

    cout << "Menu - Cancelar Pedido Em Construcao" << endl;
    cout << "**********************************************************" << endl;

    if (orders.empty()) {
        messagesErrorsWarning("Nenhum pedido em aberto no momento.");
        return;
    }

    // Busca o índice do pedido no vetor central
    int orderIndex = searchOrderIndex(orders);

    if (orderIndex >= 0)
    {
        // Valida se o pedido realmente está em construção
        if (orders[orderIndex].getStatusOrder() != StatusOrder::EM_CONSTRUCAO)
        {
            messagesErrorsWarning("Apenas pedidos EM CONSTRUCAO podem ser cancelados por este menu!");
            return;
        }

        cout << "\nTem certeza que deseja cancelar o Pedido N. "
             << orders[orderIndex].getNumberOrder() << " (Em Construcao)? (s/n): ";

        char confirm;
        cin >> confirm;

        if (confirm == 's' || confirm == 'S')
        {
            // Remove permanentemente o pedido do vetor de montagem
            orders.erase(orders.begin() + orderIndex);
            messagesSucess("Pedido em construcao cancelado e removido com sucesso!");
        }
        else
        {
            messagesSucess("\nOperacao cancelada.");
        }
    }

    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

// Listar todos os produtos cadastrados no sistema
void showOrders(vector<Order> &order)
{
    if (order.size() > 0)
    {
        cout << "\nnúmero do pedido | descrição | Valor" << endl;
        cout << "-------------------" << endl;
        for (size_t i = 0; i < order.size(); i++)
        { // size_t é um inteiro positivo (unsigned) usado pelo C++ para tamanhos e índices de vetores
            order[i].showResumeOrder();
            cout << "\n"; // Em C++ usa-se order[i] em vez de order.get(i)
        }
    }
    else
    {
        messagesSucess("Nenhum produto cadastrado.");
    }
}

// Adicionar itens ao pedido
void menuAddOrderItem(vector<Order> &orders, vector<Product> &menu)
{
    // Declaração das variáveis auxiliares utilizadas no loop
    int barCode = 0;
    int quantity = 0;
    char confirm = 'n';

    // Usa a busca pelo número do pedido em vez do índice fixo
    int orderIndex = searchOrderIndex(orders);

    if (orderIndex < 0) {
        return; // Pedido não encontrado (a searchOrderIndex já exibe a mensagem de erro)
    }
    
    Order *order = &orders[orderIndex];
    messagesSucess("pedido: " + to_string(order->getNumberOrder()) + " selecionado!");

    if (order->getStatusOrder() == StatusOrder::EM_CONSTRUCAO)
    {
        cout << "Adicionar Itens" << endl;
        cout << "**********************************************************" << endl;
        do
        {
            cout << "Informe o CODIGO do produto: ";
            cin >> barCode;

            if (!productExists(menu, barCode))
            {
                messagesErrorsWarning("Nenhum produto cadastrado com esse codigo");
                cout << "\nDeseja tentar outro codigo? (s/n): ";
                cin >> confirm;
                continue;
            }

            int index = getProductIndex(menu, barCode);

            cout << "\nProduto selecionado: " << endl;
            cout << "\nCodigo | Nome | Valor" << endl;
            cout << "-------------------------------------------" << endl;

            menu[index].show();
            cout << "-------------------------------------------" << endl;
            cout << "\nDigite a novo valor para a quantidade do item: ";
            cin >> quantity;

            if (quantity > 0)
            {
                Item newItem;
                newItem.setProductItem(menu[index]);
                newItem.setQuantityItem(quantity);
                cout << "\n-------------------------------------------" << endl;
                cout << "-> Subtotal do Item: R$ " << newItem.getPriceTotalItem() << endl;

                order->addItemToOrder(newItem);
            }
            else
            {
                messagesErrorsWarning("[ERRO] A quantidade deve ser maior que zero!");
                return;
            }
            cout << "-------------------------------------------" << endl;
            cout << "\nDeseja adicionar mais um produto ao pedido?(s/n): ";
            cin >> confirm;
        } while (confirm == 's' || confirm == 'S');
    }
    else
    {
        messagesErrorsWarning("Pedido em estado " + order->statusToString(order->getStatusOrder()) + " não permite adicionar itens!");
    }

    order->sumTotalPriceToOrder();

    cout << "\n========================================" << endl;
    cout << " Pedido N. " << order->getNumberOrder() << " editado com sucesso!" << endl;
    cout << " Total: R$ " << order->getTotalPriceToOrder() << endl;
    cout << "========================================\n"
         << endl;
}

// Remover item de pedido
void menuRemoveOrderItem(vector<Order> &orders, vector<Product> &menu)
{
    char confirm = 'n';
    char confirmRm = 'n';

    // Busca pelo número do pedido em vez de usar o índice posicional direto
    int orderIndex = searchOrderIndex(orders);

    if (orderIndex < 0) {
        return; // Pedido não encontrado (a searchOrderIndex já exibe a mensagem)
    }

    Order *order = &orders[orderIndex];
    messagesSucess("pedido: " + to_string(order->getNumberOrder()) + " selecionado!");

    if (order->getStatusOrder() == StatusOrder::EM_CONSTRUCAO)
    {
        cout << "Remover Itens" << endl;
        cout << "**********************************************************" << endl;
        do
        {
            // Busca o índice do produto no cardápio geral
            int productIndex = searchProductBarCode(menu);

            if (productIndex >= 0)
            {
                // Obtém o código de barras (int) do produto selecionado do menu
                int barCode = menu[productIndex].getBarCode();

                // Verifica se o produto existe DENTRO do pedido e obtém a sua posição interna
                int orderItemIndex = order->findItemIndexByBarCode(barCode);

                if (orderItemIndex >= 0)
                {
                    cout << "\nTem certeza que deseja apagar o produto: "
                         << menu[productIndex].getName() << "? (s/n): ";
                    cin >> confirmRm;

                    if (confirmRm == 's' || confirmRm == 'S')
                    {
                        // Remove o produto utilizando o índice relativo ao vetor de itens do pedido
                        order->removeItemFromOrder(orderItemIndex);
                        messagesSucess("Produto removido com sucesso!");
                    }
                }
                else
                {
                    messagesErrorsWarning("Este produto não consta no pedido selecionado!");
                }
            }
            else
            {
                messagesErrorsWarning("Operacao cancelada.");
            }

            cout << "-------------------------------------------" << endl;
            cout << "\nDeseja remover mais um produto do pedido?(s/n): ";
            cin >> confirm;
        } while (confirm == 's' || confirm == 'S');
    }
    else
    {
        messagesErrorsWarning("Pedido em estado " + order->statusToString(order->getStatusOrder()) + " não permite remover itens!");
    }

    order->sumTotalPriceToOrder();
    cout << "\n========================================" << endl;
    cout << " Pedido N. " << order->getNumberOrder() << " editado com sucesso!" << endl;
    cout << " Total: R$ " << order->getTotalPriceToOrder() << endl;
    cout << "========================================\n"
         << endl;

    char continueClear;
    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;
    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

//fechar pedido
void closeOrder(vector<Order> &orders, int indexOrder, Order *order, OrderHistoryList *orderHistoryList, OrderPreparationQueue &orderPreparationQueue)
{
    if (order == nullptr) return;

    char optionCloseOrder;
    cout << "Confirmar o fechamento do pedido N. " << order->getNumberOrder() << "? (s/n): ";
    cin >> optionCloseOrder;

    if (optionCloseOrder == 's' || optionCloseOrder == 'S')
    {
        if (order->getStatusOrder() != StatusOrder::CANCELADO && order->getStatusOrder() != StatusOrder::PRONTO)
        {
            // Altera o status
            order->setStatusOrder(StatusOrder::FECHADO);

            // Copia para o Histórico
            orderHistoryList->insertEnd(*order);

            // Enfileira na Cozinha
            if (orderHistoryList->getTail() != nullptr) {
                orderPreparationQueue.enqueue(orderHistoryList->getTail()->getOrderPointer());
            }

            // Remove do vetor 'orders' se ele já estiver lá dentro
            if (indexOrder >= 0 && indexOrder < static_cast<int>(orders.size()))
            {
                orders.erase(orders.begin() + indexOrder);
            }

            messagesSucess("Pedido fechado com sucesso!");
        }
    } else {
        messagesErrorsWarning("Operacao cancelada.");
    }
}

// Busca um pedido pelo número e retorna o índice no vetor de pedidos
int searchOrderIndex(vector<Order> &orders)
{
    int orderNumber;
    int foundIndex = -1;

    menuDividers();
    cout << "Informe o NUMERO do pedido: ";
    cin >> orderNumber;

    for (size_t i = 0; i < orders.size(); i++)
    {
        if (orders[i].getNumberOrder() == orderNumber)
        {
            foundIndex = static_cast<int>(i); // Salva o índice do pedido
            break;                            // Encontrou, para o loop
        }
    }

    if (foundIndex == -1)
    {
        messagesErrorsWarning("Pedido com o numero " + to_string(orderNumber) + " nao encontrado!");
    }

    return foundIndex; // Retorna o índice do pedido encontrado ou -1
}

// =======================================================
// MENU PRODUTOS
// =======================================================
// Menu de gerenciamento dos produtos
void menuProducts(vector<Product> &menu)
{
    int responseMenu = 0;

    menuDividers();

    cout << "Informe uma opcao" << endl;
    cout << "**********************************************************" << endl;
    cout << "1 - Cadastrar um produto" << endl;
    cout << "2 - Editar um produto" << endl;
    cout << "3 - Remover um produto" << endl;
    cout << "4 - Consultar um produto pelo nome" << endl;
    cout << "5 - Consultar lista de produtos cadastrados" << endl;
    cout << "6 - Voltar ao order principal" << endl;
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
        cout << "Menu - Produtos cadastrados" << endl;
        cout << "**********************************************************" << endl;
        showProducts(menu);
        cout << "\n";
        break;
    default:
        break;
    }
}

// Adicionar um produto ao menu
void menuAddProduct(vector<Product> &menu)
{
    char continueClear;
    char confirmMore;

    do
    {
        string name;
        int barCode;
        double price;
        Product product;

        menuDividers();

        cout << "Cadastrar produto " << endl;
        cout << "**********************************************************" << endl;

        // Loop para garantir a inserção de um código válido e único
        do
        {
            cout << "Informe o CODIGO do produto: ";
            cin >> barCode;

            if (barCode < 0)
            {
                messagesErrorsWarning("[Erro] O codigo de barras deve ser positivo! Tente novamente.");
            }
            else if (productExists(menu, barCode))
            {

                messagesErrorsWarning("[Erro] Ja existe um produto cadastrado com o codigo " + to_string(barCode) + "! Tente novamente.");
            }
        } while (barCode < 0 || productExists(menu, barCode));

        // Limpa o \n deixado pelo cin >> barCode antes de entrar no getline
        cin.ignore();

        // Loop para garantir a inserção de um nome válido e único
        do
        {
            cout << "Informe o NOME do produto: ";
            getline(cin, name);

            if (name.empty() || name.find_first_not_of(" \t\n\r") == string::npos)
            {
                messagesErrorsWarning("[Erro] O nome do produto deve ser diferente de vazio! Tente novamente.");
            }
            else if (productExistsName(menu, name))
            {

                messagesErrorsWarning("[Erro] Ja existe um produto cadastrado com o nome " + name + "! Tente novamente.");
            }
        } while (name.empty() || name.find_first_not_of(" \t\n\r") == string::npos || productExistsName(menu, name));

        // Loop para garantir a inserção de um preço válido (positivo)
        do
        {
            cout << "Informe o VALOR UNITARIO do produto: ";
            cin >> price;

            if (price < 0)
            {
                messagesErrorsWarning("[Erro] O valor unitario deve ser positivo! Tente novamente.");
            }
        } while (price < 0);

        // Salva os dados no objeto
        product.setName(name);
        product.setBarCode(barCode);
        product.setUnitPrice(price);

        // Adiciona o produto ao vetor do menu
        menu.push_back(product);

        messagesSucess("Produto cadastrado com sucesso!");

        // Pergunta se deseja cadastrar outro produto
        cout << "\nDeseja cadastrar outro produto? (s/n): ";
        cin >> confirmMore;

    } while (confirmMore == 's' || confirmMore == 'S');

    cout << "\npressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

// Editar um produto do order
void menuEditProduct(vector<Product> &menu)
{
    char continueClear;
    string newName;
    double newPrice;

    // Chama a busca que pede o código e retorna o índice (posição no vetor)
    int productIndex = searchProductBarCode(menu);

    // Valida se o produto foi encontrado (>= 0 inclui o índice 0)
    if (productIndex >= 0)
    {
        cout << "\n---------------------------------------------------------\n";
        cout << "Produto " << menu[productIndex].getBarCode() << " selecionado!\n";
        cout << "\nCodigo | Nome | Valor" << endl;
        cout << "-------------------" << endl;
        menu[productIndex].show();
        cout << "\n---------------------------------------------------------\n";

        cin.ignore(); // Limpa o buffer do cin para ler o getline sem pular

        cout << "\nInforme o novo NOME do produto OU tecle [ENTER] para manter o mesmo nome: ";
        getline(cin, newName);
        cout << "Informe o novo VALOR UNITARIO do produto ou digite [0] zero para manter o mesmo valor: ";
        cin >> newPrice;

        // Atualiza o preço apenas se for digitado um valor maior que zero
        if (!newName.empty())
        {
            menu[productIndex].setName(newName);
        }
        if (newPrice > 0)
        {
            menu[productIndex].setUnitPrice(newPrice);
        }

        messagesSucess("Produto atualizado com sucesso!");

        cout << "\nCodigo | Nome | Valor" << endl;
        cout << "-------------------" << endl;
        menu[productIndex].show();
        cout << "\n\n";
    }
    else
    {
        messagesErrorsWarning("Produto nao encontrado!");
    }

    cout << "pressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

// Deletar um produto do menu
void menuDeleteProduct(vector<Product> &menu)
{
    char continueClear;

    // Chama a busca por código, que já pede o código do produto e retorna a posição
    int productIndex = searchProductBarCode(menu);

    // Se o índice for 0 ou maior, o produto existe na lista
    if (productIndex >= 0)
    {
        cout << "\nTem certeza que deseja apagar o produto: "
             << menu[productIndex].getName() << "? (s/n): ";

        char confirm;
        cin >> confirm;

        if (confirm == 's' || confirm == 'S')
        {
            // Apaga o produto do vetor usando o iterador
            menu.erase(menu.begin() + productIndex);
            messagesSucess("Produto removido com sucesso!");
            showProducts(menu);
        }
        else
        {
            messagesErrorsWarning("Operacao cancelada.");
        }
    }

    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

// Listar todos os produtos que contenham parte de uma palavra
void searchProductName(vector<Product> &menu)
{
    char continueClear;
    string partName;

    cin.ignore();

    menuDividers();

    cout << "Consultar produto " << endl;
    cout << "********************************** " << endl;
    cout << "Informe o NOME do produto: ";
    getline(cin, partName);

    bool found = false;
    cout << "\nCodigo | Nome | Valor" << endl;
    cout << "-------------------" << endl;
    for (size_t i = 0; i < menu.size(); i++)
    {
        // Verifica se o texto digitado em 'partName' está contido na descrição
        if (menu[i].getName().find(partName) != string::npos)
        {
            menu[i].show();
            cout << "\n";
            found = true;
        }
    }

    if (!found)
    {
        messagesErrorsWarning("Nenhum produto encontrado com o termo: " + partName);
    }

    cout << "\npressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

// Listar todos os produtos que contenham esse código de barras
int searchProductBarCode(vector<Product> &menu)
{
    int barCode;
    int foundIndex = -1; // Inicializa o índice como -1, indicando que não foi encontrado

    menuDividers();
    cout << "Informe o CODIGO do produto: ";
    cin >> barCode;

    for (size_t i = 0; i < menu.size(); i++)
    {
        if (menu[i].getBarCode() == barCode)
        {
            foundIndex = i; // Salva o índice onde o produto está
            break;          // Encontrou, para o loop
        }
    }

    if (foundIndex == -1)
    {

        messagesErrorsWarning("Produto com o codigo " + to_string(barCode) + " nao encontrado!");
    }

    return foundIndex; // Retorna o índice do produto encontrado ou -1 se não encontrado
}

// Listar todos os produtos cadastrados no sistema
void showProducts(vector<Product> &menu)
{
    if (menu.size() > 0)
    {
        cout << "\nCodigo | Nome | Valor" << endl;
        cout << "-------------------" << endl;
        for (size_t i = 0; i < menu.size(); i++)
        { // size_t é um inteiro positivo (unsigned) usado pelo C++ para tamanhos e índices de vetores
            menu[i].show();
        }
    }
    else
    {
        messagesErrorsWarning("Nenhum produto cadastrado.");
    }
}

// Retorna a posição do produto no vetor
int getProductIndex(const vector<Product> &menu, int barCode)
{
    for (size_t i = 0; i < menu.size(); i++)
    {
        if (menu[i].getBarCode() == barCode)
        {
            return i; // Retorna a posição (0, 1, 2...) onde o produto está no vetor
        }
    }
    return -1; // Retorna -1 se não encontrar
}

// Verifica se o produto existe no order pelo código de barras, mas sem retornar texto
bool productExists(const vector<Product> &menu, int barCode)
{

    int posicaoEncontrada = getProductIndex(menu, barCode); // Procura em que posição o produto está no vetor

    // Testa se a posição é válida
    if (posicaoEncontrada != -1)
    {
        return true; // Se a posição for diferente de -1, o produto existe na lista!
    }
    else
    {
        return false; // Se for igual a -1, o produto não existe na lista!
    }
}

// Nova versão do productExists, mas para NOME (mesmo nome de função, parâmetros diferentes)
bool productExistsName(vector<Product> &menu, const string &name)
{
    for (size_t i = 0; i < menu.size(); i++)
    {
        if (menu[i].getName() == name)
        { // Compara se os nomes são idênticos
            return true;
        }
    }
    return false;
}

// =======================================================
// HISTORICO
// =======================================================
void menuManagerHistory(OrderHistoryList *orderHistoryList)
{
    int responseMenu = 0;

    menuDividers();

    cout << "MENU - HISTORICO DE PEDIDOS" << endl;
    cout << "**********************************************************" << endl;
    cout << "1 - Exibir historico de pedidos completo" << endl;
    cout << "2 - Exibir historico de pedidos resumido" << endl;
    cout << "3 - Buscar um pedido pelo nome do cliente" << endl;
    cout << "4 - Buscar um pedido pelo numero" << endl;
    cout << "5 - Cancelar um pedido do historico" << endl;
    cout << "6 - Remover um pedido do historico" << endl;
    cout << "10 - Voltar ao order principal" << endl;
    cout << "\nDigite a opção desejada: ";
    cin >> responseMenu;

    menuDividers();
    switch (responseMenu)
    {
    case 1:
    {
        deleteTerminal();
        cout << "HISTORICO COMPLETO DOS PEDIDOS" << endl;
        cout << "**********************************************************" << endl;
        char tecla;
        orderHistoryList->showReportAll();
        cout << "aperte qualquer tecla para sair" << endl;
        cin >> tecla;
    }

    break;
    case 2:
        resumeHistory(orderHistoryList);
        break;
    case 3:
        searchOrderByName(orderHistoryList);
        break;
    case 4:
        searchOrderByNumber(orderHistoryList);
        break;
    case 5:
        
        break;
    case 6:

        break;
    default:
        break;
    }
}

void resumeHistory(OrderHistoryList *orderHistoryList)
{
    int responseMenu = 0;
    int count = 1;
    int size = orderHistoryList->getSize();
    bool continuar = true;

    if (size > 0)
    {
        OrderHistory *aux = orderHistoryList->gethead();

        do
        {

            cout << "\n\nTotal de Pedidos " << count << "/" << size << endl;

            menuDividers();

            cout << "MENU - RESUMO HISTORICO DE PEDIDOS" << endl;
            cout << "**********************************************************" << endl;

            aux->getOrder().showResumeOrder();

            cout << ((aux->getNext() != nullptr) ? "1 - Proximo  | " : "") << ((aux->getPrevious() != nullptr) ? "2 - Anterior | " : "") << "0 - Voltar menu principal" << endl;
            cout << "\nDigite a opção desejada: ";
            cin >> responseMenu;

            deleteTerminal();

            menuDividers();

            switch (responseMenu)
            {
            case 1:

                if (aux->getNext() != nullptr)
                {
                    aux = aux->getNext();
                    count++;
                }

                break;
            case 2:

                if (aux->getPrevious() != nullptr)
                {
                    aux = aux->getPrevious();
                    count--;
                }

                break;
            default:
                continuar = false;
                break;
            }
        } while (continuar);
    }
    else
    {
        messagesErrorsWarning("Nenhum pedido no historico!");
    }
}

void searchOrderByName(OrderHistoryList *orderHistoryList)
{
    char continueClear;

    cout << "Menu - Buscar Pedido por Nome do Cliente" << endl;
    cout << "**********************************************************" << endl;

    if (orderHistoryList == nullptr || orderHistoryList->isEmpty())
    {
        messagesErrorsWarning("O historico de pedidos esta vazio.");
        return;
    }

    string clientName;
    cout << "Informe o nome do cliente: ";
    cin.ignore();
    getline(cin, clientName);

    OrderHistory *aux = orderHistoryList->gethead();
    bool found = false;

    cout << "\n--- RESULTADO DA BUSCA ---" << endl;

    while (aux != nullptr)
    {
        // Usando getNameClient() em vez de getClientName()
        if (aux->getOrder().getNameClient() == clientName)
        {
            found = true;
            aux->getOrder().showResumeOrder();
            cout << "----------------------------------------------------------" << endl;
        }
        aux = aux->getNext();
    }

    if (!found)
    {
        messagesErrorsWarning("Nenhum pedido encontrado para o cliente: " + clientName);
    }

    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

void searchOrderByNumber(OrderHistoryList *orderHistoryList)
{
    char continueClear;

    cout << "Menu - Buscar Pedido por Numero" << endl;
    cout << "**********************************************************" << endl;

    if (orderHistoryList == nullptr || orderHistoryList->isEmpty())
    {
        messagesErrorsWarning("O historico de pedidos esta vazio.");
        return;
    }

    int orderNumber;
    cout << "Informe o NUMERO do pedido: ";
    cin >> orderNumber;

    OrderHistory *aux = orderHistoryList->gethead();
    bool found = false;

    while (aux != nullptr)
    {
        if (aux->getOrder().getNumberOrder() == orderNumber)
        {
            found = true;
            cout << "\n--- PEDIDO ENCONTRADO ---" << endl;
            aux->getOrder().showResumeOrder();
            cout << "----------------------------------------------------------" << endl;
            break; // Como o número é único, pode encerrar o loop
        }
        aux = aux->getNext();
    }

    if (!found)
    {
        messagesErrorsWarning("Pedido N. " + to_string(orderNumber) + " nao foi encontrado no historico.");
    }

    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

// =======================================================
// COZINHA
// =======================================================
void menuKitchen(OrderPreparationQueue *orderPreparationQueue, vector<Order *> &kitchen, OrderPickupStack &orderPickupStack)
{
    int responseMenu = 0;

    menuDividers();

    cout << "MENU - COZINHA" << endl;
    cout << "**********************************************************" << endl;
    cout << "1 - Exibir fila de preparo" << endl;
    cout << "2 - Iniciar preparo" << endl;
    cout << "3 - Finalizar Preparo" << endl;
    cout << "4 - Pedidos na cozinha " << endl;
    cout << "\nDigite a opção desejada: ";
    cin >> responseMenu;

    switch (responseMenu)
    {
    case 1:
        orderPreparationQueue->showQueuePreparation();
        break;
    case 2:
        if (!orderPreparationQueue->isEmpty())
        {
            Order *orderPreparo = orderPreparationQueue->getOrderPreparation();
            orderPreparo->setStatusOrder(StatusOrder::COZINHA);
            kitchen.push_back(orderPreparo);
            orderPreparationQueue->dequeue();

            messagesSucess("Iniciando o preparo do Pedido N. " + to_string(kitchen.back()->getNumberOrder()));
        }
        else
        {
            messagesErrorsWarning("Nenhum pedido na Fila de preparo");
        }
        break;
    case 3:
    {
        int pedidoIndex;
        cout << "\nDigite o numero do pedido que deseja finalizar: ";
        cin >> pedidoIndex;

        if (pedidoIndex > 0)
        {
            if (kitchen.size() > 0)
            {
                for (size_t i = 0; i < kitchen.size(); i++)
                {
                    if (kitchen[i]->getNumberOrder() == pedidoIndex)
                    {

                        char optionCloseOrder;

                        cout << "Confirmar o fechamento do pedido [ " << kitchen[i]->getNumberOrder() << " ] ? (s/n): ";
                        cin >> optionCloseOrder;

                        bool isClosedNow = (optionCloseOrder == 's' || optionCloseOrder == 'S');
                        if (isClosedNow)
                        {

                            messagesSucess("Pedido " + to_string(kitchen[i]->getNumberOrder()) + " esta PRONTO e disponivel para a retirada!!");
                            kitchen[i]->setStatusOrder(StatusOrder::PRONTO);
                            kitchen.erase(kitchen.begin() + i);
                            orderPickupStack.push(kitchen[i]);
                        }
                        else
                        {
                            messagesErrorsWarning("Pedido " + to_string(kitchen[i]->getNumberOrder()) + " nao finalizado!");
                        }

                        return;
                    }
                }

                messagesErrorsWarning("O pedido [ " + to_string(pedidoIndex) + " ] é inexistente. Tente novamente!");
            }
            else
            {
                messagesErrorsWarning("Nenhum pedido na cozinha!");
            }
        }
        else
        {
            messagesErrorsWarning("Digite um valor positivo!");
        }
    }

    break;
    case 4:

        if (kitchen.size() > 0)
        {
            cout << "\n\nRELATORIO DE PEDIDOS NA COZINHA " << endl;
            cout << "**********************************************************" << endl;

            for (size_t i = 0; i < kitchen.size(); i++)
            {
                kitchen[i]->showResumeOrder();
            }
        }
        else
        {
            messagesErrorsWarning("Nenhum pedido na cozinha!");
        }

        break;
    default:
        break;
    }
}

void menuPickupStack(OrderPickupStack &orderPickupStack)
{
    int responseMenu = 0;

    menuDividers();

    cout << "MENU - PEDIDOS PRONTOS" << endl;
    cout << "**********************************************************" << endl;
    cout << "1 - Exibir pedidos prontos" << endl;
    cout << "2 - Entregar pedido (topo)" << endl;
    cout << "\nDigite a opção desejada: ";
    cin >> responseMenu;

    switch (responseMenu)
    {
    case 1:
        orderPickupStack.printReadyOrders();
        break;
    case 2:
        orderPickupStack.pop();
        break;
    default:
        messagesErrorsWarning("Opção invalida, tente novamente!");
        break;
    }
}

// =======================================================
// CONFIGURÇÕES
// =======================================================
void menuDividers()
{
    cout << "------------------------------------------------------------------" << endl;
    cout << endl;
}

void deleteTerminal()
{
    system("clear");
}

void messagesSucess(string messsage)
{
    cout << "\n---------------------------------------------------------\n";
    cout << messsage << "\n";
    cout << "---------------------------------------------------------\n\n";
}

void messagesErrorsWarning(string messsage)
{
    cout << "\n<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n";
    cout << messsage << "\n";
    cout << "<>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<><>-_-<>\n\n";
}

// =======================================================
// CADASTROS PRÉVIOS
// =======================================================
void previousRegistrations(vector<Order> &orders, vector<Product> &menu, OrderHistoryList &orderHistory, OrderPreparationQueue &orderPreparationQueue)
{

    Product product;
    Item item;

    product.setBarCode(1);
    product.setName("coca cola 1 litro");
    product.setUnitPrice(7);

    menu.push_back(product);

    product.setBarCode(2);
    product.setName("coca cola 2 litro");
    product.setUnitPrice(14);

    menu.push_back(product);

    product.setBarCode(3);
    product.setName("bauru artesanal");
    product.setUnitPrice(14);

    menu.push_back(product);

    product.setBarCode(4);
    product.setName("hamburguer artesanal");
    product.setUnitPrice(22);
    menu.push_back(product);

    product.setBarCode(5);
    product.setName("cheeseburguer");
    product.setUnitPrice(18);
    menu.push_back(product);

    product.setBarCode(6);
    product.setName("pizza calabresa");
    product.setUnitPrice(35);
    menu.push_back(product);

    product.setBarCode(7);
    product.setName("pizza mussarela");
    product.setUnitPrice(32);
    menu.push_back(product);

    product.setBarCode(8);
    product.setName("refrigerante lata");
    product.setUnitPrice(6);
    menu.push_back(product);

    product.setBarCode(9);
    product.setName("suco de laranja");
    product.setUnitPrice(8);
    menu.push_back(product);

    product.setBarCode(10);
    product.setName("suco de maracuja");
    product.setUnitPrice(7);
    menu.push_back(product);

    product.setBarCode(11);
    product.setName("agua mineral");
    product.setUnitPrice(3);
    menu.push_back(product);

    /*// pre-cadastro de pedidos
    Order order_temp;

    order_temp.setNameClient("jackson");
    order_temp.setNumberOrder(1);
    order_temp.setNumberTable(1);
    item.setProductItem(menu[0]);
    item.setQuantityItem(3);
    order_temp.addItemToOrder(item);
    order_temp.sumTotalPriceToOrder();
    order_temp.setStatusOrder(StatusOrder::EM_CONSTRUCAO);
    orders.push_back(order_temp);

    order_temp.setNameClient("Thiago");
    order_temp.setNumberOrder(2);
    order_temp.setNumberTable(2);
    item.setProductItem(menu[9]);
    item.setQuantityItem(10);
    order_temp.addItemToOrder(item);
    item.setProductItem(menu[8]);
    item.setQuantityItem(6);
    order_temp.addItemToOrder(item);
    order_temp.sumTotalPriceToOrder();
    order_temp.setStatusOrder(StatusOrder::FECHADO);

    orderHistory.insertEnd(order_temp);

    orderPreparationQueue.enqueue(orderHistory.getTail()->getOrderPointer());*/
}
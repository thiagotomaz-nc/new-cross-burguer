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

// orders
void showOrders(vector<Order> &order);
int searchOrderNumber(vector<Order> &order);
void menuSelectItemOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *orderHistoryList, OrderPreparationQueue &orderPreparationQueue, int *orderNumber);
void menuAddOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *orderHistoryList, OrderPreparationQueue &orderPreparationQueue, int *orderNumber, StatusProductCategories selectCategories);
void menuCancelOrder(vector<Order> &orders);
void menuEditOrder(vector<Order> &orders, vector<Product> &menu);
void menuAddOrderItem(vector<Order> &orders, vector<Product> &menu);
void menuRemoveOrderItem(vector<Order> &orders, vector<Product> &menu);
void closeOrder(vector<Order> &orders, int indexOrder, Order *order, OrderHistoryList *OrderHistoryList, OrderPreparationQueue &orderPreparationQueue);

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
    int response = 0, numberOrder = 2;
    bool repeat = true;
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
        cout << "2 - Cancelar pedido" << endl;
        cout << "3 - Produtos da Hamburgueria" << endl;
        cout << "4 - Historico" << endl;
        cout << "5 - Cozinha" << endl;
        cout << "6 - Fila de retirada" << endl;
        cout << "10 - Sair do sistema" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "\nDigite a opcao desejada: ";
        cin >> response;

        deleteTerminal();

        switch (response)
        {
        case 1:
            menuManageOrder(orders, menu_products, &orderHistoryList, orderPreparationQueue, &numberOrder);
            break;
        case 2:
            menuCancelOrder(orders);
            break;
        case 3:
            menuProducts(menu_products);
            break;
        case 4:
            menuManagerHistory(&orderHistoryList);
            break;
        case 5:
            menuKitchen(&orderPreparationQueue, kitchen, orderPickupStack);
            break;
        case 6:
            menuPickupStack(orderPickupStack);
            break;
        case 10:
            /* code */
            cout << endl;
            cout << "Saindo do sistema!!!\nAte mais!!" << endl;
            cout << endl;
            repeat = false;
            break;

        default:
            messagesErrorsWarning("Opcao invalida! Tente novamente.");
            continue;
        }
    } while (repeat);

    return 0;
}

// =======================================================
// MENU gerenciar PEDIDOS - Editar pedido
// =======================================================
// Menu de gerenciamento dos pedidos
void menuManageOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *orderHistoryList, OrderPreparationQueue &orderPreparationQueue, int *orderNumber)
{

    int responseMenuOrder = 0;
    bool repeat = true;

    menuDividers();
    do
    {
        cout << "Menu - Gerenciar Pedidos" << endl;
        cout << "**********************************************************" << endl;
        cout << "1 - Adicionar um pedido" << endl;
        cout << "2 - Cancelar um pedido" << endl;
        cout << "3 - Editar pedido" << endl;
        cout << "4 - Fechar um pedido " << endl;
        cout << "5 - Consultar lista de produtos cadastrados" << endl;
        cout << "6 - Exibir pedidos em construcao" << endl;
        cout << "7 - Exibir todos os pedidos" << endl;
        cout << "8 - Voltar  menu anterior" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "\nDigite a opcao desejada: ";
        cin >> responseMenuOrder;
        cout << "---------------------------------------------------------" << endl;

        deleteTerminal();

        switch (responseMenuOrder)
        {
        case 1:
            menuSelectItemOrder(orders, menu, orderHistoryList, orderPreparationQueue, orderNumber);
            break;
        case 2:
            menuCancelOrder(orders);
            break;
        case 3:
            menuEditOrder(orders, menu);
            break;
        case 4:
        {
            int orderIndex;

            cout << "\n Informe o numero do pedido que deseja fechar : " << endl;
            cin >> orderIndex;
            Order *order;

            try
            {
                // .at() lança std::out_of_range se o índice for inválido
                order = &orders.at(orderIndex - 1);
                cout << "\n pedido: " << order->getNumberOrder() << " selecionado!" << endl;

                if (order->getStatusOrder() == StatusOrder::FECHADO)
                {
                    messagesErrorsWarning("Atencao o pedido" + to_string(order->getNumberOrder()) + " ja esta fechado!");
                    return;
                }

                closeOrder(orders, orderIndex, order, orderHistoryList, orderPreparationQueue);
            }
            catch (const std::out_of_range &e)
            {
                // Captura o erro out_of_range especificamente
                messagesErrorsWarning("[ERRO] Posição fora do limite do vetor!");
                return;
            }

            // salvar na lista de pedidos
        }
        break;
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
        case 7:
            menuDividers();
            cout << "RELATORIO GERAL DOS PEDIDOS " << endl;
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
            cout << "\n";

            if (!orderHistoryList->isEmpty())
            {
                orderHistoryList->showReportAll();
            }

            break;
        case 8:
            repeat = false;
            break;
        default:
            messagesErrorsWarning("Opção invalida, tente novamente!");
            break;
        }
    } while (repeat);
}

void menuEditOrder(vector<Order> &orders, vector<Product> &menu)
{

    int responseMenuEditOrder = 0;

    cout << "\nMenu - Editar pedido" << endl;
    cout << "**********************************************************" << endl;
    cout << "1 - Adicionar um item" << endl;
    cout << "2 - Remover um item" << endl;
    cout << "3 - Desfazer a ultima ação do um item" << endl;
    cout << "4 - Editar o nome do cliente: " << endl;
    cout << "5 - Editar o numero da mesa: " << endl;
    cout << "6 - Sair" << endl;
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
    /*case 3:
        // pilha de ações
        break;*/
    case 4:
    {
        int orderIndex;
        string newName = "";

        cout << "\n Informe o numero do pedido que deseja editar o cliente : " << endl;
        cin >> orderIndex;
        Order *order;

        try
        {
            // .at() lança std::out_of_range se o índice for inválido
            order = &orders.at(orderIndex - 1);
            cout << "\n pedido: " << order->getNumberOrder() << " selecionado!" << endl;
        }
        catch (const std::out_of_range &e)
        {
            // Captura o erro out_of_range especificamente
            messagesErrorsWarning("[ERRO] Posição fora do limite do vetor!");
            return;
        }
        cin.ignore();
        cout << "\n informe o novo nome do cliente ou tecle [ENTER] para manter o mesmo nome: ";
        getline(cin, newName);
        if (!newName.empty() || newName.find_first_not_of(" \t\n\r") != string::npos)
        {
            order->setNameClient(newName);
            messagesSucess("Nome do cliente atualizado com sucesso!");
        }
        else
        {
            messagesErrorsWarning("[Erro] O nome do cliente deve ser diferente de vazio! Tente novamente.");
            return;
        }
        // salvar na lista de pedidos
    }
    break;
    case 5:
    {
        int orderIndex;
        int numBerTable = 0;

        cout << "\n Informe o numero do pedido que deseja editar a mesa : " << endl;
        cin >> orderIndex;
        Order *order;

        try
        {
            // .at() lança std::out_of_range se o índice for inválido
            order = &orders.at(orderIndex - 1);
            messagesSucess("pedido: " + to_string(order->getNumberOrder()) + " selecionado!");
        }
        catch (const std::out_of_range &e)
        {
            // Captura o erro out_of_range especificamente
            messagesErrorsWarning("[ERRO] Posição fora do limite do vetor!");
            return;
        }
        cin.ignore();
        cout << "\n informe o novo numero da mesa do pedido ou tecle [ENTER] para manter o mesmo numero: ";
        cin >> numBerTable;
        if (numBerTable > 0)
        {
            order->setNumberTable(numBerTable);
            messagesSucess("Nome do cliente atualizado com sucesso!");
        }
        else
        {
            messagesErrorsWarning("[Erro] O nome do cliente deve ser diferente de vazio! Tente novamente.");
            return;
        }
        // salvar na lista de pedidos
    }

    break;
    default:
        break;
    }
}

void menuAddOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *history, OrderPreparationQueue &orderPreparationQueue, int *orderNumber, StatusProductCategories selectCategories)
{

    bool repeat = true;

    int selectProduct;

    Order currentOrder;

    // Loop para adicionar todos os itens do pedido
    do
    {
        menuDividers();
        cout << "Menu - Adicionar produto ao pedido(s)" << endl;
        cout << "**********************************************************" << endl;
        cout << "informe o numero do item para adicionar ao pedido ou [0] para menu anterior: ";

        cin >> selectProduct;

        if (selectProduct != 0 && selectProduct > 0)
        {
            repeat = false;
            deleteTerminal();
        }
        else
        {
            messagesErrorsWarning("opção invalida, tente novamente!");
        }

    } while (repeat);
}

// Menu de seleção dos itens do pedido por categoria
void menuSelectItemOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *history, OrderPreparationQueue &orderPreparationQueue, int *orderNumber)
{
    bool repeat = true;

    int categoriesSelect;

    Order currentOrder;

    // Loop para adicionar todos os itens do pedido
    do
    {
        menuDividers();
        cout << "Menu - Selecionar categoria do produto" << endl;
        cout << "**********************************************************" << endl;
        cout << "1 - Bebidas " << endl;
        cout << "2 - Hamburguer: " << endl;
        cout << "3 - Acompanhamentos: " << endl;
        cout << "4 - voltar ao menu anterior " << endl;
        cout << "------------------------------------------------" << endl;

        cout << "Informe a categoria do produto: ";
        cin >> categoriesSelect;

        deleteTerminal();

        switch (categoriesSelect)
        {
        case 1:
            cout << "Relatorio de bebidas: " << endl;
            cout << "------------------------------------------------" << endl;
            for (size_t i = 0; i < menu.size(); i++)
            {
                if (menu[i].getStatusProductCategories() == StatusProductCategories::DRINKS)
                {
                    menu[i].printProduct();
                }
            }
            cout << "\n\n"
                 << endl;

            menuAddOrder(orders, menu, history, orderPreparationQueue, orderNumber, StatusProductCategories::DRINKS);
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;

        default:
            messagesErrorsWarning("opção invalida, tente novamente!");
            break;
        }

    } while (repeat);
}

// função cancelar Pedido
void menuCancelOrder(vector<Order> &orders)
{
    // Chama a busca por código, que já pede o código do produto e retorna a posição
    int OrderIndex = searchOrderNumber(orders);

    cout << "Menu - Cancelar produto " << endl;
    cout << "**********************************************************" << endl;

    // Se o índice for 0 ou maior, o produto existe na lista
    if (OrderIndex >= 0)
    {
        cout << "\nTem certeza que deseja apagar o produto: "
             << orders[OrderIndex].getNumberOrder() << "? (s/n): ";

        char confirm;
        cin >> confirm;

        if (confirm == 's' || confirm == 'S')
        {
            // Apaga o produto do vetor usando o iterador
            orders.erase(orders.begin() + OrderIndex);
            messagesSucess("Produto removido com sucesso!");
        }
        else
        {
            messagesSucess("\nOperacao cancelada.");
        }
    }

    deleteTerminal();
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
    int orderIndex;
    int barCode;
    int quantity;
    char confirm;

    cout << "\n Informe o numero do pedido que deseja adicionar itens : " << endl;
    cin >> orderIndex;
    Order *order;

    try
    {
        // .at() lança std::out_of_range se o índice for inválido
        order = &orders.at(orderIndex - 1);
        messagesSucess("pedido: " + to_string(order->getNumberOrder()) + " selecionado!");
    }
    catch (const std::out_of_range &e)
    {
        // Captura o erro out_of_range especificamente
        messagesErrorsWarning("[ERRO] Posição fora do limite do vetor!");
        return;
    }
    cin.ignore();

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

            menu[index].printProduct();
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
            cout << "\nDeseja adicionar mais um produto ao pedido?(s/n): " << endl;
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
    int orderIndex;
    char confirm;
    char confirmRm;

    cout << "\n Informe o numero do pedido que deseja remover itens : " << endl;
    cin >> orderIndex;
    Order *order;

    try
    {
        // .at() lança std::out_of_range se o índice for inválido
        order = &orders.at(orderIndex - 1);
        messagesSucess("pedido: " + to_string(order->getNumberOrder()) + " selecionado!");
    }
    catch (const std::out_of_range &e)
    {
        messagesErrorsWarning("[ERRO] Posição fora do limite do vetor!");
        return;
    }
    cin.ignore();

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
            cout << "\nDeseja remover mais um produto do pedido?(s/n): " << endl;
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

    deleteTerminal();
}

void closeOrder(vector<Order> &orders, int indexOrder, Order *order, OrderHistoryList *orderHistoryList, OrderPreparationQueue &orderPreparationQueue)
{
    char optionCloseOrder;

    cout << "Confirmar o fechamento do pedido? (s/n)" << endl;
    cin >> optionCloseOrder;

    bool isClosedNow = (optionCloseOrder == 's' || optionCloseOrder == 'S');

    if (isClosedNow)
    {
        if (order->getStatusOrder() != StatusOrder::CANCELADO && order->getStatusOrder() != StatusOrder::PRONTO)
        {
            order->setStatusOrder(StatusOrder::FECHADO);
            orderHistoryList->insertEnd(*order);
            orderPreparationQueue.enqueue(orderHistoryList->getTail()->getOrderPointer());

            if (indexOrder > 0)
            {
                orders.erase(orders.begin() + indexOrder);
            }

            messagesSucess("Pedido fechado com sucesso!");
        }
    }
}
// =======================================================
// MENU PRODUTOS
// =======================================================
// Menu de gerenciamento dos produtos
void menuProducts(vector<Product> &menu)
{
    int responseMenu = 0;
    bool repeat = true;

    menuDividers();

    do
    {
        cout << "MENU - PRODUTOS DA HAMBURGUERIA" << endl;
        cout << "**********************************************************" << endl;
        cout << "1 - Cadastrar um produto" << endl;
        cout << "2 - Editar um produto" << endl;
        cout << "3 - Remover um produto" << endl;
        cout << "4 - Consultar um produto pelo nome" << endl;
        cout << "5 - Consultar lista de produtos cadastrados" << endl;
        cout << "6 - Voltar ao order principal" << endl;
        cout << "\nDigite a opção desejada: ";
        cin >> responseMenu;

        deleteTerminal();
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
        case 6:
            repeat = false;
            break;
        default:
            break;
        }
    } while (repeat);
}

// Adicionar um produto ao menu
void menuAddProduct(vector<Product> &menu)
{

    char confirmMore;

    do
    {
        string name;
        int barCode;
        double price;
        int categoriesProduct;
        Product product;

        menuDividers();

        cout << "Cadastrar produto " << endl;
        cout << "**********************************************************" << endl;

        // Loop para garantir a inserção de um código válido e único
        do
        {
            cout << "Informe o CODIGO do produto: ";
            cin >> barCode;

            if (barCode < 1)
            {
                messagesErrorsWarning("[Erro] O codigo de barras deve ser maior que zero! Tente novamente.");
            }
            else if (productExists(menu, barCode))
            {

                messagesErrorsWarning("[Erro] Ja existe um produto cadastrado com o codigo " + to_string(barCode) + "! Tente novamente.");
            }
        } while (barCode < 0 || productExists(menu, barCode));
        cout << "---------------------------------------------------------------------" << endl;

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
        cout << "---------------------------------------------------------------------" << endl;

        // Loop para garantir a inserção de um preço válido (positivo)
        do
        {
            cout << "Informe o VALOR UNITARIO do produto: ";
            cin >> price;

            if (price < 1)
            {
                messagesErrorsWarning("[Erro] O valor unitario deve ser positivo! Tente novamente.");
            }
        } while (price < 1);
        cout << "---------------------------------------------------------------------" << endl;
        // Loop para garantir a inserção de um código válido e único
        do
        {
            cout << "\nCategorias do produto" << endl;
            cout << "1 - bebidas " << endl;
            cout << "2 - Hambuguer " << endl;
            cout << "3 - Acompanhemento " << endl;
            cout << "\nInforme a categoria do produto: ";
            cin >> categoriesProduct;

            if (categoriesProduct < 1 || categoriesProduct > 3)
            {
                messagesErrorsWarning("[Erro] A categoria deve estar entre os valores [ 1 - 3 ]! Tente novamente.");
            }

        } while (categoriesProduct < 1 || categoriesProduct > 3);

        cout << "---------------------------------------------------------------------" << endl;
        // Salva os dados no objeto
        product.setName(name);
        product.setBarCode(barCode);
        product.setUnitPrice(price);
        product.setStatusProductCategoriesNumber(categoriesProduct);

        // Adiciona o produto ao vetor do menu
        menu.push_back(product);

        messagesSucess("Produto [ " + to_string(barCode) + " ] cadastrado com sucesso!");

        // Pergunta se deseja cadastrar outro produto
        cout << "\nDeseja cadastrar outro produto? (s/n): ";
        cin >> confirmMore;

        if (confirmMore == 's' || confirmMore == 'S')
        {
            deleteTerminal();
        }

    } while (confirmMore == 's' || confirmMore == 'S');

    deleteTerminal();
}

// Editar um produto do order
void menuEditProduct(vector<Product> &menu)
{

    string newName;
    double newPrice;
    char continueClear;
    int newCategoriesProduct;

    do
    {
        cout << "Editar um produto " << endl;
        cout << "**********************************************************" << endl;
        // Chama a busca que pede o código e retorna o índice (posição no vetor)
        int productIndex = searchProductBarCode(menu);

        // Valida se o produto foi encontrado (>= 0 inclui o índice 0)
        if (productIndex >= 0)
        {
            cout << "\n---------------------------------------------------------";
            cout << "\nProduto " << menu[productIndex].getBarCode() << " selecionado!\n";
            cout << "\nCodigo | Nome | Valor" << endl;
            cout << "-------------------" << endl;
            menu[productIndex].printProduct();
            cout << "\n---------------------------------------------------------\n";

            cin.ignore(); // Limpa o buffer do cin para ler o getline sem pular

            // Loop para garantir a inserção de um nome válido e único
            do
            {
                cout << "Informe o NOME do produto: ";
                getline(cin, newName);

                if (newName.empty() || newName.find_first_not_of(" \t\n\r") == string::npos)
                {
                    messagesErrorsWarning("[Erro] O nome do produto deve ser diferente de vazio! Tente novamente.");
                }
                else if (productExistsName(menu, newName))
                {

                    messagesErrorsWarning("[Erro] Ja existe um produto cadastrado com o nome " + newName + "! Tente novamente.");
                }
            } while (newName.empty() || newName.find_first_not_of(" \t\n\r") == string::npos || productExistsName(menu, newName));
            cout << "---------------------------------------------------------------------" << endl;

            // Loop para garantir a inserção de um preço válido (positivo)
            do
            {
                cout << "Informe o VALOR UNITARIO do produto: ";
                cin >> newPrice;

                if (newPrice < 1)
                {
                    messagesErrorsWarning("[Erro] O valor unitario deve ser positivo! Tente novamente.");
                }
            } while (newPrice < 1);
            cout << "---------------------------------------------------------------------" << endl;
            // Loop para garantir a inserção de um código válido e único
            do
            {
                cout << "\nCategorias do produto" << endl;
                cout << "1 - bebidas " << endl;
                cout << "2 - Hambuguer " << endl;
                cout << "3 - Acompanhemento " << endl;
                cout << "\nInforme a categoria do produto: ";
                cin >> newCategoriesProduct;

                if (newCategoriesProduct < 1 || newCategoriesProduct > 3)
                {
                    messagesErrorsWarning("[Erro] A categoria deve estar entre os valores [ 1 - 3 ]! Tente novamente.");
                }

            } while (newCategoriesProduct < 1 || newCategoriesProduct > 3);

            cout << "---------------------------------------------------------------------" << endl;

            // Atualiza o preço apenas se for digitado um valor maior que zero
            menu[productIndex].setName(newName);

            menu[productIndex].setUnitPrice(newPrice);
            menu[productIndex].setStatusProductCategoriesNumber(newCategoriesProduct);

            messagesSucess("Produto [ " + to_string( menu[productIndex].getBarCode()) + " ] atualizado com sucesso!");

            cout << "\nCodigo | Nome | Valor | Categoria" << endl;
            cout << "-------------------" << endl;
            menu[productIndex].printProduct();
            cout << "\n\n";

            cout << "\nPressione qualquer outra para voltar ao menu anterior..." << endl;
            cin >> continueClear;

            continueClear = 'n';
            deleteTerminal();
        }
        else
        {
            cout << "\nPressione a tecla [s] para tentar novamente ou qualquer outra para continuar..." << endl;
            cin >> continueClear;
            deleteTerminal();
            
        }

    } while (continueClear == 's' || continueClear == 'S');

    
}

// Deletar um produto do menu
void menuDeleteProduct(vector<Product> &menu)
{
    char continueClear;
    do
    {
        // Chama a busca por código, que já pede o código do produto e retorna a posição
        cout << "Remover um produto " << endl;
        cout << "**********************************************************" << endl;
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
                messagesErrorsWarning("Produto nao deletado");
            }
        }
        else
        {
            messagesErrorsWarning("Produto nao encontrado!");
            cout << "\nPressione a tecla [s] para tentar novamente ou qualquer outra para continuar..." << endl;
            cin >> continueClear;
        }
    } while (continueClear == 's' || continueClear == 'S');

    deleteTerminal();
}

// Listar todos os produtos que contenham parte de uma palavra
void searchProductName(vector<Product> &menu)
{

    string partName;

    cin.ignore();

    menuDividers();

    cout << "Consultar produto pelo nome " << endl;
    cout << "********************************** " << endl;
    cout << "Informe o NOME do produto: ";
    getline(cin, partName);

    bool found = false;

    cout << "\nCodigo | Nome | Valor | Categoria" << endl;
    cout << "-------------------------------------------" << endl;
    for (size_t i = 0; i < menu.size(); i++)
    {
        // Verifica se o texto digitado em 'partName' está contido na descrição
        if (menu[i].getName().find(partName) != string::npos)
        {
            menu[i].printProduct();
            found = true;
        }
    }

    if (!found)
    {
        messagesErrorsWarning("Nenhum produto encontrado com o termo: " + partName);
    }
    cout <<"\n";

}

// Listar todos os produtos que contenham esse código de barras
int searchProductBarCode(vector<Product> &menu)
{
    int barCode;
    int foundIndex = -1; // Inicializa o índice como -1, indicando que não foi encontrado

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

int searchOrderNumber(vector<Order> &order)
{
    (void)order;
    return 1;
}
// Listar todos os produtos cadastrados no sistema
void showProducts(vector<Product> &menu)
{
    if (menu.size() > 0)
    {
        cout << "\nCodigo | Nome | Valor | Categoria" << endl;
        cout << "-------------------" << endl;
        for (size_t i = 0; i < menu.size(); i++)
        { // size_t é um inteiro positivo (unsigned) usado pelo C++ para tamanhos e índices de vetores
            menu[i].printProduct();
        }
        cout << "\n\n";
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
        {
            // Compara se os nomes são idênticos
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
    cout << "3 - Remover um pedido do historico" << endl;
    cout << "4 - Voltar ao order principal" << endl;
    cout << "\nDigite a opção desejada: ";
    cin >> responseMenu;

    menuDividers();
    switch (responseMenu)
    {
    case 1:
    {
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

        break;
    case 4:

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

    /*
    char continueClear;
    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        system("clear");
    }*/

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
    product.setStatusProductCategories(StatusProductCategories::DRINKS);

    menu.push_back(product);

    product.setBarCode(2);
    product.setName("coca cola 2 litro");
    product.setUnitPrice(14);
    product.setStatusProductCategories(StatusProductCategories::DRINKS);

    menu.push_back(product);

    product.setBarCode(3);
    product.setName("bauru artersal");
    product.setUnitPrice(14);
    product.setStatusProductCategories(StatusProductCategories::BURGERS);

    menu.push_back(product);

    product.setBarCode(4);
    product.setName("hamburguer artesanal");
    product.setUnitPrice(22);
    product.setStatusProductCategories(StatusProductCategories::BURGERS);
    menu.push_back(product);

    product.setBarCode(5);
    product.setName("cheeseburguer");
    product.setUnitPrice(18);
    product.setStatusProductCategories(StatusProductCategories::BURGERS);
    menu.push_back(product);

    product.setBarCode(6);
    product.setName("batatas fritas 300g");
    product.setUnitPrice(13);
    product.setStatusProductCategories(StatusProductCategories::SIDE_DISHES);
    menu.push_back(product);

    product.setBarCode(7);
    product.setName("batatas fritas 800g");
    product.setUnitPrice(30);
    product.setStatusProductCategories(StatusProductCategories::SIDE_DISHES);
    menu.push_back(product);

    product.setBarCode(8);
    product.setName("refrigerante lata");
    product.setUnitPrice(6);
    product.setStatusProductCategories(StatusProductCategories::DRINKS);
    menu.push_back(product);

    product.setBarCode(9);
    product.setName("suco de laranja");
    product.setUnitPrice(8);
    product.setStatusProductCategories(StatusProductCategories::DRINKS);
    menu.push_back(product);

    product.setBarCode(10);
    product.setName("suco de maracuja");
    product.setUnitPrice(7);
    product.setStatusProductCategories(StatusProductCategories::DRINKS);
    menu.push_back(product);

    product.setBarCode(11);
    product.setName("agua mineral");
    product.setUnitPrice(3);
    product.setStatusProductCategories(StatusProductCategories::DRINKS);
    menu.push_back(product);

    // pre-cadastro de pedidos
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

    orderPreparationQueue.enqueue(orderHistory.getTail()->getOrderPointer());
}
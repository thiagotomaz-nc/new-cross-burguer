#include "models/Product.hpp"
#include "models/Order.hpp"
#include "models/Item.hpp"
#include "models/OrderHistoryList.hpp"

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

// Menus historicos
void menuProducts(vector<Product> &menu);
void menuManageOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *orderHistoryList);
void menuCancelOrder(vector<Order> &menu);
void menuManagerHistory(OrderHistoryList *orderHistoryList);
void resumeHistory(OrderHistoryList *orderHistoryList);

// orders
void showOrders(vector<Order> &order);
int searchOrderNumber(vector<Order> &order);
void menuAddOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *historyList);
void menuCancelOrder(vector<Order> &orders);
void menuEditOrder(vector<Order> &orders, vector<Product> &menu);
void menuAddOrderItem(vector<Order> &orders, vector<Product> &menu);
void menuRemoveOrderItem(vector<Order> &orders, vector<Product> &menu);

// configurações
void deleteTerminal();
void menuDividers();
void messagesSucess(string messsage);
void messagesErrorsWarning(string messsage);

// CADASTROS PRÉVIOS
void previousRegistrations(vector<Order> &orders, vector<Product> &menu);

int main()
{
    // inicio variaveis
    int response = 0;
    bool continuar = true;
    Product product;
    vector<Product> menu_products;
    vector<Order> orders;
    OrderHistoryList orderHistoryList;

    previousRegistrations(orders, menu_products);

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
        cout << "10 - Sair do sistema" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "\nDigite a opcao desejada: ";
        cin >> response;

        switch (response)
        {
        case 1:
            menuManageOrder(orders, menu_products, &orderHistoryList);
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
        case 10:
            /* code */
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
void menuManageOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *orderHistoryList)
{

    int responseMenuOrder = 0;

    menuDividers();

    cout << "Menu - Gerenciar Pedidos" << endl;
    cout << "**********************************************************" << endl;
    cout << "1 - Adicionar um pedido" << endl;
    cout << "2 - Cancelar um pedido" << endl;
    cout << "3 - Editar pedido" << endl;
    cout << "4 - Fechar um pedido " << endl;
    cout << "5 - Consultar lista de produtos cadastrados" << endl;
    cout << "6 - Relatorio de pedidos" << endl;
    cout << "7 - Voltar ao menu principal" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "\nDigite a opcao desejada: ";
    cin >> responseMenuOrder;
    cout << "---------------------------------------------------------" << endl;

    switch (responseMenuOrder)
    {
    case 1:
        menuAddOrder(orders, menu, orderHistoryList);
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
        int optionCloseOrder;

        cout << "\n Informe o numero do pedido que deseja fechar : " << endl;
        cin >> orderIndex;
        Order *order;

        try
        {
            // .at() lança std::out_of_range se o índice for inválido
            order = &orders.at(orderIndex - 1);
            cout << "\n pedido: " << order->getNumberOrder() << " selecionado!" << endl;

            if (order->getStatusOrder() == static_cast<int>(StatusOrder::FECHADO))
            {
                messagesErrorsWarning("Atencao o pedido" +to_string(order->getNumberOrder()) +" ja esta fechado!");
                return;
            }

            cout << "Confirmar o fechamento do pedido? 1 - [Sim] | 0 - [Nao]" << endl;

            cin >> optionCloseOrder;

            if (optionCloseOrder == 1)
            {
                if (order->getStatusOrder() != static_cast<int>(StatusOrder::CANCELADO) && order->getStatusOrder() != static_cast<int>(StatusOrder::PRONTO))
                {
                    order->setStatusOrder(StatusOrder::FECHADO);
                    orderHistoryList->insertBegin(*order);

                    messagesSucess("Pedido fechado com sucesso!");
                }
            }
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
        cout << "RELATORIO DOS PEDIDOS" << endl;
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
            messagesSucess("Nenhum produto cadastrado.");
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
    cout << "3 - Desfazer a ultima ação do um item" << endl;
    cout << "4 - Editar o nome do cliente: " << endl;
    cout << "5 - Editar a mesa: " << endl;
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
        if (!newName.empty() || !newName.find_first_not_of(" \t\n\r") == string::npos)
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
// Menu de cadastro de pedidos
void menuAddOrder(vector<Order> &orders, vector<Product> &menu, OrderHistoryList *historyList)
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

    // Pergunta sobre o fechamento do pedido
    char closeOrder;
    cout << "-------------------------------------------" << endl;
    cout << "\nDeseja fechar o pedido agora? (s/n): ";
    cin >> closeOrder;

    bool isClosedNow = (closeOrder == 's' || closeOrder == 'S');
    if (isClosedNow)
    {
        currentOrder.setStatusOrder(StatusOrder::FECHADO);
    }
    else
    {
        currentOrder.setStatusOrder(StatusOrder::EM_CONSTRUCAO);
    }

    // Lê os dados cadastrais
    string clientName;
    int clientSeat;

    cout << "\nDigite o nome do cliente: ";
    cin >> clientName;
    cout << "Digite o numero da mesa: ";
    cin >> clientSeat;

    // Atribui o número sequencial correto
    // Garante uma sequência exata: 1, 2, 3, 4, 5...
    int nextNumber = orders.size() + 1;

    currentOrder.setNumberOrder(nextNumber);
    currentOrder.setNameClient(clientName);
    currentOrder.setNumberTable(clientSeat);
    currentOrder.sumTotalPriceToOrder();

    // Salva no vetor ativo
    orders.push_back(currentOrder);

    // Insere no histórico apenas se estiver FECHADO
    if (isClosedNow && historyList != nullptr)
    {
        historyList->insertEnd(currentOrder);
    }

    cout << "\n========================================" << endl;
    cout << " Pedido N. " << currentOrder.getNumberOrder() << " finalizado com sucesso!" << endl;
    cout << " Total: R$ " << currentOrder.getTotalPriceToOrder() << endl;
    cout << " Status: " << (isClosedNow ? "FECHADO" : "EM CONSTRUÇÃO") << endl;
    cout << "========================================\n" << endl;
}

// função cancelar Pedido
void menuCancelOrder(vector<Order> &orders)
{
    char continueClear;

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

    cout << "\nPressione a tecla [s] para Limpar o terminal ou qualquer outra para continuar..." << endl;
    cin >> continueClear;

    if (continueClear == 's' || continueClear == 'S')
    {
        deleteTerminal();
    }
}

int searchOrderNumber(vector<Order> &order)
{
    (void)order;
    return 1;
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

    if (order->getStatusOrder() == static_cast<int>(StatusOrder::EM_CONSTRUCAO))
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
            cout << "\nDeseja adicionar mais um produto ao pedido?(s/n): " << endl;
            cin >> confirm;
        } while (confirm == 's' || confirm == 'S');
    }
    else
    {
        messagesErrorsWarning("Pedido em estado " + to_string(order->getStatusOrder()) + " não permite adicionar itens!");
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

    if (order->getStatusOrder() == static_cast<int>(StatusOrder::EM_CONSTRUCAO))
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
        messagesErrorsWarning("Pedido em estado " + to_string(order->getStatusOrder()) + " não permite remover itens!");
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
    cout << "3 - Remover um pedido do historico" << endl;
    cout << "4 - Voltar ao order principal" << endl;
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

    int size = orderHistoryList->getSize();
    
    cout << "Total de Pedidos " << size << endl;
    if (size > 0)
    {
        OrderHistory* aux = orderHistoryList->gethead();

        menuDividers();

        cout << "Menu - Resumo Historico de pedidos" << endl;
        cout << "**********************************************************" << endl;
        cout << "1 - Proximo  | 2 - Anterior | 0 - Voltar menu principal"   << endl;
        cout << "\nDigite a opção desejada: ";
        cin >> responseMenu;
        
        deleteTerminal();

        menuDividers();

        switch (responseMenu)
        {
        case 1:

            aux->getOrder().showResumeOrder();
            aux = aux->getNext();

            if (aux == nullptr){
                orderHistoryList->gethead();
            }

            break;
        case 2:
            aux = aux->getPrevious();

            if (aux == nullptr){
                aux = orderHistoryList->getTail();
            }
           
            aux->getOrder().showResumeOrder();
            
            break;
        default:
            break;
        }
    }
    else
    {
        messagesErrorsWarning("Nenhum pedido no historico!");
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
void previousRegistrations(vector<Order> &orders, vector<Product> &menu)
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
    product.setName("bauru artersal");
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

    // pre-cadastro de pedidos
    Order order_temp;

    order_temp.setNameClient("Thiago");
    order_temp.setNumberOrder(0);
    order_temp.setNumberTable(1);
    item.setProductItem(menu[0]);
    item.setQuantityItem(3);
    order_temp.addItemToOrder(item);
    order_temp.sumTotalPriceToOrder();
    order_temp.setStatusOrder(StatusOrder::EM_CONSTRUCAO);
    orders.push_back(order_temp);

    order_temp.setNameClient("Thiago");
    order_temp.setNumberOrder(1);
    order_temp.setNumberTable(2);
    item.setProductItem(menu[9]);
    item.setQuantityItem(10);
    order_temp.addItemToOrder(item);
    item.setProductItem(menu[8]);
    item.setQuantityItem(6);
    order_temp.addItemToOrder(item);
    order_temp.sumTotalPriceToOrder();
    order_temp.setStatusOrder(StatusOrder::FECHADO);

    orders.push_back(order_temp);

} 
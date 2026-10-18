#include "../models/Order.hpp"

Order::Order()
{
    this->statusOrder = StatusOrder::EM_CONSTRUCAO;
    this->numberOrder = 0;
}

Order::Order(const Order &other)
{
    this->numberOrder = other.numberOrder;
    this->numberTable = other.numberTable;
    this->nameClient = other.nameClient;
    this->items = other.items;
    this->priceTotalToOrder = other.priceTotalToOrder;
    this->statusOrder = other.statusOrder;
}

void Order::addItemToOrder(Item item)
{
    this->items.push_back(item);
}

int Order::getItemsCount()
{
    return this->items.size();
}

void Order::removeItemFromOrder(int index)
{
    if (index >= 0 && static_cast<size_t>(index) < this->items.size())
    {
        // Apaga o produto do vetor usando o iterador
        this->items.erase(items.begin() + index);
        // adicionar a pilha de ações;
    }
}

int Order::getOdeItemIndex(int numberItemOrder){
    for (size_t i = 0; i < this->items.size(); i++){
        if (this->items[i].getProductItem().second.getBarCode() == numberItemOrder){
            return i;
        }

    }

    return -1;
}

// optional armazena o objeto diretamente quando existe
pair<bool, Item> Order::getItemToIndex(int index)
{
    if (index >= 0 && static_cast<size_t>(index) < this->items.size())
    {
        return {true, this->items[index]};
    }
    return {false, Item{}};
}

void Order::sumTotalPriceToOrder()
{
    double sumPriceTotal = 0.0;
    // size_t é um tipo inteiro sem sinal
    for (size_t i = 0; i < this->items.size(); i++)
    {
        sumPriceTotal += this->items[i].getPriceTotalItem();
    };

    this->priceTotalToOrder = sumPriceTotal;
}

double Order::getTotalPriceToOrder()
{
    return this->priceTotalToOrder;
}

int Order::setNumberOrder(int newNumberOrder)
{
    this->numberOrder = newNumberOrder; // Sem somar + 1 aqui!
    return this->numberOrder;
}

void Order::setNumberTable(int newNumberTable)
{
    this->numberTable = newNumberTable;
}

int Order::getNumberOrder()
{
    return this->numberOrder;
}

int Order::getNumberTable()
{
    return this->numberTable;
}

void Order::setNameClient(string newNameClient)
{
    this->nameClient = newNameClient;
}

string Order::getNameClient()
{
    if (this->nameClient.empty())
    {
        return "Cliente Avulso";
    }
    return this->nameClient;
}

void Order::setStatusOrder(StatusOrder newStatusOrder)
{
    this->statusOrder = newStatusOrder;
}

StatusOrder Order::getStatusOrder()
{
    return this->statusOrder;
}

string Order::statusToString(StatusOrder status)
{
    switch (status)
    {
    case StatusOrder::CANCELADO:
        return "CANCELADO";
    case StatusOrder::EM_CONSTRUCAO:
        return "EM_CONSTRUCAO";
    case StatusOrder::FECHADO:
        return "FECHADO";
    case StatusOrder::PRONTO:
        return "PRONTO";
    case StatusOrder::COZINHA:
        return "COZINHA";
    case StatusOrder::PREPARO:
        return "EM PREPARO";
    case StatusOrder::FINALIZADO:
        return "FINALIZADO";
    default:
        return "status não encontrado";
    }
}

void Order::showResumeOrder()
{
    cout <<"\nPEDIDO: " <<setfill('0') << setw(DECIMAL_PLACES_ORDER) << this->numberOrder << endl ;    
    cout <<"Numero da mesa | Cliente | status do pedido" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << this->numberTable << " | " << this->nameClient << " | " << statusToString(this->statusOrder) << endl;
    cout << "----------------------------------------------------------------"<< endl;
    cout << "\nITENS " << endl;
    cout << "Numero | cod. produto | Descricao | Preco unit. x quant.  =  total R$" << endl;
    cout << "----------------------------------------------------------------" << endl;

    if (this->items.size() > 0)
    {

        for (size_t i = 0; i < this->items.size(); i++)
        {
            this->items[i].showItems(i);
        }

        cout << "\nTotal do pedido:  R$ " << getTotalPriceToOrder() << endl;
        cout << "----------------------------------";
        cout << "\n##############################################################################"
             << endl;
    }
    else
    {
        cout << "\n---------------------------------------------------------" << endl;
        cout << "Nenhum item adicionado." << endl;
        cout << "---------------------------------------------------------\n"
             << endl;
    }
}

int Order::findItemIndexByBarCode(int barCode)
{
    // Percorre todos os itens atualmente adicionados ao pedido
    for (size_t i = 0; i < this->items.size(); ++i)
    {
        // Auto: Desestrutura o pair<bool, Product> retornado por getProductItem()
        // extrai automaticamente os elementos de dentro do pair:
        // hasProduct vira uma variável do tipo bool (recebe o first)
        // product vira uma variável do tipo Product (recebe o second)

        // hasProduct: indica se existe um produto válido no item
        // product: objeto do produto
        auto [hasProduct, product] = this->items[i].getProductItem();

        // Garante que você só vai ler o código de barras (getBarCode()) se o produto realmente existir dentro daquele item do pedido.
        if (hasProduct && product.getBarCode() == barCode)
        {
            return static_cast<int>(i); // Retorna a posição do item no pedido
        }
    }

    // Retorna -1 se o produto não for encontrado na lista de itens deste pedido
    return -1;
}

Order::~Order() {}

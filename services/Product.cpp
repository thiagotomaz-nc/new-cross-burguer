#include "../models/Product.hpp"

Product::Product() {}

int Product::getBarCode() const
{
    return this->barCode;
}

string Product::getName() const
{
    return this->name;
}

float Product::getUnitPrice() const
{
    return this->unitPrice;
}

void Product::setBarCode(int newBarCode)
{
    this->barCode = newBarCode;
}

void Product::setName(string newName)
{
    this->name = newName;
}

void Product::setUnitPrice(float newUnitPrice)
{
    this->unitPrice = newUnitPrice;
}

StatusProductCategories Product::getStatusProductCategories() const
{
    return this->statusProductCategories;
}

void Product::setStatusProductCategories(StatusProductCategories newStatusProductCategories)
{
    this->statusProductCategories = newStatusProductCategories;
}

void Product::setStatusProductCategoriesNumber(int newStatusProductCategories)
{
    switch (newStatusProductCategories)
    {
    case 1:
        this->statusProductCategories = StatusProductCategories::DRINKS;
        break;
    case 2:
        this->statusProductCategories = StatusProductCategories::BURGERS;
        break;
    case 3:
        this->statusProductCategories = StatusProductCategories::SIDE_DISHES;
        break;
    default:
        break;
    }
}

string Product::statusProductToString(StatusProductCategories status) const
{
    switch (status)
    {
    case StatusProductCategories::DRINKS:
        return "BEBIDA";
    case StatusProductCategories::BURGERS:
        return "HAMBURGUER";
    case StatusProductCategories::SIDE_DISHES:
        return "ACOMPANHAMENTO";
    default:
        return "-";
    }
}

void Product::printProduct() const
{
    cout << setfill('0') << setw(DECIMAL_PLACES) << this->barCode
         << "  |  " << this->name
         << "   | R$ " << this->unitPrice << " | " << statusProductToString(this->statusProductCategories) << endl;
}


#include "fooditem.h"
#include <iostream>
#include <iomanip>
using namespace std;

FoodItem::FoodItem() {
    ItemName = "";
    price = 0;
    quantity = 0;
}

FoodItem::FoodItem(string iname, double p, int q) {
    ItemName = iname;
    price = p;
    quantity = q;
}

void FoodItem::SetItemName(string iname) {
    ItemName = iname;
}

void FoodItem::SetPrice(double p) {
    price = p;
}

void FoodItem::SetQuantity(int q) {
    quantity = q;
}

string FoodItem::GetItemName() const {
    return ItemName;
}

double FoodItem::GetPrice() const {
    return price;
}

int FoodItem::GetQuantity() const {
    return quantity;
}

double FoodItem::calculateItemTotal() const {
    return quantity * price;
}

void FoodItem::displayItem() const {

    cout << fixed << setprecision(2);

    cout << ItemName << " x" << quantity
         << " @" << price << " EGP = "
         << calculateItemTotal() << " EGP";
         
}

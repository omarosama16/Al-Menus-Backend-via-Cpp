
#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
using namespace std;

class FoodItem {
private:
    string ItemName;
    double price;
    int quantity;

public:
    FoodItem();
    FoodItem(string iname, double p, int q);
    
    void SetItemName(string iname);
    void SetPrice(double p);
    void SetQuantity(int q);
    
    string GetItemName() const;
    double GetPrice() const;
    int GetQuantity() const;
    
    double calculateItemTotal() const;
    void displayItem() const;
};

#endif
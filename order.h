

#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "enums.h"       
#include "fooditem.h"    
#include "customer.h"    
#include "deliverydriver.h" 

using namespace std;


class order{
private:

    string orderID ;
    customer* cust ;
    deliverydriver* driver ;
    FoodItem* items;
    int itemcount ;
    int capacity ;
    OrderStatus status ;
    static int totalOrders;

    void ArrayResizer(); // its the funcion that reszes the array makes it double and copy the items 

public:

    order();

    order(string id, customer* customer);
    //---------------------------
    ~order();
    //--------------------------
    order(const order& copied);
    //----------------------------
    void addItem(const FoodItem& item);

    void assignDriver(deliverydriver* drviver);

    void updateStatus(OrderStatus NewStatus);

    double calculateTotal() const;

    void displayOrder() const;

    static int getTotalOrders();
    //------------------------
    string getOrderId() const;
    customer* getCustomer() const;
    deliverydriver* getDriver() const;
    OrderStatus getStatus() const;
    int getItemCount() const;
    //--------------------------------
    order& operator=(const order& other);
    //------------------------------
    order& operator+=(const FoodItem& item);
    order operator+(const order& other) const;
     //--------------------------------------------  
    //compare operator
    friend bool operator>(const order& l, const order& r);
    friend bool operator<(const order& l, const order& r);  
    //-----------------------------------------------------------
    // access item by index con. & not con. 
    FoodItem& operator[](int index);
    const FoodItem& operator[](int index) const;
    //-------------------------------------------
    friend ostream& operator<<(ostream& os, const order& orders);
};


#endif   

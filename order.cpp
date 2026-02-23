
#include "order.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

int order::totalOrders = 0;
//----------------------------------
order::order() : orderID(""), cust(nullptr), driver(nullptr), items(nullptr), 
                itemcount(0), capacity(10), status(OrderStatus::PENDING) {
    items = new FoodItem[capacity];
    totalOrders++;
    orderID = "ORD" + to_string(totalOrders);
}
//--------------------------------------------------
order::order(string id, customer* customer) : 
    orderID(id), cust(customer), driver(nullptr), items(nullptr),
    itemcount(0), capacity(10), status(OrderStatus::PENDING) {
    items = new FoodItem[capacity];
    totalOrders++;
}
//----------------------------------------
order::order(const order& copied) : 
    orderID(copied.orderID), cust(copied.cust), driver(copied.driver),
    itemcount(copied.itemcount), capacity(copied.capacity), status(copied.status) {
    
    items = new FoodItem[capacity];
    for (int i = 0; i < itemcount; i++) {
        items[i] = copied.items[i];
    }
    totalOrders++;
}
//----------------------------
order::~order() {
    delete[] items;
    totalOrders--;
}
//----------------------------
order& order::operator=(const order& other) {
    if (this != &other) {
        delete[] items;
        
        orderID = other.orderID;
        cust = other.cust;
        driver = other.driver;
        itemcount = other.itemcount;
        capacity = other.capacity;
        status = other.status;
        
        items = new FoodItem[capacity];
        for (int i = 0; i < itemcount; i++) {
            items[i] = other.items[i];
        }
    }
    return *this;
}

// array doubler to the size ( makes it double when it reaches max and copy items)
void order::ArrayResizer() {
    int newCapacity = capacity * 2;
    FoodItem* newItems = new FoodItem[newCapacity];
    
    for (int i = 0; i < itemcount; i++) {
        newItems[i] = items[i];
    }
    
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}
//-------------------------------------------
void order::addItem(const FoodItem& item) {
    if (itemcount >= capacity) {
        ArrayResizer();
    }
    items[itemcount] = item;
    itemcount++;
}

//----------------------------------------------------
void order::assignDriver(deliverydriver* drviver) {
    driver = drviver;
}
//----------------------------------------------------
void order::updateStatus(OrderStatus NewStatus) {
    status = NewStatus;
    
    if (status == OrderStatus::DELIVERED && driver != nullptr && cust != nullptr) {
        double orderValue = calculateTotal();
        driver->completeDelivery(orderValue);
        ++(*driver);
        
        int loyaltyPoints = static_cast<int>(orderValue / 2);
        cust->setLoyaltyPoints(cust->getLoyaltyPoints() + loyaltyPoints);
    }
}
//---------------------------------------------------------
double order::calculateTotal() const {
    double total = 0.0;
    for (int i = 0; i < itemcount; i++) {
        total += items[i].GetPrice();
    }
    return total;
}
//------------------------------------------------------------------------
void order::displayOrder() const {
    cout << endl <<"---------------- ORDER DETAILS -----------" << endl;
    cout << "Order ID: " << orderID << endl;
    
    if (cust != nullptr) {
        cout << "Customer: " << cust->getName() << endl;
    }
    
    if (driver != nullptr) {
        cout << "Driver: " << driver->getName() << endl;
    }
    
        cout << "Status: ";
    switch (status) {
        case OrderStatus::PENDING: cout << "pending"; break;
        case OrderStatus::PREPARING: cout << "preparing"; break;
        case OrderStatus::OUT_FOR_DELIVERY: cout << "out for delivery"; break;
        case OrderStatus::DELIVERED: cout << "delivered"; break;
        case OrderStatus::CANCELLED: cout << "cancelled"; break;
    }
    cout << endl; 
    
    cout << "Items (" << itemcount << "):" << endl;
    for (int i = 0; i < itemcount; i++) {
        cout << "  - " << items[i].GetItemName() 
             << ":" << fixed << setprecision(2) << items[i].GetPrice() <<"  EGP" << endl;
    }
    
    cout << "Total: " << fixed << setprecision(2) << calculateTotal() << " EGP" <<endl;
    cout << "-----------------------------" << endl;
}

//-------------------------------
int order::getTotalOrders() {
    return totalOrders;
}
//-----------------------------------------
// Get
string order::getOrderId() const {
    return orderID;
       }

customer* order::getCustomer() const {
    return cust;
     }

deliverydriver* order::getDriver() const {
    return driver;
           } 

OrderStatus order::getStatus() const {
     return status;
}

int order::getItemCount() const {
    return itemcount;
}
//--------------------------------------------------
order& order::operator+=(const FoodItem& item) {
    addItem(item);
    return *this;
}

//---------------------------------------------------
order order::operator+(const order& other) const {
    // create new order with customer from first order
    order newOrder(this->orderID + "_merged", this->cust);
    
    // then add items from 1st order
    for (int i = 0; i < this->itemcount; i++) {
        newOrder.addItem(this->items[i]);
    }
    
    // then add items from 2nd order
    for (int i = 0; i < other.itemcount; i++) {
        newOrder.addItem(other.items[i]);
    }
    
    if (this->driver != nullptr) {
        newOrder.assignDriver(this->driver);
    }
    
    return newOrder;
}
//---------------------------------
// compare opperators
bool operator>(const order& l, const order& r) {
    return l.calculateTotal() > r.calculateTotal();
}

bool operator<(const order& l, const order& r) {
    return l.calculateTotal() < r.calculateTotal();
}
//--------------------------------------------------------
// operator [] ( without cons)
FoodItem& order::operator[](int index) {
    if (index < 0 || index >= itemcount) {
        throw out_of_range("Index " + to_string(index) + 
                          " is out of bounds for order with " + 
                          to_string(itemcount) + " items");
    }
    return items[index];
}
// operator [] (cons)
const FoodItem& order::operator[](int index) const {
    if (index < 0 || index >= itemcount) {
        throw out_of_range("Index " + to_string(index) + 
                          " is out of bounds for order with " + 
                          to_string(itemcount) + " items");
    }
    return items[index];
}
//--------------------------------------------------------------------------
ostream& operator<<(ostream& os, const order& orders) {
    os << "order ID: " << orders.orderID << endl;
    os << "customer: " << (orders.cust ? orders.cust->getName() : "No Customer") << endl;
    os << "driver: " << (orders.driver ? orders.driver->getName() : "No Driver") << endl;
    os << "order sstatus: " << static_cast<int>(orders.status) << endl;
    os << "items: " << orders.itemcount << endl;
    os << "total: " << orders.calculateTotal() << "  EGP" << endl;
    return os;
}
// condition ? value_if_true : value_if_false
 
 /*
 static_cast <destination_type> (source_expression);
 operator used for compile-time type conversions between related or compatible data types
 It provides type checking during compilation, making it safer than C-style casts in many scenarios. 
 */

#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include <iostream>
#include <string>
#include "fileoperation.h"
#include "order.h"
#include "deliverydriver.h" 
using namespace std;


struct OrderRecord {
    char orderId[50];
    char customerName[100];
    char driverName[100];
    double totalAmount;
    int status;  
    int itemCount;
    char timestamp[50];
    
    OrderRecord();
    OrderRecord(const order& order);  
    void display() const;
};

class FileOperations {
public:
    static void saveCompletedOrdersToFile(order** orders, int orderCount, 
                                         const string& filename = "Completed.txt");
    
    static void saveDriverStatistics(deliverydriver** drivers, int driverCount,
                                    const string& filename = "drivers.txt");
    
    static void saveOrdersToBinaryFile(order** orders, int orderCount,
                                      const string& filename = "Orders.dat");
    
    static OrderRecord loadOrderFromBinaryFile(const string& filename, int position);
    
    static void displayBinaryFileStatistics(const string& filename = "orders.dat");  
};

#endif
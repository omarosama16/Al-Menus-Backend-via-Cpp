
#include "fileoperation.h"
#include "order.h"
#include "deliverydriver.h" 
#include <ctime>
#include <cstring>
#include <fstream>
#include <chrono>
using namespace std;

OrderRecord::OrderRecord() {
    memset(this, 0, sizeof(OrderRecord));
}

OrderRecord::OrderRecord(const order& order) { 
    memset(this, 0, sizeof(OrderRecord));
    
    
    string id = order.getOrderId();
    strncpy(orderId, id.c_str(), 49);
    orderId[49] = '\0'; 
    
    if (order.getCustomer()) {
        string name = order.getCustomer()->getName();
        strncpy(customerName, name.c_str(), 99);
        customerName[99] = '\0';
    }
    
    if (order.getDriver()) {
        string name = order.getDriver()->getName();
        strncpy(driverName, name.c_str(), 99);
        driverName[99] = '\0';
    }
    
    totalAmount = order.calculateTotal();
    status = static_cast<int>(order.getStatus()); 
    itemCount = order.getItemCount();
    

    time_t now = time(0);
    strftime(timestamp, 50, "%Y-%m-%d %H:%M:%S", localtime(&now));
    timestamp[49] = '\0';
}

void OrderRecord::display() const {
    cout << "Order: " << orderId << endl;
    cout << "Customer: " << customerName << endl;
    cout << "Driver: " << driverName << endl;
    cout << "Total: " << totalAmount << " EGP" << endl;
    cout << "Status: " << status << endl; 
    cout << "Time: " << timestamp << endl;
}

void FileOperations::saveCompletedOrdersToFile(order** orders, int orderCount, const string& filename) {
    cout << "\nSaving completed orders...\n";
    
    ofstream file(filename);
    if (!file) {
        cout << "File error\n";
        return;
    }
    
    int count = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i] && orders[i]->getStatus() == OrderStatus::DELIVERED) {
            count++;
            
            cout << "Order: " << orders[i]->getOrderId() << endl;
            
            file << "Order: " << orders[i]->getOrderId() << endl;
        }
    }
    
    file.close();
    cout << "Saved: " << filename << endl;
}

void FileOperations::saveDriverStatistics(deliverydriver** drivers, int driverCount, const string& filename) {
    cout << "\nSaving driver stats...\n";
    
    ofstream file(filename);
    if (!file) {
        cout << "File error\n";
        return;
    }
    
    for (int i = 0; i < driverCount; i++) {
        if (drivers[i]) {
         
            cout << "Driver: " << drivers[i]->getName() << endl;
    
            file << "Driver: " << drivers[i]->getName() << endl;
            file << "Earnings: " << drivers[i]->getTotalEarnings() << " EGP" << endl;
        }
    }
    
    file.close();
    cout << "Saved: " << filename << endl;
}

void FileOperations::saveOrdersToBinaryFile(order** orders, int orderCount, const string& filename) {
    cout << "\nSaving binary...\n";
    
    ofstream file(filename, ios::binary);
    if (!file) return;
    
    for (int i = 0; i < orderCount; i++) {
        if (orders[i]) {
            OrderRecord rec(*orders[i]);
            file.write((char*)&rec, sizeof(rec));
        }
    }
    
    file.close();
    cout << "Binary saved: " << filename << endl;
}


OrderRecord FileOperations::loadOrderFromBinaryFile(const string& filename, int position) {
    OrderRecord rec;
    
    auto start = chrono::high_resolution_clock::now();
    
    ifstream file(filename, ios::binary);
    if (!file) return rec;
    
    file.seekg(position * sizeof(rec));
    file.read((char*)&rec, sizeof(rec));
    
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
    cout << "Load time: " << time.count() << " ns (O(1))\n";
    
    file.close();
    return rec;
}


void FileOperations::displayBinaryFileStatistics(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) return;
    
    long size = file.tellg();
    file.close();
    
    cout << "\nBinary file: " << filename << endl;
    cout << "Size: " << size << " bytes\n";
    cout << "Records: " << (size / sizeof(OrderRecord)) << endl;
}
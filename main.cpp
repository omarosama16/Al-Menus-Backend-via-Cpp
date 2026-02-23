
#include <iostream>
#include <string>
#include <limits>
#include "fooditem.h"
#include "customer.h"
#include "deliverydriver.h"
#include "order.h"
#include "fileoperation.h"

using namespace std;

customer* customers[100];
deliverydriver* drivers[100];
order* orders[100];

int customerCount = 0;
int driverCount = 0;
int orderCount = 0;

void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void cleanup() {
    for (int i = 0; i < customerCount; i++) delete customers[i];
    for (int i = 0; i < driverCount; i++) delete drivers[i];
    for (int i = 0; i < orderCount; i++) delete orders[i];
}

void registerCustomer() {
    if (customerCount >= 100) {
        cout << "Max customers reached!\n";
        return;
    }

    clearBuffer();

    string id, name, phone, address;
    cout << "Customer ID: "; getline(cin, id);
    cout << "Name: "; getline(cin, name);
    cout << "Phone: "; getline(cin, phone);
    cout << "Address: "; getline(cin, address);

    customers[customerCount] = new customer(id, name, phone, address);
    customerCount++;
    cout << "Customer added!\n";
}

void registerDriver() {
    if (driverCount >= 100) {
        cout << "Max drivers reached!\n";
        return;
    }

    clearBuffer();

    string id, name, phone, vehicle;
    cout << "Driver ID: "; getline(cin, id);
    cout << "Name: "; getline(cin, name);
    cout << "Phone: "; getline(cin, phone);
    cout << "Vehicle: "; getline(cin, vehicle);

    drivers[driverCount] = new deliverydriver(id, name, phone, vehicle);
    driverCount++;
    cout << "Driver added!\n";
}

void showCustomers() {
    if (customerCount == 0) {
        cout << "No customers!\n";
        return;
    }

    for (int i = 0; i < customerCount; i++) {
        cout << "\nCustomer " << i+1 << ":\n";
        customers[i]->displayInfo();
    }
}

void showDrivers() {
    if (driverCount == 0) {
        cout << "No drivers!\n";
        return;
    }

    for (int i = 0; i < driverCount; i++) {
        cout << "\nDriver " << i+1 << ":\n";
        drivers[i]->displayInfo();
    }
}

void createOrder() {
    if (customerCount == 0) {
        cout << "No customers! Register customer first.\n";
        return;
    }

    clearBuffer();

    string orderId;
    cout << "Order ID: ";
    getline(cin, orderId);

    cout << "Select customer (0-" << customerCount-1 << "):\n";
    for (int i = 0; i < customerCount; i++) {
        cout << i << ". " << customers[i]->getName() << endl;
    }

    int custIndex;
    cin >> custIndex;
    clearBuffer();

    if (custIndex < 0 || custIndex >= customerCount) {
        cout << "Invalid customer!\n";
        return;
    }

    orders[orderCount] = new order(orderId, customers[custIndex]);

    char addMore;
    do {
        string itemName;
        double price;
        int quantity;

        cout << "Item name: ";
        getline(cin, itemName);

        cout << "Price: ";
        cin >> price;

        cout << "Quantity: ";
        cin >> quantity;
        clearBuffer();

        FoodItem item(itemName, price, quantity);
        orders[orderCount]->addItem(item);

        cout << "Add more items? (y/n): ";
        cin >> addMore;
        clearBuffer();

    } while (addMore == 'y' || addMore == 'Y');

    orderCount++;
    cout << "Order created!\n";
}

void assignDriver() {
    if (orderCount == 0 || driverCount == 0) {
        cout << "Need orders and drivers first!\n";
        return;
    }

    cout << "Select order (0-" << orderCount-1 << "):\n";
    for (int i = 0; i < orderCount; i++) {
        cout << i << ". " << orders[i]->getOrderId() << endl;
    }

    int orderIndex;
    cin >> orderIndex;
    clearBuffer();

    cout << "Select driver (0-" << driverCount-1 << "):\n";
    for (int i = 0; i < driverCount; i++) {
        cout << i << ". " << drivers[i]->getName() << endl;
    }

    int driverIndex;
    cin >> driverIndex;
    clearBuffer();

    if (orderIndex < 0 || orderIndex >= orderCount ||
        driverIndex < 0 || driverIndex >= driverCount) {
        cout << "Invalid selection!\n";
        return;
    }

    orders[orderIndex]->assignDriver(drivers[driverIndex]);
    cout << "Driver assigned!\n";
}

void updateStatus() {
    if (orderCount == 0) {
        cout << "No orders!\n";
        return;
    }

    cout << "Select order (0-" << orderCount-1 << "):\n";
    for (int i = 0; i < orderCount; i++) {
        cout << i << ". " << orders[i]->getOrderId() << endl;
    }

    int orderIndex;
    cin >> orderIndex;
    clearBuffer();

    cout << "Status (0=PENDING, 1=PREPARING, 2=OUT_FOR_DELIVERY, 3=DELIVERED, 4=CANCELLED): ";
    int statusInt;
    cin >> statusInt;
    clearBuffer();

    orders[orderIndex]->updateStatus(static_cast<OrderStatus>(statusInt));
    cout << "Status updated!\n";
}

void showOrder() {
    if (orderCount == 0) {
        cout << "No orders!\n";
        return;
    }

    cout << "Select order (0-" << orderCount-1 << "):\n";
    for (int i = 0; i < orderCount; i++) {
        cout << i << ". " << orders[i]->getOrderId() << endl;
    }

    int orderIndex;
    cin >> orderIndex;
    clearBuffer();

    orders[orderIndex]->displayOrder();
}

void saveCompletedOrders() {
    if (orderCount == 0) {
        cout << "No orders!\n";
        return;
    }
    FileOperations::saveCompletedOrdersToFile(orders, orderCount);
}

void saveDriverStats() {
    if (driverCount == 0) {
        cout << "No drivers!\n";
        return;
    }
    FileOperations::saveDriverStatistics(drivers, driverCount);
}

void saveToBinary() {
    if (orderCount == 0) {
        cout << "No orders!\n";
        return;
    }
    FileOperations::saveOrdersToBinaryFile(orders, orderCount);
}

void loadFromBinary() {
    cout << "Enter position to load: ";
    int pos;
    cin >> pos;
    clearBuffer();
    FileOperations::loadOrderFromBinaryFile("Orders.dat", pos);
}

void showBinaryInfo() {
    FileOperations::displayBinaryFileStatistics();
}

int main() {
    cout << "ELMENUS Food Delivery System\n";
    cout << "=============================\n";

    int choice;

    do {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Register Customer\n";
        cout << "2. Register Driver\n";
        cout << "3. Show Customers\n";
        cout << "4. Show Drivers\n";
        cout << "5. Compare Orders (Skipped)\n";
        cout << "6. Order Stats (Skipped)\n";
        cout << "7. Create Order\n";
        cout << "8. Assign Driver\n";
        cout << "9. Update Status\n";
        cout << "10. Show Order\n";
        cout << "11. Save Completed Orders\n";
        cout << "12. Save Driver Stats\n";
        cout << "13. Save to Binary\n";
        cout << "14. Load from Binary\n";
        cout << "15. Show Binary Info\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        cin >> choice;
        clearBuffer();

        switch (choice) {
            case 1: registerCustomer(); break;
            case 2: registerDriver(); break;
            case 3: showCustomers(); break;
            case 4: showDrivers(); break;
            case 5: cout << "Compare Orders is skipped.\n"; break;
            case 6: cout << "Order Stats is skipped.\n"; break;
            case 7: createOrder(); break;
            case 8: assignDriver(); break;
            case 9: updateStatus(); break;
            case 10: showOrder(); break;
            case 11: saveCompletedOrders(); break;
            case 12: saveDriverStats(); break;
            case 13: saveToBinary(); break;
            case 14: loadFromBinary(); break;
            case 15: showBinaryInfo(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    cleanup();
    return 0;
}


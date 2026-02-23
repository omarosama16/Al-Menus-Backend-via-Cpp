
#include <iostream>
#include <iomanip>
#include <string>
#include "deliverydriver.h"
using namespace std;

deliverydriver::deliverydriver()
    : user(), VechileType("NO VEHCILE YET"), completedDelivery(0), TotalEarning(0.0) {}


deliverydriver::deliverydriver(const string& id, const string& name, const string& phone,
                               const string& vehicle, double earnings, int deliveries)
    : user(id, name, phone), VechileType(vehicle), completedDelivery(deliveries), TotalEarning(earnings) {}

void deliverydriver::displayInfo() const {
    cout << "\n=== Delivery Driver Information ===" << endl;
    cout << "User ID: " << getUserId() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Phone: " << getPhoneNumber() << endl;

    cout << "Vehicle Type: " << VechileType << endl;
    cout << "Completed Deliveries: " << completedDelivery << endl;
    cout << fixed << setprecision(2);
    cout << "Total Earnings: " << TotalEarning << " EGP" << endl;

    if (completedDelivery > 0) {
        double averageEarnings = TotalEarning / completedDelivery;
        cout << "Average Earnings per Delivery: " << averageEarnings << " EGP" << endl;
    } else {
        cout << "Average Earnings per Delivery: no deliveries completed" << endl;
    }
    cout << "===================================" << endl;
    }


   double deliverydriver::calculateEarnings() const {
    return TotalEarning; 
}

void deliverydriver::completeDelivery(double orderValue) {
    if (orderValue > 0) {
        TotalEarning += orderValue * 0.15; 
    }
}

// operators overloading7
//prefix
deliverydriver& deliverydriver::operator++() {
    completedDelivery++; 
    return *this;
}
//postfix
deliverydriver deliverydriver::operator++(int) {
    deliverydriver temp = *this;
    completedDelivery++; 
    return temp;
}

//geters
string deliverydriver::getVehicleType() const {
    return VechileType; 
}

int deliverydriver::getCompletedDeliveries() const {
    return completedDelivery; 
}

double deliverydriver::getTotalEarnings() const {
    return TotalEarning; 
}
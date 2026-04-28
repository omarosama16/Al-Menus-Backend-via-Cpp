
#include <iostream>
#include <iomanip>
#include <string>
#include "customer.h"

using namespace std;

customer::customer() : user("", "", ""), deliveryAddress("No Delivery Address"), LoyaltyPoints(0) {
}

customer::customer(const string& id, const string& name, const string& phone,
            const string& address, int points)
    : user(id, name, phone), deliveryAddress(address), LoyaltyPoints(points) {
}

void customer::displayInfo() const {
    cout << endl << "=== Customer Information ===" << endl;
    cout << "user ID: " << getUserId() << endl;
    cout << "name: " << getName() << endl;
    cout << "phone: " << getPhoneNumber() << endl;
    cout << "Delivery Address: " << deliveryAddress << endl;
    cout << "Loyalty Points: " << LoyaltyPoints << endl;
    cout << fixed << setprecision(2);
    cout << "Calculated Value (Points * 0.5): " << calculateEarnings() << " EGP" << endl;
    cout << "=============================" << endl;
}

double customer::calculateEarnings() const {
    return LoyaltyPoints * 0.5;
}

int customer::getLoyaltyPoints() const {
    return LoyaltyPoints;
}

const string& customer::getDeliveryAddress() const {
    return deliveryAddress;
}

void customer::setDeliveryAddress(const string& address) {
    deliveryAddress = address;
}
//busniess rule
void customer::setLoyaltyPoints(int points) {
    LoyaltyPoints = (points >= 0) ? points : 0;
}

customer& customer::operator+=(int pointsToAdd) {
    if (pointsToAdd > 0) {
        LoyaltyPoints += pointsToAdd;
    }
    return *this;
}

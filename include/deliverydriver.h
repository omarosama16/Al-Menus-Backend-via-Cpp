
#ifndef DELIVERYDRIVER_H
#define DELIVERYDRIVER_H
#include <string>
#include "user.h"
using namespace std;

class deliverydriver : public user{
private:
string VechileType ;
int completedDelivery ;
double TotalEarning ;

public :

deliverydriver();

deliverydriver(const string& id, const string& name, const string& phone,
                   const string& vehicle, double earnings = 0.0, int deliveries = 0);

void displayInfo() const override;

double calculateEarnings() const override;

void completeDelivery(double orderValue);

//prefix
deliverydriver& operator++();


//postfixx

deliverydriver operator++(int);

string getVehicleType() const;
int getCompletedDeliveries() const;
double getTotalEarnings() const;

};

#endif 

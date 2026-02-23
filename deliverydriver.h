
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
/*

we used (int) here as a dummy parameter 
it doesnt interfere in the code 
we dont use it as a parameter 
but it just gives a signal to the compiler that this one is the post fix operator 

*/
deliverydriver operator++(int);

string getVehicleType() const;
int getCompletedDeliveries() const;
double getTotalEarnings() const;

};

#endif 



#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include "user.h"
using namespace std;

class customer : public user
{
private:
    string deliveryAddress;
    int LoyaltyPoints;

public:
    customer();  
    
    customer(const string& id, const string& name, const string& phone,
             const string& address, int points = 0); 
    //--------------------------------
    void displayInfo() const override;
    double calculateEarnings() const override;
    //------------------------------------------
    const string& getDeliveryAddress() const;
    int getLoyaltyPoints() const;
    //-----------------------------------------
    void setLoyaltyPoints(int points);
    void setDeliveryAddress(const string& address);
 //----------------------------------------------
    customer& operator+=(int pointsToAdd);
};


#endif 

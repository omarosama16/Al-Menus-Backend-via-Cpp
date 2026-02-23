
#ifndef USER_H
#define USER_H

#include <string>

using namespace std;


class user
{
protected:
    string UserID;
    string Name;
    string PhoneNumber;
    static int TotalUsers;

public:
    user();  
    
    user(string uID, string n, string pn);  
    
    virtual void displayInfo() const = 0; 
    
    virtual double calculateEarnings() const = 0;

    static int getTotalUsers();

    string getUserId() const;
    string getName() const;
    string getPhoneNumber() const;

    virtual ~user();
};

#endif
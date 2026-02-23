
#include <iostream>
#include <string>
#include "user.h"
using namespace std;

int user::TotalUsers = 0;
user::user() {
    UserID = "";
    Name = "";
    PhoneNumber = "";
    TotalUsers++;
}

user::user(string uID, string n, string pn) {
    UserID = uID;
    Name = n;
    PhoneNumber = pn;
    TotalUsers++;
}

int user::getTotalUsers() {
    return TotalUsers;
}

string user::getUserId() const {
    return UserID;
}

string user::getName() const {
    return Name;
}

string user::getPhoneNumber() const {
    return PhoneNumber;
}

user::~user() {
    TotalUsers--;  
}
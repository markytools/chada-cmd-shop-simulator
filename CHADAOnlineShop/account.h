#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "datahandler.h"
#include <iostream>
#include "selleraccount.h"
using namespace std;

const string passcode = "123sasad3SAD!!#!!sad$#";

struct Address {
    string address1;
    string address2;
    string townOrCity;
    string region;
};

class Account
{
    string code;

    string accountID;
    string accountName;     //username
    string email;
    string password;
    string firstName;
    char middleInitial;
    string lastName;
    string contactNo;
    Address shippingAddress;

public:
    void flushAccount();
    Account *flushAndReturnAcct();
    void setFields(string accountID, string accountName, string email, string password, string firstName, char middleInitial,
                   string lastName, string contactNo, Address shippingAddress);
    void permitFieldSettings(string code);
    void signUp();
    Account();

    string getAccountID() const;
    string getAccountName() const;
    string getEmail() const;
    string getPassword() const;
    string getFirstName() const;
    char getMiddleInitial() const;
    string getLastName() const;
    string getContactNo() const;
    Address getShippingAddress() const;
};

#endif // ACCOUNT_H

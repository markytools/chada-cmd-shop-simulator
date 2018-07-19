#ifndef SELLERACCOUNT_H
#define SELLERACCOUNT_H

#include <vector>
#include <iostream>
#include "account.h"
using namespace std;

struct Address;

class SellerAccount
{
    string sellerName;
    float score;
    string accountID;
    string sellerID;
    string cardNum;
    string expiryDate;
    string cvc;
    vector<string> itemIDList;
    float balance;
    Address *billingAddress;

public:

    void flushSellerAccount();

    SellerAccount();

    string getSellerName() const;
    void setSellerName(const string &value);
    string getSellerID() const;
    void setSellerID(const string &value);
    string getCardNum() const;
    void setCardNum(const string &value);
    string getExpiryDate() const;
    void setExpiryDate(const string &value);
    string getCvc() const;
    void setCvc(const string &value);
    vector<string> getItemIDList() const;
    void setItemIDList(const vector<string> &value);
    float getBalance() const;
    void setBalance(float value);
    Address *getBillingAddress() const;
    void setBillingAddress(Address *value);
    string getAccountID() const;
    void setAccountID(const string &value);
    float getScore() const;
    void setScore(float value);
};

#endif // SELLERACCOUNT_H

#ifndef SELLERDATAHANDLER_H
#define SELLERDATAHANDLER_H

#include <vector>
#include <iostream>
#include "selleraccount.h"
using namespace std;

class SellerAccount;

class SellerDataHandler
{
public:
    SellerAccount getSellerInfo(string accountID);
    string generateNewSellerID();
    bool checkIfSellerNameExists(string sellerName);
    vector<SellerAccount> getListOfSellerAccounts();
    SellerDataHandler();
};

#endif // SELLERDATAHANDLER_H

#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "account.h"
#include "chadaonlineshopdisplay.h"
#include "itemdatahandler.h"
#include <iostream>
#include "sellerdatahandler.h"
using namespace std;

class Account;
class ItemDataHandler;
class SellerDataHandler;

class DataHandler
{
    ItemDataHandler *itemDataHandler;
    SellerDataHandler *sellerDataHandler;

    Account *loadedAcct;
    void getSingleAcctInfo(Account* &account, ifstream &infile);
public:
    static const string CHADA_DATABASE;

    void setLoadedAcct(string email);
    bool checkIfAccountIDExists(string accountID);
    bool checkIfUsernameExists(string username);
    bool checkIfEmailExists(string email);
    DataHandler();

    Account *getLoadedAcct() const;
    void setLoadedAcct(Account *loadedAcct);
    ItemDataHandler *getItemDataHandler() const;
    SellerDataHandler *getSellerDataHandler() const;
};

#endif // DATAHANDLER_H

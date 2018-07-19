#ifndef SELLERSCREEN_H
#define SELLERSCREEN_H

#include "screen.h"
#include "selleraccount.h"
#include "datahandler.h"

struct SellerItemInfo {
    string itemName;
    string itemID;
    int numOfSales;
    float totalSales;
};

class SellerAccount;
class SellerScreen : public Screen
{
    DataHandler *dataHandler;
    SellerAccount *loadedSellerAccount;
    SystemManager *sysManager;
    vector<SellerItemInfo> sellerItemInfos;

    void setItemInfos();
    void flushItemInfos();
    void addItemToShop();
public:
    bool checkAndCreateSellerAccount(string accountID);
    void displayScreen();
    SellerScreen();
    SellerScreen(DataHandler *dataHandler, SystemManager *sysManager);
    void setLoadedSellerAccount(SellerAccount *value);
};

#endif // SELLERSCREEN_H

#ifndef SHOPSCREEN_H
#define SHOPSCREEN_H

#include "systemmanager.h"
#include "datahandler.h"
#include "admin.h"
#include <vector>
using namespace std;

class DataHandler;
class Item;
class Reviews;
class Admin;

enum ShopScreenState {
    HOME, SHOP, TOP_DEALS, MY_CART, SELLER_ACCOUNT, ACCOUNT_SETTINGS, LOG_OUT
};

enum SHOP_STATE {
    SEARCH_SELECTION, ITEM_SELECTION, ITEM_PREVIEW
};

class ShopScreen : public Screen
{
    bool displayItems;
    SHOP_STATE shopState;
    ShopScreenState shopScreenState;
    vector<Item> matchedItems;

    Item *previewedItem;
    DataHandler *dataHandler;
    SystemManager *sysManager;
    Admin *admin;

    float calculateRating(vector<Reviews> reviewList);
public:
    void displayScreen();

    ShopScreen();
    ShopScreen(DataHandler *dataHandler, SystemManager *sysManager);
    void setShopScreenState(const ShopScreenState &value);
};

#endif // SHOPSCREEN_H

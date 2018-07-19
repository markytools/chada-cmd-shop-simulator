#ifndef ITEMDATAHANDLER_H
#define ITEMDATAHANDLER_H

#include "item.h"
#include "iteminfo.h"
#include <vector>
#include "datahandler.h"
#include "cart.h"

class DataHandler;
class Cart;
class ItemDataHandler
{
    DataHandler *dataHandler;
    ItemInfo itemInfo;
    Cart *cart;
public:
    string generateNewItemID();
    bool checkIfItemNameExists(string itemName);
    Item getItemInfo(string itemID);
    vector<Item> getAllItems();
    ItemDataHandler();
    ItemInfo getItemInfo() const;
    DataHandler *getDataHandler() const;
    void setDataHandler(DataHandler *value);
    Cart *getCart() const;
};

#endif // ITEMDATAHANDLER_H

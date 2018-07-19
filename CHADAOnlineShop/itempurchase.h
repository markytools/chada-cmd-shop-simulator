#ifndef ITEMPURCHASE_H
#define ITEMPURCHASE_H

#include "item.h"
#include "datahandler.h"

class ItemPurchase
{
    Item *itemToPurchase;
    DataHandler *dataHandler;
public:
    ItemPurchase();
    ItemPurchase(DataHandler *dataHandler);
    void setItemToPurchase(Item *value);
    bool purchaseItem();
};

#endif // ITEMPURCHASE_H

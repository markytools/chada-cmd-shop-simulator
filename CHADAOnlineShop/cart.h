#ifndef CART_H
#define CART_H

#include "vector"
#include "itemdatahandler.h"
#include <iostream>
using namespace std;

struct ItemInCart {
    string itemID;
    int stocksLeft;
    float price;
};

class ItemDataHandler;

class Cart
{
    ItemDataHandler *itemDataHandler;
    vector<ItemInCart> itemsInCart;
    string accountID;

    Item getItemInfo(string itemID);
    void flushItemsInCart();
    bool checkCartHasItem(string itemID);
public:
    void displaySize();
    void displayCart();
    void updateCart();
    void setCart(string accountID);
    void addItemToCart(Item *itemID);
    void resetCartData();

    Cart();
    Cart(ItemDataHandler *itemDataHandler);
    vector<ItemInCart> getItemsInCart() const;
};

#endif // CART_H

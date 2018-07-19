#include "cart.h"
#include "datahandler.h"
#include <string>
#include <fstream>
#include "utils.h"
#include <iomanip>
#include "selections.h"
#include "itempurchase.h"
#include "mastercard.h"

vector<ItemInCart> Cart::getItemsInCart() const
{
    return itemsInCart;
}

//Should be ITEMxXXXXXXX
Item Cart::getItemInfo(string itemID)
{
    Item itemToReturn;
    vector<Item> itemList = itemDataHandler->getAllItems();
    for (Item item : itemList){
        if (item.getItemID() == itemID){
            itemToReturn = item;
            break;
        }
    }
    return itemToReturn;
}

void Cart::addItemToCart(Item *itemID)
{
    bool cont = true;
    for (ItemInCart itemCart : itemsInCart){
        if (itemCart.itemID == itemID->getItemID()){
            cont = false;
            break;
        }
    }
    if (cont){
        ItemInCart itemInCart;
        itemInCart.itemID = itemID->getItemID();
        itemInCart.price = itemID->getDiscountedPrice();
        itemInCart.stocksLeft = itemID->getStocks();
        itemsInCart.push_back(itemInCart);
        updateCart();
        cout << "Item Successfully Added." << endl << endl;
    }
    else cout << "Unable to add, item already in cart." << endl << endl;
}

void Cart::resetCartData()
{
    accountID = "";
    itemsInCart.clear();
}

void Cart::updateCart()
{
    vector<ItemInCart> finalItemsInCart;
    for (ItemInCart itemInCart : itemsInCart){
        Item item = getItemInfo(itemInCart.itemID);
        if (!(item.getItemName() == "" || item.getStocks() == 0)){
            itemInCart.price = item.getDiscountedPrice();
            itemInCart.stocksLeft = item.getStocks();
            finalItemsInCart.push_back(itemInCart);
        }
    }
    itemsInCart = finalItemsInCart;
    flushItemsInCart();
}

void Cart::flushItemsInCart()
{
    string cartDirec = DataHandler::CHADA_DATABASE + "cart/CART" + accountID + ".cart";
    ofstream outfile;
    outfile.open(cartDirec.data(), ios:: out);
    if (outfile.is_open()){
        for (ItemInCart itemInCart : itemsInCart){
            outfile << "Item ID:" << itemInCart.itemID << endl;
            outfile << "Stocks Left:" << itemInCart.stocksLeft << endl;
            outfile << "Price:" << itemInCart.price << endl;
            outfile << endl;
        }
    }
    else {
        cerr << "Error creating cart file." << endl;
        exit(1);
    }
    outfile.close();
}

void Cart::displaySize()
{
    cout << itemsInCart.size() << endl;
}

void Cart::displayCart()
{
    updateCart();
    clearScreen();
    int cartDisplayState = 0;
    Item *itemToPreview;
    while (cartDisplayState != -1){
        switch (cartDisplayState){
        case 0: {
            cout << left
                 << setw(15) << "ITEM NO."
                 << setw(40) << "ITEM NAME"
                 << setw(30) << "PRICE(PHP)"
                 << setw(20) << "STOCKS" << endl;
            for (int i = 0; i < itemsInCart.size(); i++){
                ItemInCart itemInCart = itemsInCart[i];
                Item item = getItemInfo(itemInCart.itemID);
                cout << left
                     << setw(15) << numberToString(i + 1, 0)
                     << setw(40) << limitStringSize(item.getItemName(), 35)
                     << setw(30) << item.getDiscountedPrice()
                     << setw(20) << item.getStocks() << endl;
            }
            cout << endl;

            if (itemsInCart.size() == 0){
                cout << "There are no items in your cart." << endl << endl;
                Selections selections;
                selections.setSInputType(NUMBERS);
                selections.putNumChoice("Back");
                selections.displaySelections();
                string selection = selections.select("------>>>>");
                cartDisplayState = -1;
            }
            else {
                Selections selections;
                selections.setSInputType(BOTH);
                selections.numListTitle = "Type Item No. to Preview it";
                for (int i = 0; i < itemsInCart.size(); i++){
                    selections.putNumChoice("Item " + numberToString(i, 0));
                }
                selections.putLetterChoiceA("Buy All Items");
                selections.putLetterChoiceA("Remove Item from Cart");
                selections.putLetterChoiceA("Back");
                selections.displaySelections(false);
                string selection = selections.select("------>>>>");
                if (selection == "A"){
                    clearScreen();

                    vector<Item> itemInfoInCart;
                    for (ItemInCart itemInCart : itemsInCart) itemInfoInCart.push_back(getItemInfo(itemInCart.itemID));
                    int amounts[itemInfoInCart.size()];

                    Selections selections;
                    string selection;
                    for (int i = 0; i < itemInfoInCart.size(); i++){
                        Item item = getItemInfo(((Item)(itemInfoInCart[i])).getItemID());
                        int stocksLeft = item.getStocks();
                        int min, max;
                        amounts[i] = 1;
                        max = (stocksLeft >= 50) ? 50 : stocksLeft;
                        min = 1;

                        cout << "Item Name: " << item.getItemName() << endl;
                        if (max != 1){
                            cout << "How many of this item would you like to purchase (1 to " << max << ")?" << endl;
                            do {
                               cout << "Quantity: ";
                               cin >> amounts[i];
                               if (amounts[i] >= min && amounts[i] <= max) break;
                            } while (1);
                        }
                    }

                    clearScreen();
                    cout << "---Prices---" << endl;
                    float totalPrice = 0;
                    for (int i = 0; i < itemInfoInCart.size(); i++){
                        Item item = getItemInfo(((Item)(itemInfoInCart[i])).getItemID());
                        cout << "Item Name: " << item.getItemName() << endl;
                        cout << "Postage: " << item.getPostage() << endl;
                        cout << "Quantity: " << amounts[i] << endl;
                        cout << "Price per unit: " << item.getDiscountedPrice() << endl;
                        totalPrice += (float)(amounts[i]) * item.getDiscountedPrice();
                        cout << fixed << setprecision(2) << "Total Price for this Item: P " << amounts[i] * item.getDiscountedPrice() << endl;
                        cout << endl;
                    }
                    cout << "Total Price: P " << totalPrice << endl;

                    cout << "Select yes to commit to buying the items: " << endl;
                    selections.setSInputType(NUMBERS);
                    selections.putNumChoice("Yes");
                    selections.putNumChoice("No");
                    selections.displaySelections();
                    selection = selections.select("--->> ");
                    if (selection == "1"){
                        clearScreen();
                        cout << "YOU WILL NOW BE PURCHASING YOUR CHADA ITEM" << endl;
                        for (int i = 0; i < itemInfoInCart.size(); i++){
                            Item item = getItemInfo(((Item)(itemInfoInCart[i])).getItemID());
                            cout << "Item Name: " << item.getItemName() << endl;
                        }
                        cout << "Total Price: P " << totalPrice << endl << endl;
                        cout << "Shipping Address: " << endl;
                        Account *loadedAccount = itemDataHandler->getDataHandler()->getLoadedAcct();
                        cout << loadedAccount->getShippingAddress().address1 << endl;
                        cout << loadedAccount->getShippingAddress().address2 << endl;
                        cout << loadedAccount->getShippingAddress().townOrCity << endl;
                        cout << loadedAccount->getShippingAddress().region << ", Philippines" << endl << endl;
                        cout << "Accepted Payment Cards: MASTERCARD, VISA, AMERICAN EXPRESS" << endl;
                        Mastercard mCard;
                        bool cardConfirmed = false;
                        while (!cardConfirmed){
                            cardConfirmed = mCard.setCurrentMastercard();
                            if (!cardConfirmed) cout << "Invalid Card Information!" << endl;
                        }
                        renderLoadingAnimTxt();
                        clearScreen();
                        bool success = mCard.subtractFromCard(totalPrice);
                        if (success){
                            for (int i = 0; i < itemInfoInCart.size(); i++){
                                Item *item = new Item(getItemInfo(((Item)(itemInfoInCart[i])).getItemID()));
                                item->setStocks(item->getStocks() - amounts[i]);
                                if (item->getStocks() == 0){
                                    Category category = item->getCategory();
                                    category.status = OUT_OF_STOCK_STATUS;
                                    item->setCategory(category);
                                }
                                ItemInfo itemInfo = itemDataHandler->getDataHandler()->getItemDataHandler()->getItemInfo();
                                itemInfo.flushItemInfo(item, itemInfo.getDefaultImages(item->getItemID()));
                            }
                            cout << "THANK YOU FOR SHOPPING AT CHADA" << endl;
                            updateCart();
                        }
                        selections.clearSelections();
                        selections.putNumChoice("Back");
                        selections.displaySelections();
                        selection = selections.select("--->> ");
                    }
                    clearScreen();
                }
                else if (selection == "B"){
                    Selections removeSelection;
                    vector<ItemInCart> finalItems;
                    removeSelection.setSInputType(NUMBERS);
                    for (int i = 0; i < itemsInCart.size(); i++){
                        removeSelection.putNumChoice("Item " + numberToString(i, 0));
                    }
                    string selection = removeSelection.select("Type the number of the item you want to remove: ");
                    int itemNum = stoi(selection);
                    for (int i = 0; i < itemsInCart.size(); i++){
                        if (itemNum - 1 != i){
                            finalItems.push_back(itemsInCart[i]);
                        }
                    }
                    itemsInCart = finalItems;
                    updateCart();
                    clearScreen();
                }
                else if (selection == "C"){
                    cartDisplayState = -1;
                }
                else {
                    ItemInCart itemInCart = itemsInCart[stoi(selection) - 1];
                    itemToPreview = new Item(getItemInfo(itemInCart.itemID));
                    cartDisplayState = 1;
                }
            }
        }; break;
        case 1: {
            cout << "\t\t\t\tITEM PREVIEW" << endl << endl;
            cout << "Item Name: " << itemToPreview->getItemName() << endl;
            cout << "Item condition: " << itemToPreview->getItemCondition() << endl;
            cout << "Original Price: P " << itemToPreview->getOriginalPrice() << endl;
            cout << "Real Price: P " << itemToPreview->getDiscountedPrice() << endl << endl;
            cout << "Item Description: " << itemToPreview->getItemDescription() << endl << endl;
            cout << "Postage: " << itemToPreview->getPostage() << endl;
            cout << "Item Location: " << itemToPreview->getItemLocation() << endl;
            cout << "Returns: " << itemToPreview->getReturns() << endl;

            string rating;
            string stars = (itemToPreview->getRating() > 1) ? "Stars" : "Star";
            if (numberToString(itemToPreview->getRating(), 0) != "nan") rating = "No rating";
            else rating = numberToString(itemToPreview->getRating(), 0) + " " + stars;
            cout << "Rating: " << rating << endl;

            string stocks = (itemToPreview->getStocks() > 10) ? "More than 10 available" : stocks + " left";
            cout << "Stocks: " << stocks << endl << endl;

            string seller = "<<--Item Sold by: ";
            if (itemToPreview->getCategory().status == "TEST ITEM"){
                seller += itemToPreview->getTestItemInfo().username;
            }
            cout << seller << endl;
            cout << endl;

            Selections itemPreviewSelections;
            itemPreviewSelections.setSInputType(NUMBERS);
            itemPreviewSelections.putNumChoice("Buy Item");
            itemPreviewSelections.putNumChoice("Back");
            itemPreviewSelections.displaySelections();
            string itemPreviewSelection = itemPreviewSelections.select("------>>>> ");

            if (itemPreviewSelection == "1"){
                ItemPurchase itemPurchase(itemDataHandler->getDataHandler());
                itemPurchase.setItemToPurchase(itemToPreview);
                bool success = itemPurchase.purchaseItem();
                if (success){
                    cout << "THANK YOU FOR SHOPPING AT CHADA" << endl;
                }
                Selections selections;
                selections.clearSelections();
                selections.putNumChoice("Back to Cart");
                selections.displaySelections();
                string selection = selections.select("--->>");
            }
            clearScreen();
            cartDisplayState = 0;
        }; break;
        default: break;
        }
    }

    clearScreen();
}

bool Cart::checkCartHasItem(string itemID)
{
    for (ItemInCart itemInCart : itemsInCart){
        if (itemInCart.itemID == itemID) return true;
    }
    return false;
}

void Cart::setCart(string accountID)
{
    this->accountID = accountID;
    string cartDirec = DataHandler::CHADA_DATABASE + "cart/CART" + accountID + ".cart";
    createFileIfNotExist(cartDirec);
    ifstream infile;
    infile.open(cartDirec.data(), ios::in);
    if (infile.is_open()){
        while (!infile.eof()){
            string itemID;
            getline(infile >> ws, itemID);
            removeSubstring(itemID, "Item ID:");
            if (itemID.empty()) break;

            int stocks;
            string temp;
            getline(infile >> ws, temp);
            removeSubstring(temp, "Stocks Left:");
            stocks = stoi(temp);

            float price;
            getline(infile >> ws, temp);
            removeSubstring(temp, "Price:");
            price = stof(temp);

            if (!checkCartHasItem(itemID)){
                ItemInCart itemInCart;
                itemInCart.itemID = itemID;
                itemInCart.price = price;
                itemInCart.stocksLeft = stocks;
                itemsInCart.push_back(itemInCart);
            }
        }
    }
    else {
        cerr << "Error reading file." << endl;
        exit(1);
    }
    infile.close();
}

Cart::Cart()
{

}

Cart::Cart(ItemDataHandler *itemDataHandler)
{
    this->itemDataHandler = itemDataHandler;
}


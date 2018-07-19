#include "itempurchase.h"
#include "selections.h"
#include <iomanip>
#include "utils.h"
#include "account.h"
#include "mastercard.h"

ItemPurchase::ItemPurchase(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
}

void ItemPurchase::setItemToPurchase(Item *value)
{
    itemToPurchase = value;
}

bool ItemPurchase::purchaseItem()
{
    clearScreen();
    Selections selections;
    string selection;
    cout << "Item Name: " << itemToPurchase->getItemName() << endl;
    cout << "Would you like to purchase this item? " << endl;
    selections.setSInputType(NUMBERS);
    selections.putNumChoice("Yes");
    selections.putNumChoice("No");
    selections.displaySelections();
    selection = selections.select("--->> ");
    if (selection == "2") return false;
    selections.clearSelections();

    int stocksLeft = itemToPurchase->getStocks();
    int min, max, amount = 1;
    float amountPayable;
    max = (stocksLeft >= 50) ? 50 : stocksLeft;
    min = 1;

    if (max != 1){
        cout << "How many of this item would you like to purchase (1 to " << max << ")? " << endl;
        do {
            cout << "Quantity: ";
            cin >> amount;
            if (amount >= min && amount <= max) break;
            cout << "Invalid amount." << endl;
        } while (1);
    }

    amountPayable = amount * itemToPurchase->getDiscountedPrice();
    cout << fixed << setprecision(2);
    cout << "Your total purchase is Php " << amountPayable << " (X" << amount << "). Select yes to commit to buying the item: " << endl;
    selections.setSInputType(NUMBERS);
    selections.putNumChoice("Yes");
    selections.putNumChoice("No");
    selections.displaySelections();
    selection = selections.select("--->> ");
    if (selection == "2") return false;
    selections.clearSelections();

    clearScreen();
    cout << endl << endl;
    cout << "YOU WILL NOW BE PURCHASING YOUR CHADA ITEM" << endl;
    cout << "Item Name: " << itemToPurchase->getItemName() << endl;
    cout << "Postage: " << itemToPurchase->getPostage() << endl;
    cout << "Quantity: " << amount << endl;
    cout << "Total Price: " << amountPayable << endl << endl;
    cout << "Shipping Address: " << endl;
    Account *loadedAccount = dataHandler->getLoadedAcct();
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
    bool success = mCard.subtractFromCard(amountPayable);
    if (success){
        itemToPurchase->setStocks(itemToPurchase->getStocks() - amount);
        if (itemToPurchase->getStocks() == 0){
            Category category = itemToPurchase->getCategory();
            category.status = OUT_OF_STOCK_STATUS;
            itemToPurchase->setCategory(category);
        }
        ItemInfo itemInfo = dataHandler->getItemDataHandler()->getItemInfo();
        itemInfo.flushItemInfo(itemToPurchase, itemInfo.getDefaultImages(itemToPurchase->getItemID()));
    }
    return success;
}

ItemPurchase::ItemPurchase()
{

}


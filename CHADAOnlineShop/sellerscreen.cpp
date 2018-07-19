#include "sellerscreen.h"
#include "selleraccount.h"
#include "selections.h"
#include "windows.h"
#include "utils.h"
#include "mastercard.h"
#include <iomanip>
#include <algorithm>

void SellerScreen::setLoadedSellerAccount(SellerAccount *value)
{
    loadedSellerAccount = value;
}

void SellerScreen::setItemInfos()
{
    sellerItemInfos.clear();
    for (string itemID : loadedSellerAccount->getItemIDList()){
        string finalID = itemID.substr(4, 17);
        string direc = DataHandler::CHADA_DATABASE + "system/INFO" + finalID + ".info";
        ifstream infile;
        infile.open(direc.data(), ios::in);
        if (infile.is_open()){
            SellerItemInfo sellerItemInfo;

            getline(infile >> ws, sellerItemInfo.itemName);
            removeSubstring(sellerItemInfo.itemName, "Item Name:");
            getline(infile >> ws, sellerItemInfo.itemID);
            removeSubstring(sellerItemInfo.itemID, "Item ID:");

            string temp;
            getline(infile >> ws, temp);
            removeSubstring(temp, "Number of Sales:");
            sellerItemInfo.numOfSales = stoi(temp);

            getline(infile >> ws, temp);
            removeSubstring(temp, "Total Sales:");
            sellerItemInfo.totalSales = stof(temp);

            sellerItemInfos.push_back(sellerItemInfo);
        }
        else {
            cerr << "Error opening item info file." << endl;
            exit(1);
        }
        infile.close();
    }
}

void SellerScreen::flushItemInfos()
{
    for (SellerItemInfo itemInfo : sellerItemInfos){
        string finalID = itemInfo.itemID.substr(4, 17);
        string directory = DataHandler::CHADA_DATABASE + "system/INFO" + finalID + ".info";
        ofstream outfile;
        outfile.open(directory.data(), ios::app);
        if (outfile.is_open()){
            outfile << "Item Name:" << itemInfo.itemName << endl;
            outfile << "Item ID:" << itemInfo.itemID << endl;
            outfile << "Number of Sales:" << itemInfo.numOfSales << endl;
            outfile << "Total Sales:" << itemInfo.totalSales << endl;
        }
        else {
            cerr << "Error opening item info files." << endl;
            exit(1);
        }
        outfile.close();
    }
}

void SellerScreen::addItemToShop()
{
    Item item;

    string itemName = "";
    string itemCondition;
    float originalPrice;
    float discountedPrice;
    string postage;
    string itemLocation;
    string returns;
    string itemDescription;
    string itemID;
    string sellerID;
    float rating;
    int stocks;

    Category category;
    cout << "---SELL AN ITEM---" << endl;
    cout << "Please enter the following item informations..." << endl;
    do {
        cout << "Item Name: ";
        getline(cin >> ws, itemName);
        if (!dataHandler->getItemDataHandler()->checkIfItemNameExists(itemName)) break;
        cout << "That item name has already been taken." << endl;
    } while (1);
    cout << "Item Condition: ";
    getline(cin >> ws, itemCondition);

    string temp;
    cout << "Original Price: ";
    getline(cin >> ws, temp);
    originalPrice = stof(temp);

    do {
        cout << "Discounted Price: ";
        getline(cin >> ws, temp);
        discountedPrice = stof(temp);
        if (discountedPrice <= originalPrice) break;
        cout << "Discounted Price Should be Smaller or Equal to Original Price." << endl;
    } while (1);

    Selections selections;
    selections.setSInputType(NUMBERS);
    selections.putNumChoice("PICK UP (Delivery Time Varies)");
    selections.putNumChoice("LBC (3-5 Days)");
    selections.putNumChoice("2-GO (5-10 Days)");
    selections.putNumChoice("PHILPOST (10-20 Days)");
    selections.displaySelections();
    string selection = selections.select("Select Postage for Item Delivery: ");
    int numSelection = stoi(selection);
    switch (numSelection){
    case 1: postage = "PICK UP (Delivery Time Varies)"; break;
    case 2: postage = "LBC (3-5 Days)"; break;
    case 3: postage = "2-GO (5-10 Days)"; break;
    case 4: postage = "PHILPOST (10-20 Days)"; break;
    default: break;
    }

    cout << "Item Location: ";
    getline(cin >> ws, itemLocation);
    cout << "Are there any returns for your item?" << endl;
    selections.clearSelections();
    selections.putNumChoice("Yes");
    selections.putNumChoice("No");
    selections.displaySelections();
    selection = selections.select("--->> ");
    if (selection == "2") returns = "No Returns";
    else {
        int returnDays;
        cout << "Specify the max day of return: ";
        cin >> returnDays;
        string day = (returnDays == 1) ? "Day" : "Days";
        returns = numberToString(returnDays, 0) + " " + day + " Return";
    }

    cout << "Item Description: ";
    getline(cin >> ws, itemDescription);
    itemID = dataHandler->getItemDataHandler()->generateNewItemID();
    sellerID = loadedSellerAccount->getSellerID();
    rating = stof("NaN");
    cout << "Stocks: ";
    cin >> stocks;

    string selection1 = "Antique";
    string selection2 = "Art";
    string selection3 = "Baby";
    string selection4 = "Books";
    string selection5 = "Business";
    string selection6 = "Camera";
    string selection7 = "Computer";
    string selection8 = "Electronics";
    string selection9 = "Movies";
    string selection10 = "Health";
    string selection11 = "Jewelry";
    string selection12 = "Mobile";
    string selection13 = "Music";
    string selection14 = "Instruments";
    string selection15 = "Pottery";
    string selection16 = "Sports";
    string selection17 = "Toys";
    string selection18 = "Vehicles";

    Selections categorySelections;
    categorySelections.setSInputType(NUMBERS);
    categorySelections.numListTitle = "---Main Categories---";
    categorySelections.putNumChoice(selection1);
    categorySelections.putNumChoice(selection2);
    categorySelections.putNumChoice(selection3);
    categorySelections.putNumChoice(selection4);
    categorySelections.putNumChoice(selection5);
    categorySelections.putNumChoice(selection6);
    categorySelections.putNumChoice(selection7);
    categorySelections.putNumChoice(selection8);
    categorySelections.putNumChoice(selection9);
    categorySelections.putNumChoice(selection10);
    categorySelections.putNumChoice(selection11);
    categorySelections.putNumChoice(selection12);
    categorySelections.putNumChoice(selection13);
    categorySelections.putNumChoice(selection14);
    categorySelections.putNumChoice(selection15);
    categorySelections.putNumChoice(selection16);
    categorySelections.putNumChoice(selection17);
    categorySelections.putNumChoice(selection18);
    categorySelections.displaySelections();
    string mCategory = categorySelections.select("Select Item Main Category: ");
    int num = stoi(mCategory);

    switch (num){
    case 1 : category.mainCategory = selection1; break;
    case 2 : category.mainCategory = selection2; break;
    case 3 : category.mainCategory = selection3; break;
    case 4 : category.mainCategory = selection4; break;
    case 5 : category.mainCategory = selection5; break;
    case 6 : category.mainCategory = selection6; break;
    case 7 : category.mainCategory = selection7; break;
    case 8 : category.mainCategory = selection8; break;
    case 9 : category.mainCategory = selection9; break;
    case 10 : category.mainCategory = selection10; break;
    case 11 : category.mainCategory = selection11; break;
    case 12 : category.mainCategory = selection12; break;
    case 13 : category.mainCategory = selection13; break;
    case 14 : category.mainCategory = selection14; break;
    case 15 : category.mainCategory = selection15; break;
    case 16 : category.mainCategory = selection16; break;
    case 17 : category.mainCategory = selection17; break;
    case 18 : category.mainCategory = selection18; break;
    default: break;
    }

    vector<string> subCategories;
    string subCategory;
    cout << "Enter a subcategory for the item or type -1 to stop adding..." << endl;
    do {
        cout << "Sub-Category: ";
        getline(cin >> ws, subCategory);
        if (subCategory == "-1" && subCategories.size() != 0) break;
        if (!checkIfVectorHasItem(subCategories, subCategory)) subCategories.push_back(subCategory);
    } while (1);
    category.subCategory = subCategories;
    category.noOfViews = 0;
    category.status = PENDING_STATUS;

    vector<ImageReplacementInfo> imageReplacements;
    cout << "Enter the directory of the image you want to add (the first is the main image of the item),\nor type -1 to exit (Max. 1 Image): " << endl;
    do {
        string imageDirec;
        cout << "Directory: ";
        getline(cin >> ws, imageDirec);
        replace(imageDirec.begin(), imageDirec.end(), '\\', '/');
        if (imageDirec == "-1" && imageReplacements.size() >= 1) break;
        if (fileExists(imageDirec) && (imageDirec.substr(imageDirec.length() - 4, imageDirec.length()) == ".jpg" ||
                                       imageDirec.substr(imageDirec.length() - 4, imageDirec.length()) == ".png" ||
                                       imageDirec.substr(imageDirec.length() - 4, imageDirec.length()) == ".ico")){
            ImageReplacementInfo iRInfo;
            iRInfo.imageDirec = imageDirec;
            iRInfo.code = -1;
            imageReplacements.push_back(iRInfo);
        }
        else cout << "Unable to add file or you need to add at least one image. Check spelling properly and add the file extension." << endl;
    } while (1);

    string direc1 = DataHandler::CHADA_DATABASE + "items/ITEM" + itemID;
    string direc2 = DataHandler::CHADA_DATABASE + "items/ITEM" + itemID + "/images";
    CreateDirectory(direc1.c_str(), NULL);
    CreateDirectory(direc2.c_str(), NULL);
    item.setItemName(itemName);
    item.setItemCondition(itemCondition);
    item.setOriginalPrice(originalPrice);
    item.setDiscountedPrice(discountedPrice);
    item.setPostage(postage);
    item.setItemLocation(itemLocation);
    item.setReturns(returns);
    item.setItemDescription(itemDescription);
    item.setItemID("ITEM" + itemID);
    item.setSellerID("SELLER" + sellerID);
    item.setRating(rating);
    item.setStocks(stocks);
    item.setCategory(category);

    ItemInfo mItemInfo = dataHandler->getItemDataHandler()->getItemInfo();
    mItemInfo.flushItemInfo(new Item(item), imageReplacements);

    SellerItemInfo sellerItemInfo;
    sellerItemInfo.itemID = "ITEM" + itemID;
    sellerItemInfo.itemName = itemName;
    sellerItemInfo.numOfSales = 0;
    sellerItemInfo.totalSales = 0;
    sellerItemInfos.push_back(sellerItemInfo);
    vector<string> itemIDs = loadedSellerAccount->getItemIDList();
    itemIDs.push_back(sellerItemInfo.itemID);
    loadedSellerAccount->setItemIDList(itemIDs);
    loadedSellerAccount->flushSellerAccount();
    flushItemInfos();

    clearScreen();
    cout << "---ITEM SUBMITTED---" << endl;
    cout << "Your item has been submitted and is waiting for approval. Check the item's status." << endl;

    selections.clearSelections();
    selections.putNumChoice("Back");
    selections.displaySelections();
    string back = selections.select("--->> ");
}

bool SellerScreen::checkAndCreateSellerAccount(string accountID)
{
    bool createAcct = true;
    vector<SellerAccount> sellerAccts = dataHandler->getSellerDataHandler()->getListOfSellerAccounts();
    for (SellerAccount sellerAcct : sellerAccts){
        if (accountID == sellerAcct.getAccountID()){
            createAcct = false;
            break;
        }
    }

    if (createAcct){
        clearScreen();
        cout << "You have not yet linked your account with a seller account. Do this now?" << endl;
        Selections selections;
        selections.setSInputType(NUMBERS);
        selections.putNumChoice("Yes");
        selections.putNumChoice("No");
        selections.displaySelections();
        string selection = selections.select("--->>");
        if (selection == "1"){
            string termsOfService = DataHandler::CHADA_DATABASE + "system/Terms of Service.html";
            ShellExecuteA(0, 0, termsOfService.c_str(), 0, 0 , SW_SHOW );
            cout << "Shown to you is the Terms of Service that you need to agree on: " << endl;
            selections.clearSelections();
            selections.setSInputType(NUMBERS);
            selections.putNumChoice("Yes");
            selections.putNumChoice("No");
            selections.displaySelections();
            string selection = selections.select("--->>");
            if (selection == "1"){
                string sellerName;
                float score;
                string accountID;
                string sellerID;
                string cardNum;
                string expiryDate;
                string cvc;
                vector<string> itemIDList;
                float balance;
                Address *billingAddress = new Address();

                cout << "Please enter the following information to create a seller account..." << endl;
                do {
                    cout << "Seller Name: ";
                    getline(cin >> ws, sellerName);
                    if (!dataHandler->getSellerDataHandler()->checkIfSellerNameExists(sellerName)) break;
                    cout << "Another seller has used that name." << endl;
                } while (1);
                score = 0;
                accountID = dataHandler->getLoadedAcct()->getAccountID();
                sellerID = dataHandler->getSellerDataHandler()->generateNewSellerID();

                cout << "Enter your credit card information..." << endl;
                Mastercard msCard;
                bool contCard = false;
                while (!contCard){
                    contCard = msCard.setCurrentMastercard();
                }
                cardNum = msCard.getCardNumber();
                expiryDate = msCard.getExpiryDate();
                cvc = msCard.getCVC();
                balance = 0;
                cout << "Enter your billing address information..." << endl;
                cout << "Address 1: ";
                getline(cin >> ws, billingAddress->address1);
                cout << "Address 2: ";
                getline(cin >> ws, billingAddress->address2);
                cout << "Town/City: ";
                getline(cin >> ws, billingAddress->townOrCity);
                cout << "Region: ";
                getline(cin >> ws, billingAddress->region);

                SellerAccount newSellerAcct;
                newSellerAcct.setSellerName(sellerName);
                newSellerAcct.setScore(score);
                newSellerAcct.setAccountID(accountID);
                newSellerAcct.setCardNum(cardNum);
                newSellerAcct.setExpiryDate(expiryDate);
                newSellerAcct.setSellerID("SELLER" + sellerID);
                newSellerAcct.setCvc(cvc);
                newSellerAcct.setItemIDList(itemIDList);
                newSellerAcct.setBalance(balance);
                newSellerAcct.setBillingAddress(billingAddress);
                newSellerAcct.flushSellerAccount();

                clearScreen();
                cout << "You have successfully created your seller account." << endl;
                Selections contSelections;
                contSelections.setSInputType(NUMBERS);
                contSelections.putNumChoice("Continue");
                contSelections.putNumChoice("Back");
                contSelections.displaySelections();
                string contSelection = contSelections.select("--->> ");
                if (contSelection == "1"){
                    loadedSellerAccount = new SellerAccount(newSellerAcct);
                    return true;
                }
                else return false;
            }
            else return false;
        }
        return false;
    }
    else {
        loadedSellerAccount = new SellerAccount(
                    dataHandler->getSellerDataHandler()->getSellerInfo(
                        dataHandler->getLoadedAcct()->getAccountID()));
        return true;
    }
}

void SellerScreen::displayScreen()
{
    clearScreen();
    bool continueAfterAcctCreation = checkAndCreateSellerAccount(dataHandler->getLoadedAcct()->getAccountID());
    clearScreen();
    if (continueAfterAcctCreation){
        int state = 0;
        while (state != -1){
            switch (state){
            case 0: {
                setItemInfos();
                cout << left
                     << setw(5) << "NO."
                     << setw(20) << "ITEM NAME"
                     << setw(15) << "O. PRICE(PHP)"
                     << setw(15) << "D. PRICE(PHP)"
                     << setw(10) << "STOCKS"
                     << setw(13) << "NO. OF SALES"
                     << setw(18) << "TOTAL SALES(PHP)"
                     << setw(10) << "STATUS"
                     << setw(12) << "RATINGS" << endl;

                float totalEarnings = loadedSellerAccount->getBalance();
                for (int i = 0; i < sellerItemInfos.size(); i++){
                    SellerItemInfo sellerItemInfo = sellerItemInfos[i];
                    Item item = dataHandler->getItemDataHandler()->getItemInfo(sellerItemInfo.itemID);
                    totalEarnings += sellerItemInfo.totalSales;
                    string star = (item.getRating() > 1) ? "Stars" : "Star";
                    string ratingText = (numberToString(item.getRating(), 2) != "nan") ? numberToString(item.getRating(), 2) + star : "No rating";
                    cout << left
                         << setw(5) << numberToString(i + 1, 0)
                         << setw(20) << limitStringSize(item.getItemName(), 15)
                         << setw(15) << numberToString(item.getOriginalPrice(), 2)
                         << setw(15) << numberToString(item.getDiscountedPrice(), 2)
                         << setw(10) << numberToString(item.getStocks(), 0)
                         << setw(13) << numberToString(sellerItemInfo.numOfSales, 0)
                         << setw(18) << numberToString(sellerItemInfo.totalSales, 0)
                         << setw(10) << item.getCategory().status
                         << setw(12) << ratingText << endl;
                }
                if (sellerItemInfos.size() == 0) cout << "No items." << endl << endl;

                cout << endl;
                cout << fixed << setprecision(2) << "My Total Earnings: P " << totalEarnings << endl;
                cout << endl;

                Selections selections;
                selections.setSInputType(BOTH);
                selections.putNumChoice("Sell New Item");
                selections.putNumChoice("Change Item Stocks");
                selections.putNumChoice("Remove an Item");
                selections.putNumChoice("Payment");
                selections.putNumChoice("Seller Account Settings");
                selections.putNumChoice("Back");
                selections.displaySelections();
                string selection = selections.select("--->> ");

                if (selection == "1"){
                    clearScreen();
                    addItemToShop();
                    setItemInfos();
                    clearScreen();
                }
                else if (selection == "2"){
                    if (sellerItemInfos.size() == 0){
                        cout << "There are no items to be selected." << endl;
                    }
                    else {
                        cout << "---Add Stock---" << endl;
                        int itemNum;
                        do {
                            cout << "Enter item number: ";
                            cin >> itemNum;
                            if (itemNum >= 1 && itemNum <= sellerItemInfos.size()) break;
                            cout << "Invalid Input." << endl;
                        } while (1);
                        SellerItemInfo sInfo = sellerItemInfos[itemNum - 1];
                        Item item = dataHandler->getItemDataHandler()->getItemInfo(sInfo.itemID);
                        clearScreen();
                        cout << "Item Name: " << item.getItemName() << endl;
                        cout << "Stocks: " << item.getStocks() << endl;
                        do {
                            cout << "How many stocks should this item have? ";
                            cin >> itemNum;
                            if (itemNum >= 1) break;
                            cout << "Invalid Input." << endl;
                        } while (1);
                        cout << "---CHANGE STOCKS---" << endl;
                        cout << "Number of Stocks changed to: " + numberToString(itemNum, 0) << endl;
                        Category category = item.getCategory();
                        category.status = ON_SALE_STATUS;
                        item.setCategory(category);
                        item.setStocks(itemNum);
                        ItemInfo itemInfo = dataHandler->getItemDataHandler()->getItemInfo();
                        itemInfo.flushItemInfo(new Item(item), itemInfo.getDefaultImages(item.getItemID()));

                        selections.clearSelections();
                        selections.putNumChoice("Back");
                        selections.displaySelections();
                        string back = selections.select("--->> ");
                    }

                    clearScreen();
                }
                else if (selection == "3"){
                    if (sellerItemInfos.size() == 0){
                        cout << "There are no items to be selected." << endl;
                    }
                    else {
                        cout << "---Remove Item---" << endl;
                        int itemNum;
                        do {
                            cout << "Enter item number: ";
                            cin >> itemNum;
                            if (itemNum >= 1 && itemNum <= sellerItemInfos.size()) break;
                            cout << "Invalid Input." << endl;
                        } while (1);
                        SellerItemInfo sInfo = sellerItemInfos[itemNum - 1];
                        Item item = dataHandler->getItemDataHandler()->getItemInfo(sInfo.itemID);

                        cout << "Are you sure want to remove the item? " << endl;
                        selections.clearSelections();
                        selections.putNumChoice("No");
                        selections.putNumChoice("Yes");
                        selections.displaySelections();
                        string contDelete = selections.select("--->> ");
                        if (contDelete == "2"){
                            vector<string> newItemList;
                            for (string itemID : loadedSellerAccount->getItemIDList()){
                                if (item.getItemID() != itemID) newItemList.push_back(itemID);
                            }
                            loadedSellerAccount->setItemIDList(newItemList);
                            loadedSellerAccount->flushSellerAccount();
                            clearScreen();
                            cout << "---ITEM REMOVED SUCCESSFULLY---" << endl;
                            cout << item.getItemID() << endl;
                            deleteFolderOnly(DataHandler::CHADA_DATABASE + "items/" + item.getItemID());
                            deleteFileOnly(DataHandler::CHADA_DATABASE + "system/INFO" + item.getItemID().substr(4, 17) + ".info");

                            selections.clearSelections();
                            selections.putNumChoice("Back");
                            selections.displaySelections();
                            string back = selections.select("--->> ");
                        }
                    }
                    clearScreen();
                }
                else if (selection == "4"){
                    clearScreen();
                    if (loadedSellerAccount->getBalance() >= 10000){
                        cout << "---PAYMENT----" << endl;
                        cout <<  "Select Payment Method..." << endl;
                        Selections selections;
                        selections.setSInputType(NUMBERS);
                        selections.putNumChoice("Check");
                        selections.putNumChoice("Bank Transfer");
                        selections.displaySelections();
                        string str = selections.select("--->> ");
                        float amount, toWithdraw;
                        if (str == "1"){
                            cout << fixed << setprecision(2) << "Your balance is P " << loadedSellerAccount->getBalance() << endl;
                            do {
                                cout << "How much would you like to withdraw? P ";
                                cin >> amount;
                                if (amount >= 5000){
                                    toWithdraw = amount + (amount * .05f);
                                    if (toWithdraw <= loadedSellerAccount->getBalance()) break;
                                    cout << "Insufficient Balance." << endl;
                                }
                                else cout << "You can only withdraw a max amount of P 5000.00." << endl;
                            } while (1);
                            cout << endl;
                            cout << "These are your informations..." << endl;
                            cout << "---BILLING ADDRESS---" << endl;
                            cout << "Address 1: " << loadedSellerAccount->getBillingAddress()->address1 << endl;
                            cout << "Address 2: " << loadedSellerAccount->getBillingAddress()->address2 << endl;
                            cout << "Town/City: " << loadedSellerAccount->getBillingAddress()->townOrCity << endl;
                            cout << "Region: " << loadedSellerAccount->getBillingAddress()->region << endl;
                            cout << "Amount to withdraw: P " << amount << endl;
                            cout << "Transfer Fee (5%): P " << amount * .05f << endl;
                            selections.clearSelections();
                            selections.numListTitle = "Continue?";
                            selections.putNumChoice("Yes");
                            selections.putNumChoice("No");
                            selections.displaySelections();
                            string contWith = selections.select("--->> ");
                            if (contWith == "1"){
                                clearScreen();
                                cout << "---PAYMENT SUCCESSFUL---" << endl;
                                loadedSellerAccount->setBalance(loadedSellerAccount->getBalance() - toWithdraw);
                                loadedSellerAccount->flushSellerAccount();

                                Selections selections;
                                selections.setSInputType(NUMBERS);
                                selections.putNumChoice("Back");
                                selections.displaySelections();
                                string back = selections.select("--->> ");
                            }
                        }
                        else {
                            cout << fixed << setprecision(2) << "Your balance is P " << loadedSellerAccount->getBalance() << endl;
                            do {
                                cout << "How much would you like to withdraw? P ";
                                cin >> amount;
                                if (amount >= 5000){
                                    toWithdraw = amount + (amount * .05f);
                                    if (toWithdraw <= loadedSellerAccount->getBalance()) break;
                                    cout << "Insufficient Balance." << endl;
                                }
                                else cout << "You can only withdraw a max amount of P 5000.00." << endl;
                            } while (1);
                            cout << endl;
                            Mastercard msCard;
                            cout << "You have requested to transfer money to your bank account..." << endl;
                            cout << "---CARD INFORMATION---" << endl;
                            cout << "Card Type: " << "Mastercard" << endl;
                            cout << "Card Number: **** **** **** " << loadedSellerAccount->getCardNum().substr(12, 16) << endl;
                            cout << "Amount to withdraw: P " << amount << endl;
                            cout << "Transfer Fee (5%): P " << amount * .05f << endl;
                            selections.clearSelections();
                            selections.numListTitle = "Continue?";
                            selections.putNumChoice("Yes");
                            selections.putNumChoice("No");
                            selections.displaySelections();
                            string contWith = selections.select("--->> ");
                            if (contWith == "1"){
                                clearScreen();
                                msCard.setCard(loadedSellerAccount->getCardNum(),
                                               loadedSellerAccount->getExpiryDate(), loadedSellerAccount->getCvc());
                                msCard.addAmount(amount);

                                cout << "---PAYMENT SUCCESSFUL---" << endl;
                                loadedSellerAccount->setBalance(loadedSellerAccount->getBalance() - toWithdraw);
                                loadedSellerAccount->flushSellerAccount();

                                selections.clearSelections();
                                selections.putNumChoice("Back");
                                selections.displaySelections();
                                string back = selections.select("--->> ");
                            }
                        }
                    }
                    else {
                        cout << "You balance before you can withdraw is P 10000.00." << endl;
                        selections.clearSelections();
                        selections.putNumChoice("Back");
                        selections.displaySelections();
                        string back = selections.select("--->> ");
                    }
                    clearScreen();
                }
                else if (selection == "5"){
                    clearScreen();

                    string address1, address2, townOrCity, region;
                    string cardNum, expiryDate, cvc;
                    cout << "---SELLER ACCOUNT SETTINGS---" << endl;
                    cout << "Change Billing Address Informations..." << endl;
                    cout << "Address 1: ";
                    getline(cin >> ws, address1);
                    cout << "Address 2: ";
                    getline(cin >> ws, address2);
                    cout << "Town/City: ";
                    getline(cin >> ws, townOrCity);
                    cout << "Region: ";
                    getline(cin >> ws, region);

                    cout << "Change Card Information..." << endl;
                    Mastercard msCard;
                    bool cont = false;
                    while (!cont){
                        cont = msCard.setCurrentMastercard();
                    }
                    cardNum = msCard.getCardNumber();
                    expiryDate = msCard.getExpiryDate();
                    cvc = msCard.getCVC();

                    Address address;
                    address.address1 = address1;
                    address.address2 = address2;
                    address.townOrCity = townOrCity;
                    address.region = region;
                    loadedSellerAccount->setBillingAddress(new Address(address));
                    loadedSellerAccount->setCardNum(cardNum);
                    loadedSellerAccount->setExpiryDate(expiryDate);
                    loadedSellerAccount->setCvc(cvc);
                    loadedSellerAccount->flushSellerAccount();

                    cout << "You have successfully changed your seller account settings." << endl;
                    selections.clearSelections();
                    selections.putNumChoice("Back");
                    selections.displaySelections();
                    string back = selections.select("--->> ");

                    clearScreen();
                }
                else if (selection == "6"){
                    state = -1;
                    sysManager->setCurrentScreen(SHOP_SCREEN);
                }
            }; break;
            default: break;
            }
        }
    }
    else {
        sysManager->setCurrentScreen(SHOP_SCREEN);
    }
    clearScreen();
}

SellerScreen::SellerScreen()
{

}

SellerScreen::SellerScreen(DataHandler *dataHandler, SystemManager *sysManager)
{
    this->dataHandler = dataHandler;
    this->sysManager = sysManager;
}


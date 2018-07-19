#include "shopscreen.h"
#include "selections.h"
#include "utils.h"
#include <iomanip>
#include <algorithm>
#include <windows.h>
#include "itempurchase.h"

void ShopScreen::setShopScreenState(const ShopScreenState &value)
{
    shopScreenState = value;
}
float ShopScreen::calculateRating(vector<Reviews> reviewList)
{
    vector<float> ratings;
    for (Reviews reviews : reviewList){
        if (reviews.rating >= 1 && reviews.rating <= 5){
            ratings.push_back(reviews.rating);
        }
    }

    return accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
}

void ShopScreen::displayScreen()
{
    switch (shopScreenState){
    case HOME: {
        clearScreen();

        string selectionStr = "P";
        while (selectionStr == "P"){
            cout << "Welcome " << dataHandler->getLoadedAcct()->getFirstName() << " " << dataHandler->getLoadedAcct()->getLastName()
                 << "!" << endl;
            Selections selections;
            selections.setSInputType(BOTH);
            selections.putNumChoice("Shop Now!");
            selections.putNumChoice("Top 50 CHADA Items");
            selections.putNumChoice("My Cart");
            selections.putNumChoice("Seller Account");
            selections.putNumChoice("Account Settings");
            selections.putNumChoice("Log out");
            selections.displaySelections();
            selectionStr = selections.specialSelect("Type in your selection: ");
            if (selectionStr == "P") admin->displayAdmin(dataHandler->getLoadedAcct()->getAccountID());
            else {
                int selection = stoi(selectionStr);
                switch (selection){
                case 1: shopScreenState = SHOP; break;
                case 2: shopScreenState = TOP_DEALS; break;
                case 3: shopScreenState = MY_CART; break;
                case 4: shopScreenState = SELLER_ACCOUNT; break;
                case 5: shopScreenState = ACCOUNT_SETTINGS; break;
                case 6: shopScreenState = LOG_OUT; break;
                default: break;
                }
                Cart *cart  = dataHandler->getItemDataHandler()->getCart();
                cart->setCart(dataHandler->getLoadedAcct()->getAccountID());
                shopState = SEARCH_SELECTION;
            }
            selectionStr = "x";
        }
    }; break;
    case SHOP: {
        clearScreen();
        vector<Item> itemList = dataHandler->getItemDataHandler()->getAllItems();

        switch (shopState){
        case SEARCH_SELECTION: {
            Selections searchTypeSelections;
            searchTypeSelections.setSInputType(NUMBERS);
            searchTypeSelections.putNumChoice("Search For An Item by Name");
            searchTypeSelections.putNumChoice("Search For An Item by Category");
            searchTypeSelections.putNumChoice("Back");
            searchTypeSelections.numListTitle = "SEARCH SHOP";
            searchTypeSelections.displaySelections();
            string selectionStr = searchTypeSelections.select("Type in your selection: ");
            int selection = stoi(selectionStr);
            switch (selection){
            case 1: {
                cout << endl;
                string keyword;
                cout << "Enter a keyword for your item: ";
                getline(cin >> ws, keyword);

                matchedItems.clear();
                for (int i = 0; i < itemList.size(); i++){
                    Item currentItem = itemList.at(i);
                    bool matched = false;
                    string itemName = toLowerString(currentItem.getItemName());
                    string keyName;
                    vector<string> categories;
                    Category itemCategory = currentItem.getCategory();
                    categories.push_back(toLowerString(itemCategory.mainCategory));
                    for (int i = 0; i < itemCategory.subCategory.size(); i++){
                        categories.push_back(toLowerString(itemCategory.subCategory.at(i)));
                    }
                    keyName = toLowerString(keyword);

                    if (ifStringHasSubstring(itemName, keyName) || ifStringHasSubstring(keyName, itemName)) matched = true;
                    else {
                        for (int i = 0; i < categories.size(); i++){
                            if (((string)(categories.at(i))).length() >= keyName.length()){
                                if (ifStringHasSubstring(categories.at(i), keyName)){
                                    matched = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (matched && currentItem.getStocks() != 0 &&
                            (currentItem.getCategory().status == TEST_ITEM_STATUS
                             || currentItem.getCategory().status == ON_SALE_STATUS)) matchedItems.push_back(currentItem);
                }
                shopState = ITEM_SELECTION;
            }; break;
            case 2: {
                cout << endl;
                string keyNum, keyword;
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
                categorySelections.numListTitle = "Select an Item Category";
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
                keyNum = categorySelections.select("Category No.: ");
                int num = stoi(keyNum);

                switch (num){
                case 1 : keyword = selection1; break;
                case 2 : keyword = selection2; break;
                case 3 : keyword = selection3; break;
                case 4 : keyword = selection4; break;
                case 5 : keyword = selection5; break;
                case 6 : keyword = selection6; break;
                case 7 : keyword = selection7; break;
                case 8 : keyword = selection8; break;
                case 9 : keyword = selection9; break;
                case 10 : keyword = selection10; break;
                case 11 : keyword = selection11; break;
                case 12 : keyword = selection12; break;
                case 13 : keyword = selection13; break;
                case 14 : keyword = selection14; break;
                case 15 : keyword = selection15; break;
                case 16 : keyword = selection16; break;
                case 17 : keyword = selection17; break;
                case 18 : keyword = selection18; break;
                default: break;
                }

                matchedItems.clear();
                for (int i = 0; i < itemList.size(); i++){
                    Item currentItem = itemList.at(i);
                    bool matched = false;
                    string itemName = toLowerString(currentItem.getItemName());
                    string keyName;
                    vector<string> categories;
                    Category itemCategory = currentItem.getCategory();
                    categories.push_back(toLowerString(itemCategory.mainCategory));
                    for (int i = 0; i < itemCategory.subCategory.size(); i++){
                        categories.push_back(toLowerString(itemCategory.subCategory.at(i)));
                    }
                    keyName = toLowerString(keyword);

                    if (ifStringHasSubstring(itemName, keyName) || ifStringHasSubstring(keyName, itemName)) matched = true;
                    else {
                        for (int i = 0; i < categories.size(); i++){
                            if (((string)(categories.at(i))).length() >= keyName.length()){
                                if (ifStringHasSubstring(categories.at(i), keyName)){
                                    matched = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (matched && currentItem.getStocks() != 0 &&
                            (currentItem.getCategory().status == TEST_ITEM_STATUS
                             || currentItem.getCategory().status == ON_SALE_STATUS)) matchedItems.push_back(currentItem);
                }
                shopState = ITEM_SELECTION;
            }; break;
            case 3: shopScreenState = HOME; break;
            default: break;
            }
        }; break;
        case ITEM_SELECTION: {
            clearScreen();
            cout << left
                 << setw(5) << "NO."
                 << setw(35) << "ITEM NAME"
                 << setw(30) << "PRICE(PHP)"
                 << setw(20) << "RATING(1-5 STARS)"
                 << setw(10) << "STOCKS LEFT" << endl;
            if (matchedItems.size() == 0){
                cout << "\t\t\t" << "No item matches your search" << endl;
            }
            else {
                for (int i = 0; i < matchedItems.size(); i++){
                    Item item = matchedItems.at(i);
                    string itemName = item.getItemName();
                    string price;
                    int discount = ((1.0 - item.getDiscountedPrice() / item.getOriginalPrice()) * 100);
                    if (discount > 0){
                        price = "P " + numberToString(item.getDiscountedPrice(), 2) + " (" + numberToString(discount, 2) + "% off)";
                    }
                    else price = "P " + numberToString(item.getDiscountedPrice(), 2);
                    float rating = item.getRating();
                    string star = (rating > 1) ? "Stars" : "Star";
                    string ratingText = numberToString(rating, 0);
                    string ratingDisplay = (ratingText == "nan") ? "No rating" : ratingText + " " + star;
                    string stocksLeft = (item.getStocks() <= 10) ? numberToString(item.getStocks(), 0) + " left" : "More than 10 available";

                    cout << left
                         << setw(5) << i + 1
                         << setw(35) << limitStringSize(itemName, 30)
                         << setw(30) << price
                         << setw(20) << ratingDisplay
                         << setw(10) << stocksLeft << endl;
                }
            }
            cout << endl;
            Selections itemSelections;
            itemSelections.setSInputType(BOTH);
            itemSelections.numListTitle = "---To Select an Item, Type the Item Number---";
            itemSelections.letterListATitle = "---Sorting Options---";
            itemSelections.letterListBTitle = "---Other Options---";
            itemSelections.putLetterChoiceA("Alphabetical (A-Z)");
            itemSelections.putLetterChoiceA("Alphabetical (Z-A)");
            itemSelections.putLetterChoiceA("Lowest Price");
            itemSelections.putLetterChoiceA("Highest Price");
            itemSelections.putLetterChoiceA("Relevance (Most Viewed)");
            itemSelections.putLetterChoiceA("Top Customer Ratings");
            itemSelections.putLetterChoiceB("Search for Another Item");
            itemSelections.putLetterChoiceB("Back to Menu");
            cout << itemSelections.numListTitle << endl;
            for (int i = 0; i < matchedItems.size(); i++) itemSelections.putNumChoice("Item No." + (i + 1));
            itemSelections.displaySelections(false);
            cout << endl;
            string selection = itemSelections.select("------>>>> ");
            cout << selection << endl;
            if (selection == "A"){
                vector<Item> newMatchedList;
                vector<string> itemNames;
                for (Item item : matchedItems) itemNames.push_back(toLowerString(item.getItemName()));
                sort(itemNames.begin(), itemNames.end());
                for (string str : itemNames){
                    for (Item item : matchedItems){
                        if (toLowerString(item.getItemName()) == str){
                            newMatchedList.push_back(item);
                            break;
                        }
                    }
                }
                matchedItems = newMatchedList;
            }
            else if (selection == "B"){
                vector<Item> newMatchedList;
                vector<string> itemNames;
                for (Item item : matchedItems) itemNames.push_back(toLowerString(item.getItemName()));
                sort(itemNames.begin(), itemNames.end());

                for (int i = itemNames.size() - 1; i >= 0; i--){
                    for (Item item : matchedItems){
                        if (toLowerString(item.getItemName()) == itemNames.at(i)){
                            newMatchedList.push_back(item);
                            break;
                        }
                    }
                }
                matchedItems = newMatchedList;
            }
            else if (selection == "C"){
                vector<Item> newMatchedList;
                vector<float> prices;
                for (Item item : matchedItems) prices.push_back(item.getDiscountedPrice());
                sort(prices.begin(), prices.end());

                for (float price : prices){
                    for (Item item : matchedItems){
                        if (item.getDiscountedPrice() == price){
                            newMatchedList.push_back(item);
                            break;
                        }
                    }
                }
                matchedItems = newMatchedList;
            }
            else if (selection == "D"){
                vector<Item> newMatchedList;
                vector<float> prices;
                for (Item item : matchedItems) prices.push_back(item.getDiscountedPrice());
                sort(prices.begin(), prices.end());


                for (int i = prices.size() - 1; i >= 0; i--){
                    for (Item item : matchedItems){
                        if (item.getDiscountedPrice() == prices[i]){
                            newMatchedList.push_back(item);
                            break;
                        }
                    }
                }
                matchedItems = newMatchedList;
            }
            else if (selection == "E"){
                vector<Item> newMatchedList;
                vector<int> mostViewedItems;
                for (Item item : matchedItems) mostViewedItems.push_back(item.getCategory().noOfViews);
                sort(mostViewedItems.begin(), mostViewedItems.end());

                for (int numOfViews : mostViewedItems){
                    for (Item item : matchedItems){
                        if (item.getCategory().noOfViews == numOfViews){
                            newMatchedList.push_back(item);
                            break;
                        }
                    }
                }
                matchedItems = newMatchedList;
            }
            else if (selection == "F"){
                vector<Item> newMatchedList;
                vector<Item> noRatingItems;
                vector<Item> ratingItems;
                vector<float> ratings;
                for (Item item : matchedItems) if (numberToString(item.getRating(), 0) == "nan")
                    noRatingItems.push_back(item);
                for (Item item : matchedItems) if (numberToString(item.getRating(), 0) != "nan")
                    ratingItems.push_back(item);
                for (Item item : ratingItems) ratings.push_back(item.getRating());
                sort(ratings.begin(), ratings.end());
                for (int i = ratings.size() - 1; i >= 0; i--){
                    for (Item item : ratingItems){
                        if (item.getRating() == ratings[i]){
                            newMatchedList.push_back(item);
                            break;
                        }
                    }
                }
                for (Item item : noRatingItems) newMatchedList.push_back(item);
                matchedItems = newMatchedList;
            }
            else if (selection == "G"){
                shopState = SEARCH_SELECTION;
            }
            else if (selection == "H"){
                shopScreenState = HOME;
            }
            else {
                previewedItem = new Item(matchedItems.at(stoi(selection) - 1));
                shopState = ITEM_PREVIEW;
            }
        }; break;
        case ITEM_PREVIEW: {
            Category category = previewedItem->getCategory();
            category.noOfViews++;
            previewedItem->setCategory(category);

            cout << fixed << setprecision(2);
            cout << "\t\t\t\tITEM PREVIEW" << endl << endl;
            cout << "Item Name: " << previewedItem->getItemName() << endl;
            cout << "Item condition: " << previewedItem->getItemCondition() << endl;
            cout << "Original Price: P " << previewedItem->getOriginalPrice() << endl;
            cout << "Real Price: P " << previewedItem->getDiscountedPrice() << endl << endl;
            cout << "Item Description: " << previewedItem->getItemDescription() << endl << endl;
            cout << "Postage: " << previewedItem->getPostage() << endl;
            cout << "Item Location: " << previewedItem->getItemLocation() << endl;
            cout << "Returns: " << previewedItem->getReturns() << endl;

            string rating;
            string stars = (previewedItem->getRating() > 1) ? "Stars" : "Star";
            if (numberToString(previewedItem->getRating(), 0) == "nan") rating = "No rating";
            else rating = numberToString(previewedItem->getRating(), 0) + " " + stars;
            cout << "Rating: " << rating << endl;

            string stocks = (previewedItem->getStocks() > 10) ? "More than 10 available" : numberToString(previewedItem->getStocks(), 0) + " left";
            cout << "Stocks: " << stocks << endl << endl;

            string seller = "<<--Item Sold by: ";
            if (previewedItem->getCategory().status == "TEST ITEM"){
                seller += previewedItem->getTestItemInfo().username;
            }
            else {
                SellerAccount sAcct = dataHandler->getSellerDataHandler()->getSellerInfo(dataHandler->getLoadedAcct()->getAccountID());
                seller += sAcct.getSellerName();
            }
            cout << seller << endl;
            cout << endl;

            Selections itemPreviewSelections;
            itemPreviewSelections.setSInputType(BOTH);
            itemPreviewSelections.numListTitle = "---Item Options---";
            itemPreviewSelections.letterListATitle = "---Buy Options---";
            itemPreviewSelections.letterListBTitle = "---Other Options---";
            itemPreviewSelections.putNumChoice("Preview Item Images");
            itemPreviewSelections.putNumChoice("View Seller's' Info");
            itemPreviewSelections.putNumChoice("View Customer Reviews");
            itemPreviewSelections.putLetterChoiceA("Buy Item");
            itemPreviewSelections.putLetterChoiceA("Add Item to Cart");
            itemPreviewSelections.putLetterChoiceB("Back");
            itemPreviewSelections.displaySelections();
            cout << endl;
            string itemPreviewSelection = itemPreviewSelections.select("------>>>> ");

            if (itemPreviewSelection == "1"){
                string imageDirectory = DataHandler::CHADA_DATABASE + "items/" + previewedItem->getItemID()
                        + "/images/0.jpg";
                ShellExecuteA(0, 0, imageDirectory.c_str(), 0, 0 , SW_SHOW );
            }
            else if (itemPreviewSelection == "2"){
                if (previewedItem->getCategory().status == "TEST ITEM"){
                    clearScreen();
                    cout << "---Seller Info---" << endl;
                    cout << "Username: " << previewedItem->getTestItemInfo().username << endl;
                    cout << "Email: " << previewedItem->getTestItemInfo().email << endl;
                    cout << "Contact No.: " << previewedItem->getTestItemInfo().contactNo << endl;
                    Selections sellerInfoSelection;
                    sellerInfoSelection.setSInputType(NUMBERS);
                    sellerInfoSelection.putNumChoice("Back");
                    cout << endl;
                    sellerInfoSelection.displaySelections();
                    string sInfoSelection = sellerInfoSelection.select("--->> ");
                    clearScreen();
                }
                else {
                    SellerAccount sAcct = dataHandler->getSellerDataHandler()->getSellerInfo(dataHandler->getLoadedAcct()->getAccountID());
                    clearScreen();
                    cout << "---Seller Info---" << endl;
                    cout << "Username: " << sAcct.getSellerName() << endl;
                    cout << "Email: " << sAcct.getSellerName() << "@gmail.com" << endl;
                    cout << "Contact No.: " << "09123649232" << endl;
                    Selections sellerInfoSelection;
                    sellerInfoSelection.setSInputType(NUMBERS);
                    sellerInfoSelection.putNumChoice("Back");
                    cout << endl;
                    sellerInfoSelection.displaySelections();
                    string sInfoSelection = sellerInfoSelection.select("--->> ");
                    clearScreen();
                }
            }
            else if (itemPreviewSelection == "3"){
                clearScreen();

                int reviewState = 0;
                vector<Reviews> reviewsList;

                while (reviewState != -1){
                    switch (reviewState){
                    case 0: {
                        bool canAddReview = true;

                        cout << "---Customer Reviews---" << endl;
                        reviewsList = previewedItem->getReviews();
                        for (Reviews reviews : reviewsList) if (reviews.accountID == dataHandler->getLoadedAcct()->getAccountID()){
                            canAddReview = false;
                            break;
                        }
                        if (reviewsList.size() == 0){
                            cout << endl;
                            cout << "There are no customer ratings for this item yet." << endl;
                        }
                        else {
                            for (Reviews reviews : reviewsList){
                                cout << endl;
                                cout << reviews.review << endl;
                                string star = (previewedItem->getRating() > 1) ? "Stars" : "Star";
                                string rating = numberToString(previewedItem->getRating(), 0) + " " + star;
                                string ratingText = rating + " <<-->> by " + reviews.name;
                                cout << ratingText << endl;
                                cout << endl;
                            }
                        }
                        cout << endl;
                        Selections reviewSelections;
                        reviewSelections.setSInputType(NUMBERS);
                        if (canAddReview) reviewSelections.putNumChoice("Add a review");
                        reviewSelections.putNumChoice("Back");
                        reviewSelections.displaySelections();
                        string rSelection = reviewSelections.select("-->> ");
                        if (canAddReview){
                            if (rSelection == "1"){
                                reviewState = 1;
                                clearScreen();
                            } else reviewState = -1;
                        }
                        else reviewState = -1;
                    }; break;
                    case 1: {
                        string review;
                        float rating;
                        float aveRating;
                        cout << "Type in your review: ";
                        getline(cin >> ws, review);

                        do {
                            cout << "What is you rating for this item (1 - 5): ";
                            cin >> rating;
                            if (rating >= 1 && rating <= 5) break;
                            cout << "Invalid rating." << endl;
                        } while (1);

                        Reviews myReviews;
                        myReviews.accountID = dataHandler->getLoadedAcct()->getAccountID();
                        myReviews.name = dataHandler->getLoadedAcct()->getAccountName();
                        myReviews.rating = rating;
                        myReviews.review = review;
                        myReviews.timeSubmitted = 1;

                        reviewsList.push_back(myReviews);
                        aveRating = calculateRating(reviewsList);
                        previewedItem->setRating(aveRating);
                        previewedItem->setReviews(reviewsList);

                        dataHandler->getItemDataHandler()->getItemInfo().flushItemInfo(
                                    previewedItem, dataHandler->getItemDataHandler()->getItemInfo().getDefaultImages(
                                        previewedItem->getItemID()));

                        reviewState = 0;
                        clearScreen();
                    }; break;
                    default: break;
                    }
                }

                clearScreen();
            }
            else if (itemPreviewSelection == "A"){
                ItemPurchase itemPurchase(dataHandler);
                itemPurchase.setItemToPurchase(previewedItem);
                bool success = itemPurchase.purchaseItem();
                if (success){
                    cout << "THANK YOU FOR SHOPPING AT CHADA" << endl;
                    cout << EMAIL_CONFIRM << endl;
                }
                cout << endl;
                Selections selections;
                selections.setSInputType(NUMBERS);
                selections.putNumChoice("Back to Items Selection");
                selections.displaySelections();
                string selection = selections.select("--->>");
                shopState = ITEM_SELECTION;
            }
            else if (itemPreviewSelection == "B"){
                clearScreen();
                cout << "---Add Item to Cart---" << endl;
                cout << "Item Name: " << previewedItem->getItemName() << endl << endl;
                dataHandler->getItemDataHandler()->getCart()->addItemToCart(previewedItem);
                Selections selections;
                selections.setSInputType(NUMBERS);
                selections.putNumChoice("Back to Items Selection");
                selections.displaySelections();
                string selection = selections.select("--->>");
                shopState = ITEM_PREVIEW;
                clearScreen();
            }
            else if (itemPreviewSelection == "C"){
                shopState = ITEM_SELECTION;
            }
        }; break;
        default: break;
        }
    }; break;
    case TOP_DEALS: {
        vector<Item> items = dataHandler->getItemDataHandler()->getAllItems();
        matchedItems.clear();
        vector<Item> *itemList = new vector<Item>(items);
        while (matchedItems.size() < 20){
            int topIndex = 0;
            for (int i = 0; i < itemList->size(); i++){
                Item itemA = itemList->at(i);
                Item itemB = itemList->at(topIndex);
                float scoreA, scoreB;
                float ratingA, ratingB;
                ratingA = (numberToString(itemA.getRating(), 0) != "nan") ? itemA.getRating() : 0;
                ratingB = (numberToString(itemB.getRating(), 0) != "nan") ? itemB.getRating() : 0;
                scoreA = itemA.getCategory().noOfViews * ratingA;
                scoreB = itemB.getCategory().noOfViews * ratingB;
                if (scoreA > scoreB) topIndex = i;
            }
            Item selectedItem = itemList->at(topIndex);
            if (selectedItem.getStocks() != 0 &&
                    (selectedItem.getCategory().status == TEST_ITEM_STATUS
                     || selectedItem.getCategory().status == ON_SALE_STATUS)){
                matchedItems.push_back(selectedItem);
                itemList->erase(itemList->begin() + topIndex);
            }
        }
        shopScreenState = SHOP;
        shopState = ITEM_SELECTION;
    }; break;
    case MY_CART: {
        Cart *cart  = dataHandler->getItemDataHandler()->getCart();
        cart->displayCart();
        cart->resetCartData();
        shopScreenState = HOME;
    }; break;
    case SELLER_ACCOUNT: {
        shopScreenState = HOME;
        sysManager->setCurrentScreen(SELLER_SCREEN);
    }; break;
    case ACCOUNT_SETTINGS: {
        clearScreen();

        cout << "---Change Account Settings---" << endl;

        string accountID;
        string accountName;
        string email;
        string password;
        string firstName;
        char middleInitial;
        string lastName;
        string contactNo;
        Address shippingAddress;

        Account account;
        account.permitFieldSettings("123sasad3SAD!!#!!sad$#");

        cout << "First name: ";
        getline(cin >> ws, firstName);
        cout << "Middle initial: ";
        cin >> middleInitial;
        cout << "Last name: ";
        getline(cin >> ws, lastName);

        int cont;
        do {
            cont = 1;
            cout << "Username: ";
            getline(cin >> ws, accountName);
            if (!isLettersAndNumbersOnly(accountName)){
                cout << "Invalid username format. Should only be in letters and numbers." << endl;
                cont = 0;
            }
            if (dataHandler->checkIfUsernameExists(accountName)){
                cout << "Another user has taken that username." << endl;
                cont = 0;
            }
        } while (cont != 1);

        do {
            cont = 1;
            cout << "Email: ";
            getline(cin >> ws, email);
            if (!checkEmailHasCorrectFormat(email)){
                cout << "Invalid email format. Please include the local host (i.e. @gmail, @yahoo, etc.)." << endl;
                cont = 0;
            }
            if (dataHandler->checkIfEmailExists(email)){
                cout << "Another user has taken that email." << endl;
                cont = 0;
            }
        } while (cont != 1);

        do {
            cout << "Password: ";
            string strPassword = acquirePassword();
            cout << endl;
            if (strPassword.size() >= 5 && strPassword.size() <= 32){
                password = strPassword;
                break;
            }
            else cout << "Password should consists of 5 to 32 characters." << endl;
        } while (1);
        cout << "Please enter shipping address information." << endl;
        cout << "Address 1: ";
        getline(cin >> ws, shippingAddress.address1);
        cout << "Address 2: ";
        getline(cin >> ws, shippingAddress.address2);
        cout << "Town/City: ";
        getline(cin >> ws, shippingAddress.townOrCity);
        cout << "Region: ";
        getline(cin >> ws, shippingAddress.region);
        do {
            cout << "Contact No.: ";
            getline(cin >> ws, contactNo);
            if (isContactNumFormat(contactNo)) break;
            else cout << "Invalid contact no. format." << endl;
        } while (1);

        account.setFields(dataHandler->getLoadedAcct()->getAccountID(), accountName, email, password, firstName, middleInitial,
                          lastName, contactNo, shippingAddress);
        account.flushAccount();
        dataHandler->setLoadedAcct(new Account(account));

        clearScreen();
    }; break;
    case LOG_OUT: {
        shopScreenState = HOME;
        sysManager->setCurrentScreen(SIGN_IN_SCREEN);
    }; break;
    default: break;
    }
}

ShopScreen::ShopScreen()
{

}

ShopScreen::ShopScreen(DataHandler *dataHandler, SystemManager *sysManager)
{
    this->dataHandler = dataHandler;
    this->sysManager = sysManager;
    admin = new Admin(dataHandler);
}

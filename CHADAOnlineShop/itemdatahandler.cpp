#include "itemdatahandler.h"
#include "datahandler.h"
#include <fstream>
#include <string>
#include "utils.h"


ItemInfo ItemDataHandler::getItemInfo() const
{
    return itemInfo;
}

DataHandler *ItemDataHandler::getDataHandler() const
{
    return dataHandler;
}

void ItemDataHandler::setDataHandler(DataHandler *value)
{
    dataHandler = value;
}

Cart *ItemDataHandler::getCart() const
{
    return cart;
}

string ItemDataHandler::generateNewItemID()
{
    char *id = new char[13];
    bool cont;
    while (!cont){
        cont = true;
        genRandomID(id, 13);
        vector<string> itemFolders = getListOfFilesFromDirec(DataHandler::CHADA_DATABASE + "items/");
        for (string foldName : itemFolders){
            if (ifStringHasSubstring(foldName, string(id))) cont = false;
        }
    }
    return string(id);
}

bool ItemDataHandler::checkIfItemNameExists(string itemName)
{
    vector<Item> itemList = dataHandler->getItemDataHandler()->getAllItems();
    for (Item item : itemList){
        if (itemName == item.getItemName()) return true;
    }
    return false;
}

Item ItemDataHandler::getItemInfo(string itemID)
{
    Item itemToReturn;
    vector<Item> itemList = dataHandler->getItemDataHandler()->getAllItems();
    for (Item item : itemList){
        if (item.getItemID() == itemID){
            itemToReturn = item;
            break;
        }
    }
    return itemToReturn;
}

vector<Item> ItemDataHandler::getAllItems()
{
    vector<Item> items;
    vector<string> listOfItemFolders = getListOfFilesFromDirec(DataHandler::CHADA_DATABASE + "items/");
    for (int i = 0; i < listOfItemFolders.size(); i++){
        Item item;

        ifstream itemFileStream1, itemFileStream2, itemFileStream3, itemReviewFileStream;

        itemFileStream1.open((DataHandler::CHADA_DATABASE + "items/" + listOfItemFolders.at(i) + "/info1.chada").data(), ios::in);
        if (itemFileStream1.is_open()){
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

            getline(itemFileStream1 >> ws, itemName);
            removeSubstring(itemName, "Item Name:");
            getline(itemFileStream1 >> ws, itemCondition);
            removeSubstring(itemCondition, "Item Condition:");

            string price;
            getline(itemFileStream1 >> ws, price);
            removeSubstring(price, "Original Price:");
            originalPrice = stof(price);

            getline(itemFileStream1 >> ws, price);
            removeSubstring(price, "Discounted Price:");
            discountedPrice = stof(price);

            getline(itemFileStream1 >> ws, postage);
            removeSubstring(postage, "Postage:");
            getline(itemFileStream1 >> ws, itemLocation);
            removeSubstring(itemLocation, "Item Location:");
            getline(itemFileStream1 >> ws, returns);
            removeSubstring(returns, "Returns:");
            getline(itemFileStream1 >> ws, itemDescription);
            removeSubstring(itemDescription, "Item Description:");
            getline(itemFileStream1 >> ws, itemID);
            removeSubstring(itemID, "Item ID:");
            getline(itemFileStream1 >> ws, sellerID);
            removeSubstring(sellerID, "Seller ID:");

            string temp;
            getline(itemFileStream1 >> ws, temp);
            removeSubstring(temp, "Rating:");
            rating = stof(temp);

            getline(itemFileStream1 >> ws, temp);
            removeSubstring(temp, "Stocks:");
            stocks = stoi(temp);

            item.setItemName(itemName);
            item.setItemCondition(itemCondition);
            item.setOriginalPrice(originalPrice);
            item.setDiscountedPrice(discountedPrice);
            item.setPostage(postage);
            item.setItemLocation(itemLocation);
            item.setReturns(returns);
            item.setItemDescription(itemDescription);
            item.setItemID(itemID);
            item.setSellerID(sellerID);
            item.setRating(rating);
            item.setStocks(stocks);
        }
        else {
            cerr << "Error opening item file 1." << endl;
            exit(1);
        }

        itemFileStream2.open((DataHandler::CHADA_DATABASE + "items/" + listOfItemFolders.at(i) + "/info2.chada").data(), ios::in);
        if (itemFileStream2.is_open()){
            Category category;

            getline(itemFileStream2 >> ws, category.mainCategory);
            removeSubstring(category.mainCategory, "Main Category:");

            vector<string> subcategories;
            string subCategory;
            getline(itemFileStream2 >> ws, subCategory);
            removeSubstring(subCategory, "Sub Category:");
            while (subCategory.size() != 0){
                string categoryA = substringAtPos(subCategory, 0, ',');
                subcategories.push_back(categoryA);
                removeSubstring(subCategory, categoryA + ",");
            }
            category.subCategory = subcategories;

            getline(itemFileStream2 >> ws, category.status);
            removeSubstring(category.status, "Status:");

            string temp;
            getline(itemFileStream2 >> ws, temp);
            removeSubstring(temp, "No. of Views:");
            category.noOfViews = stoi(temp);

            item.setCategory(category);
        }
        else {
            cerr << "Error opening item file 2." << endl;
            exit(1);
        }

        if (item.getCategory().status == "TEST ITEM"){
            itemFileStream3.open((DataHandler::CHADA_DATABASE + "items/" + listOfItemFolders.at(i) + "/info3.chada").data(), ios::in);
            if (itemFileStream3.is_open()){
                TestItemInfo testItemInfo;

                getline(itemFileStream3 >> ws, testItemInfo.username);
                removeSubstring(testItemInfo.username, "Username:");
                getline(itemFileStream3 >> ws, testItemInfo.email);
                removeSubstring(testItemInfo.email, "Email Address:");
                getline(itemFileStream3 >> ws, testItemInfo.contactNo);
                removeSubstring(testItemInfo.contactNo, "Contact No:");

                item.setTestItemInfo(testItemInfo);
            }
            else {
                cerr << "Error opening item file 3." << endl;
                exit(1);
            }
        }

        itemReviewFileStream.open((DataHandler::CHADA_DATABASE + "items/" + listOfItemFolders.at(i) + "/reviews.chada").data(), ios::in);
        if (itemReviewFileStream.is_open()){
            vector<Reviews> reviews;
            if (!isFileEmpty(itemReviewFileStream)){
                while (!itemReviewFileStream.eof()){
                    Reviews review;

                    getline(itemReviewFileStream >> ws, review.accountID);
                    removeSubstring(review.accountID, "Account ID:");
                    if (review.accountID.empty()) break;

                    getline(itemReviewFileStream >> ws, review.name);
                    removeSubstring(review.name, "Account Name:");

                    string temp;
                    getline(itemReviewFileStream >> ws, temp);
                    removeSubstring(temp, "Account Rating:");
                    review.rating = stof(temp);

                    getline(itemReviewFileStream >> ws, review.review);
                    removeSubstring(review.review, "Account Review:");

                    getline(itemReviewFileStream >> ws, temp);
                    removeSubstring(temp, "Time Submitted:");
                    review.timeSubmitted = stol(temp);
                    reviews.push_back(review);
                }
                item.setReviews(reviews);
            }
        }
        else {
            cerr << "Error opening review file." << endl;
            exit(1);
        }

        itemFileStream1.close();
        itemFileStream2.close();
        itemFileStream3.close();
        itemReviewFileStream.close();

        items.push_back(item);
    }

    return items;
}

ItemDataHandler::ItemDataHandler()
{
    cart = new Cart(this);
}


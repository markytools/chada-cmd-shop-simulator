#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <vector>
using namespace std;

struct Category {
    string mainCategory;
    vector<string> subCategory;
    string status;
    int noOfViews;
};

struct TestItemInfo {
    string username;
    string email;
    string contactNo;
};

struct Reviews {
    string accountID;
    string name;
    float rating;
    string review;
    long timeSubmitted;
};

class Item
{
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
    TestItemInfo testItemInfo;
    vector<Reviews> reviews;
public:
    Item();

    string getItemName() const;
    void setItemName(const string &value);
    string getItemCondition() const;
    void setItemCondition(const string &value);
    string getPostage() const;
    void setPostage(const string &value);
    string getItemLocation() const;
    void setItemLocation(const string &value);
    string getReturns() const;
    void setReturns(const string &value);
    string getItemDescription() const;
    void setItemDescription(const string &value);
    string getItemID() const;
    void setItemID(const string &value);
    string getSellerID() const;
    void setSellerID(const string &value);
    float getRating() const;
    void setRating(float value);
    int getStocks() const;
    void setStocks(int value);
    Category getCategory() const;
    void setCategory(const Category &value);
    TestItemInfo getTestItemInfo() const;
    void setTestItemInfo(const TestItemInfo &value);
    vector<Reviews> getReviews() const;
    void setReviews(const vector<Reviews> &value);
    float getOriginalPrice() const;
    void setOriginalPrice(float value);
    float getDiscountedPrice() const;
    void setDiscountedPrice(float value);
};

#endif // ITEM_H

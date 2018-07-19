#include "item.h"


string Item::getItemName() const
{
    return itemName;
}

void Item::setItemName(const string &value)
{
    itemName = value;
}

string Item::getItemCondition() const
{
    return itemCondition;
}

void Item::setItemCondition(const string &value)
{
    itemCondition = value;
}

string Item::getPostage() const
{
    return postage;
}

void Item::setPostage(const string &value)
{
    postage = value;
}

string Item::getItemLocation() const
{
    return itemLocation;
}

void Item::setItemLocation(const string &value)
{
    itemLocation = value;
}

string Item::getReturns() const
{
    return returns;
}

void Item::setReturns(const string &value)
{
    returns = value;
}

string Item::getItemDescription() const
{
    return itemDescription;
}

void Item::setItemDescription(const string &value)
{
    itemDescription = value;
}

string Item::getItemID() const
{
    return itemID;
}

void Item::setItemID(const string &value)
{
    itemID = value;
}

string Item::getSellerID() const
{
    return sellerID;
}

void Item::setSellerID(const string &value)
{
    sellerID = value;
}

float Item::getRating() const
{
    return rating;
}

void Item::setRating(float value)
{
    rating = value;
}

int Item::getStocks() const
{
    return stocks;
}

void Item::setStocks(int value)
{
    stocks = value;
}

Category Item::getCategory() const
{
    return category;
}

void Item::setCategory(const Category &value)
{
    category = value;
}

TestItemInfo Item::getTestItemInfo() const
{
    return testItemInfo;
}

void Item::setTestItemInfo(const TestItemInfo &value)
{
    testItemInfo = value;
}

vector<Reviews> Item::getReviews() const
{
    return reviews;
}

void Item::setReviews(const vector<Reviews> &value)
{
    reviews = value;
}

float Item::getOriginalPrice() const
{
    return originalPrice;
}

void Item::setOriginalPrice(float value)
{
    originalPrice = value;
}

float Item::getDiscountedPrice() const
{
    return discountedPrice;
}

void Item::setDiscountedPrice(float value)
{
    discountedPrice = value;
}
Item::Item()
{

}


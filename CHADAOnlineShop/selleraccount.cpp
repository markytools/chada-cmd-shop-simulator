#include "selleraccount.h"
#include "utils.h"
#include <fstream>
#include "datahandler.h"

Address *SellerAccount::getBillingAddress() const
{
    return billingAddress;
}

void SellerAccount::setBillingAddress(Address *value)
{
    billingAddress = value;
}

string SellerAccount::getAccountID() const
{
    return accountID;
}

void SellerAccount::setAccountID(const string &value)
{
    accountID = value;
}


float SellerAccount::getScore() const
{
    return score;
}

void SellerAccount::setScore(float value)
{
    score = value;
}
void SellerAccount::flushSellerAccount()
{
    string directory = DataHandler::CHADA_DATABASE + "accounts/" + sellerID + ".acct";
    ofstream outfile;
    outfile.open(directory.data(), ios::out);
    if (outfile.is_open()){
        outfile << "Seller Name:" << sellerName << endl;
        outfile << "Seller Score:" << score << endl;
        outfile << "Account ID:" << accountID << endl;
        outfile << "Seller ID:" << sellerID << endl;
        outfile << "Balance:" << balance << endl;
        outfile << "Card Number:" << cardNum << endl;
        outfile << "Expiry Date:" << expiryDate << endl;
        outfile << "CVC:" << cvc << endl;
        outfile << "List of Item ID:" ;
        for (string itemID : itemIDList){
            outfile << itemID << ",";
        }
        outfile << endl;
        outfile << "Address 1:" << billingAddress->address1 << endl;
        outfile << "Address 2:" << billingAddress->address2 << endl;
        outfile << "Town/City:" << billingAddress->townOrCity << endl;
        outfile << "Region:" << billingAddress->region << endl;
    }
    else {
        cerr << "Error creating seller file." << endl;
        exit(1);
    }
    outfile.close();
}

string SellerAccount::getSellerName() const
{
    return sellerName;
}

void SellerAccount::setSellerName(const string &value)
{
    sellerName = value;
}

string SellerAccount::getSellerID() const
{
    return sellerID;
}

void SellerAccount::setSellerID(const string &value)
{
    sellerID = value;
}

string SellerAccount::getCardNum() const
{
    return cardNum;
}

void SellerAccount::setCardNum(const string &value)
{
    cardNum = value;
}

string SellerAccount::getExpiryDate() const
{
    return expiryDate;
}

void SellerAccount::setExpiryDate(const string &value)
{
    expiryDate = value;
}

string SellerAccount::getCvc() const
{
    return cvc;
}

void SellerAccount::setCvc(const string &value)
{
    cvc = value;
}

vector<string> SellerAccount::getItemIDList() const
{
    return itemIDList;
}

void SellerAccount::setItemIDList(const vector<string> &value)
{
    itemIDList = value;
}

float SellerAccount::getBalance() const
{
    return balance;
}

void SellerAccount::setBalance(float value)
{
    balance = value;
}

SellerAccount::SellerAccount()
{

}


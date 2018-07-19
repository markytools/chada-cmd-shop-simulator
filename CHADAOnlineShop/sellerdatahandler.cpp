#include "sellerdatahandler.h"
#include <fstream>
#include "utils.h"
#include "datahandler.h"
#include <string>
#include "utils.h"

SellerAccount SellerDataHandler::getSellerInfo(string accountID)
{
    vector<SellerAccount> sellerAccts = getListOfSellerAccounts();
    for (SellerAccount sellerAcct : sellerAccts){
        if (accountID == sellerAcct.getAccountID()) return sellerAcct;
    }
}

string SellerDataHandler::generateNewSellerID()
{
    char *id = new char[13];
    vector<string> fileNames = getListOfFilesFromDirec(DataHandler::CHADA_DATABASE + "accounts/");

    bool hasID;
    do {
        hasID = false;
        genRandomID(id, 13);
        for (string str : fileNames){
            if (ifStringHasSubstring(str, string(id))) hasID = true;
        }
    } while (hasID);

    return string(id);
}

bool SellerDataHandler::checkIfSellerNameExists(string sellerName)
{
    vector<SellerAccount> sellerAccts = getListOfSellerAccounts();
    for (SellerAccount sellerAcct : sellerAccts){
        if (sellerName == sellerAcct.getSellerName()) return true;
    }
    return false;
}

vector<SellerAccount> SellerDataHandler::getListOfSellerAccounts()
{
    vector<SellerAccount> sellerAccts;
    vector<string> accountFiles = getListOfFilesFromDirec(DataHandler::CHADA_DATABASE + "accounts/");
    for (string fileName : accountFiles){
        if (fileName.substr(0, 6) == "SELLER"){
            ifstream infile;
            infile.open((DataHandler::CHADA_DATABASE + "accounts/" + fileName).data(), ios::in);
            if (infile.is_open()){
                SellerAccount sellerAccount;

                string sellerName;
                float score;
                string accountID;
                string sellerID;
                float balance;
                string cardNum;
                string expiryDate;
                string cvc;
                vector<string> itemIDList;
                Address *billingAddress = new Address();

                getline(infile >> ws, sellerName);
                removeSubstring(sellerName, "Seller Name:");

                if (sellerName.empty()) return sellerAccts;

                string temp;
                getline(infile >> ws, temp);
                removeSubstring(temp, "Seller Score:");
                score = stof(temp);

                getline(infile >> ws, accountID);
                removeSubstring(accountID, "Account ID:");
                getline(infile >> ws, sellerID);
                removeSubstring(sellerID, "Seller ID:");

                getline(infile >> ws, temp);
                removeSubstring(temp, "Balance:");
                balance = stof(temp);

                getline(infile >> ws, cardNum);
                removeSubstring(cardNum, "Card Number:");
                getline(infile >> ws, expiryDate);
                removeSubstring(expiryDate, "Expiry Date:");
                getline(infile >> ws, cvc);
                removeSubstring(cvc, "CVC:");

                string itemListStr;
                getline(infile >> ws, itemListStr);
                removeSubstring(itemListStr, "List of Item ID:");
                while (itemListStr.length() != 0){
                    string itemID = substringAtPos(itemListStr, 0, ',');
                    itemIDList.push_back(itemID);
                    removeSubstring(itemListStr, itemID + ",");
                }

                string address1, address2, townOrCity, region;
                getline(infile >> ws, address1);
                removeSubstring(address1, "Address 1:");
                getline(infile >> ws, address2);
                removeSubstring(address2, "Address 2:");
                getline(infile >> ws, townOrCity);
                removeSubstring(townOrCity, "Town/City:");
                getline(infile >> ws, region);
                removeSubstring(region, "Region:");

                billingAddress->address1 = address1;
                billingAddress->address2 = address2;
                billingAddress->townOrCity = townOrCity;
                billingAddress->region = region;

                sellerAccount.setSellerName(sellerName);
                sellerAccount.setScore(score);
                sellerAccount.setAccountID(accountID);
                sellerAccount.setSellerID(sellerID);
                sellerAccount.setBalance(balance);
                sellerAccount.setCardNum(cardNum);
                sellerAccount.setExpiryDate(expiryDate);
                sellerAccount.setCvc(cvc);
                sellerAccount.setItemIDList(itemIDList);
                sellerAccount.setBillingAddress(billingAddress);

                sellerAccts.push_back(sellerAccount);
            }
            else {
                cerr << "Error opening seller account file." << endl;
                exit(1);
            }
        }
    }

    return sellerAccts;
}

SellerDataHandler::SellerDataHandler()
{

}


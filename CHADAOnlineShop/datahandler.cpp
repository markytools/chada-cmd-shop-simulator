#include "datahandler.h"
#include "utils.h"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include "account.h"
using namespace std;

//Replace with the 'CHADA Database' directory with the '/' at the end
const string DataHandler::CHADA_DATABASE = "C:/DIRECTORY/OF/THE/CHADADATAB/.../CHADA Database/";

Account *DataHandler::getLoadedAcct() const
{
    return loadedAcct;
}

void DataHandler::setLoadedAcct(Account *loadedAcct)
{
    this->loadedAcct = loadedAcct;
}


ItemDataHandler *DataHandler::getItemDataHandler() const
{
    return itemDataHandler;
}


SellerDataHandler *DataHandler::getSellerDataHandler() const
{
    return sellerDataHandler;
}

void DataHandler::getSingleAcctInfo(Account* &account, ifstream &infile)
{
    string accountID;
    string accountName;
    string email;
    string password;
    string firstName;
    char middleInitial;
    string lastName;
    string contactNo;
    Address shippingAddress;

    getline(infile >> ws, accountID);
    removeSubstring(accountID, "Account ID:");
    getline(infile >> ws, accountName);
    removeSubstring(accountName, "Username:");
    getline(infile >> ws, email);
    removeSubstring(email, "Email:");
    getline(infile >> ws, password);
    removeSubstring(password, "Password:");
    getline(infile >> ws, firstName);
    removeSubstring(firstName, "First Name:");

    string miStr;
    getline(infile >> ws, miStr);
    removeSubstring(miStr, "Middle Initial:");
    middleInitial = miStr[0];

    getline(infile >> ws, lastName);
    removeSubstring(lastName, "Last Name:");
    getline(infile >> ws, contactNo);
    removeSubstring(contactNo, "Contact No.:");

    string address1, address2, townOrCity, region;
    getline(infile >> ws, address1);
    removeSubstring(address1, "Address 1:");
    getline(infile >> ws, address2);
    removeSubstring(address2, "Address 2:");
    getline(infile >> ws, townOrCity);
    removeSubstring(townOrCity, "Town/City:");
    getline(infile >> ws, region);
    removeSubstring(region, "Region:");

    shippingAddress.address1 = address1;
    shippingAddress.address2 = address2;
    shippingAddress.townOrCity = townOrCity;
    shippingAddress.region = region;

    account->permitFieldSettings("123sasad3SAD!!#!!sad$#");
    account->setFields(accountID, accountName, email, password, firstName, middleInitial, lastName, contactNo, shippingAddress);
}

void DataHandler::setLoadedAcct(string email)
{
    vector<string> accountFiles = getListOfFilesFromDirec(CHADA_DATABASE + "/accounts/");
    for (int i = 0; i < accountFiles.size(); i++){
        ifstream infile;
        infile.open((CHADA_DATABASE + "accounts/" + accountFiles.at(i)).data(), ios::in);
        if (infile.is_open()){
            Account *account = new Account();
            getSingleAcctInfo(account, infile);
            if (account->getEmail() == email){
                loadedAcct = new Account(*account);
                infile.close();
                break;
            }
        }
        else {
            cerr << "Error opening account file." << endl;
            exit(1);
        }
        infile.close();
    }
}

bool DataHandler::checkIfAccountIDExists(string accountID)
{
    vector<string> accountFiles = getListOfFilesFromDirec(CHADA_DATABASE + "/accounts/");
    for (int i = 0; i < accountFiles.size(); i++){
        string fileAccountID;
        ifstream infile;
        infile.open((CHADA_DATABASE + "accounts/" + accountFiles.at(i)).data(), ios::in);
        if (infile.is_open()){
            getline(infile >> ws, fileAccountID);
            removeSubstring(fileAccountID, "Account ID:");
        }
        else {
            cerr << "Error opening account file." << endl;
            exit(1);
        }
        infile.close();
        if (fileAccountID == accountID) return true;
    }
    return false;
}

bool DataHandler::checkIfUsernameExists(string username)
{
    vector<string> accountFiles = getListOfFilesFromDirec(CHADA_DATABASE + "/accounts/");
    for (int i = 0; i < accountFiles.size(); i++){
        string fileUsername;
        ifstream infile;
        infile.open((CHADA_DATABASE + "accounts/" + accountFiles.at(i)).data(), ios::in);
        if (infile.is_open()){
            for (int i = 0; i < 2; i++){
                getline(infile >> ws, fileUsername);
            }
            removeSubstring(fileUsername, "Username:");
        }
        else {
            cerr << "Error opening account file." << endl;
            exit(1);
        }
        infile.close();
        if (fileUsername == username) return true;
    }
    return false;
}

bool DataHandler::checkIfEmailExists(string email)
{
    vector<string> accountFiles = getListOfFilesFromDirec(CHADA_DATABASE + "/accounts/");
    for (int i = 0; i < accountFiles.size(); i++){
        string fileEmail;
        ifstream infile;
        infile.open((CHADA_DATABASE + "accounts/" + accountFiles.at(i)).data(), ios::in);
        if (infile.is_open()){
            for (int i = 0; i < 3; i++){
                getline(infile >> ws, fileEmail);
            }
            removeSubstring(fileEmail, "Email:");
        }
        else {
            cerr << "Error opening account file." << endl;
            exit(1);
        }
        infile.close();
        if (fileEmail == email) return true;
    }
    return false;
}

DataHandler::DataHandler()
{
    itemDataHandler = new ItemDataHandler();
    itemDataHandler->setDataHandler(this);
    sellerDataHandler = new SellerDataHandler();
}


#include "mastercard.h"
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

AcctInfo Mastercard::getMatchedAccount(string acctNumber)
{
    AcctInfo acctInfo;
    acctInfo.name == "";
    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        while (1){
            AcctInfo infoExtracted = getSingleInfos(infile);
            if (infoExtracted.acctNum == acctNumber){
                acctInfo = infoExtracted;
                break;
            }
            if (infile.eof()) break;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    return acctInfo;
}

AcctInfo Mastercard::getSingleInfos(ifstream &infile)
{
    AcctInfo acctInfoData;

    infile.ignore(1000, ':');
    char name[100];
    infile.ignore(1000, '\n');
    infile.get(name, 100, ';');
    acctInfoData.name = name;

    infile.ignore(1000, ';');
    char address[100];
    infile.ignore(1000, '\n');
    infile.get(address, 100, ';');
    acctInfoData.address = address;

    infile.ignore(1000, ';');
    char acctNum[100];
    infile.ignore(1000, '\n');
    infile.get(acctNum, 100, ';');
    acctInfoData.acctNum = acctNum;

    infile.ignore(1000, ';');
    char balance[100];
    infile.ignore(1000, '\n');
    infile.get(balance, 100, ';');
    acctInfoData.balance = strtof(balance, NULL);

    infile.ignore(1000, ';');
    char pin[100];
    infile.ignore(1000, '\n');
    infile.get(pin, 100, ';');
    acctInfoData.pin = pin;

    return acctInfoData;
}

int Mastercard::getTotalAccounts()
{
    int totalAccounts = 0;
    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        while (1){
            getSingleInfos(infile);
            if (infile.eof()) break;
            totalAccounts++;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    return totalAccounts;
}

void Mastercard::setBalance(string acctNum, float bal){
    int totalAccts = getTotalAccounts();
    string accountInfos[totalAccts];

    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        for (int i = 0; i < totalAccts; i++){
            AcctInfo infoExtracted = getSingleInfos(infile);
            ostringstream strs;
            if (infoExtracted.acctNum == acctNum){
                infoExtracted.balance = bal;
            }
            strs << infoExtracted.balance;
            string strBal = strs.str();
            string accountInfo =
                    string("\n") +
                    string("*AcctInfo:\n") +
                    infoExtracted.name + string(";\n") +
                    infoExtracted.address + string(";\n") +
                    infoExtracted.acctNum + string(";\n") +
                    strBal + string(";\n") +
                    infoExtracted.pin + string(";\n");
            accountInfos[i] = accountInfo;
            if (infile.eof()) break;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    clearFileContents(filename);
    for (int i = 0; i < totalAccts; i++){
        writeStringToFile(filename, accountInfos[i]);
    }
}

void Mastercard::clearFileContents(string filename)
{
    ofstream ofs;
    ofs.open(filename.data(), std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void Mastercard::writeStringToFile(string filename, string data)
{
    ofstream outfile;
    outfile.open(filename.data(), ios::app);
    if (outfile.is_open()){
        outfile << data;
    } else {
        cerr << "unable to open file";
        exit(1);
    }
    outfile.close();
}

MastercardInfo Mastercard::getSingleMCInfo(ifstream &infile)
{
    MastercardInfo mcInfo;
    mcInfo.acctNumber = "";

    string lineInfo;
    getline(infile >> ws, lineInfo);
    if (lineInfo.length() != 0){

        string acctNum = substringAtPos(lineInfo.substr(0, 20), 0, ' ');
        string cardNum = substringAtPos(lineInfo.substr(20, 20), 0, ' ');
        string expiryDate = substringAtPos(lineInfo.substr(40, 10), 0, ' ');
        string cvc = substringAtPos(lineInfo.substr(50, 3), 0, ' ');

        mcInfo.acctNumber = acctNum;
        mcInfo.cardNumber = cardNum;
        mcInfo.expiryDate = expiryDate;
        mcInfo.cvc = cvc;
    }

    return mcInfo;
}

void Mastercard::setCurrentAccount()
{
    acctInfo = getMatchedAccount(msInfo.acctNumber);
}

bool Mastercard::checkIfCardNumExists(string cardNum)
{
    string directory = MC_DIRECTORY + "mastercardLists.mc";
    if (!fileExists(directory)) createFile(directory);

    ifstream infile;
    infile.open(directory.data(), ios::in);
    if (infile.is_open()){
        while (!infile.eof()){
            MastercardInfo mcInfo = getSingleMCInfo(infile);
            if (mcInfo.cardNumber == cardNum){
                infile.close();
                return true;
            }
        }
    }
    else {
        cerr << "Unable to open Mastercard file." << endl;
        exit(1);
    }
    infile.close();
    return false;
}

//Returns true if card was found, then sets it as the current card. False otherwise.
bool Mastercard::setCurrentMastercard()
{
    string directory = MC_DIRECTORY + "mastercardLists.mc";
    if (!fileExists(directory)) createFile(directory);

    string cardNum, expiryDate, cvc;
    string month, year;
    cout << "Enter Card Number: ";
    getline(cin >> ws, cardNum);
    cout << "Enter Expiry Month: ";
    getline(cin >> ws, month);
    cout << "Enter Expiry Year: ";
    getline(cin >> ws, year);
    expiryDate = month + "/" + year;
    cout << "Enter Card CVC: ";
    getline(cin >> ws, cvc);

    ifstream infile;
    infile.open(directory.data(), ios::in);
    if (infile.is_open()){
        while (!infile.eof()){
            MastercardInfo msInfo = getSingleMCInfo(infile);
            if (msInfo.acctNumber != ""){
                if (cardNum == msInfo.cardNumber &&
                        expiryDate == msInfo.expiryDate &&
                        cvc == msInfo.cvc){
                    if (!cardExpired(msInfo.expiryDate)){
                        this->msInfo = msInfo;
                        setCurrentAccount();
                        infile.close();
                        return true;
                    }
                }
            }
        }
    }
    infile.close();
    return false;
}

void Mastercard::setCard(string cardNumber, string expiryDate, string cvc)
{
    string directory = MC_DIRECTORY + "mastercardLists.mc";
    if (!fileExists(directory)) createFile(directory);
    ifstream infile;
    infile.open(directory.data(), ios::in);
    if (infile.is_open()){
        while (!infile.eof()){
            MastercardInfo msInfo = getSingleMCInfo(infile);
            if (msInfo.acctNumber != ""){
                if (cardNumber == msInfo.cardNumber &&
                        expiryDate == msInfo.expiryDate &&
                        cvc == msInfo.cvc){
                    if (!cardExpired(msInfo.expiryDate)){
                        this->msInfo = msInfo;
                        setCurrentAccount();
                    }
                }
            }
        }
    }
    else {
        cerr << "Unable to open file." << endl;
        exit(1);
    }
    infile.close();
}

bool Mastercard::subtractFromCard(float amount)
{
    if (amount <= 0 || acctInfo.balance - amount < 0) cout << "There was a problem during transaction. "
                                                              "It might be that the card has insufficient balance, or entered amount is invalid." << endl;
    else {
        setBalance(acctInfo.acctNum, acctInfo.balance - amount);
        cout << "Transaction Success." << endl;
        return true;
    }
    return false;
}

bool Mastercard::addAmount(float amount)
{
    if (amount <= 0) cout << "Invalid amount to add." << endl;
    else {
        setBalance(acctInfo.acctNum, acctInfo.balance + amount);
        cout << "Transaction Success." << endl;
        return true;
    }
    return false;
}

string Mastercard::getCardNumber()
{
    return msInfo.cardNumber;
}

string Mastercard::getExpiryDate()
{
    return msInfo.expiryDate;
}

string Mastercard::getCVC()
{
    return msInfo.cvc;
}

string Mastercard::getCardType()
{
    return "MASTERCARD";
}

Mastercard::Mastercard()
{

}


bool Mastercard::stringIsEmptyOrHasOnlyWS(string str)
{
    return ((str.find_first_not_of(' ') != std::string::npos) || str.size() == 0);
}


bool Mastercard::fileExists(string name)
{
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}


string Mastercard::substringAtPos(string str, int pos, char delim)
{
    string finalStr = "";
    char strChars[str.length()];
    strcpy(strChars, str.c_str());
    for (int i = pos; i < str.length(); i++){
        if (strChars[i] == delim) break;
        finalStr += convertCharToString(strChars[i]);
    }
    return finalStr;
}


void Mastercard::createFile(string filename)
{
    ofstream ofs;
    ofs.open(filename.data(), std::ofstream::out);
    ofs.close();
}


string Mastercard::convertCharToString(char c)
{
    stringstream ss;
    string target;
    ss << c;
    ss >> target;
    return target;
}

bool Mastercard::cardExpired(string expiryDate){
    time_t theTime = time(NULL);
    struct tm * aTime = localtime(&theTime);

    int month = aTime -> tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    int year = aTime -> tm_year + 1900; // Year is # years since 1900

    ostringstream strs2;
    strs2 << month;
    string strMonth = strs2.str();

    ostringstream strs3;
    strs3 << year;
    string strYear = strs3.str();

    string cardMonth = substringAtPos(expiryDate, 0, '/');
    string cardYear = substringAtPos(expiryDate, 3, '/');

    if (cardYear < strYear) return true;
    else if (cardYear == strYear) if (cardMonth <= strMonth) return true;
    return false;
}


#ifndef MASTERCARD_H
#define MASTERCARD_H

#include <iostream>
#include <fstream>
using namespace std;

const string MS_CONFIG_MSG_1 = "Card successfully set";
const string MS_CONFIG_MSG_2 = "Card expired";
const string MS_CONFIG_MSG_3 = "Invalid card.";

struct AcctInfo {
    string name;
    string address;
    string acctNum;
    float balance;
    string pin;
};

struct MastercardInfo {
    string acctNumber;
    string cardNumber;
    string expiryDate;
    string cvc;
};

class Mastercard
{
private:
    const string MC_DIRECTORY = "D:/Documents/QT Project/TyBankOOD/mastercard/";
    const string ACCT_FILE = "D:/Documents/QT Project/TyBankOOD/acct.lst";
    const string cardType = "MASTERCARD";

    AcctInfo acctInfo;
    MastercardInfo msInfo;

    AcctInfo getSingleInfos(ifstream &infile);
    AcctInfo getMatchedAccount(string acctNumber);
    bool confirmCard(string num, string expiryDate, string cvc);
    int getTotalAccounts();
    void setBalance(string acctNum, float bal);
    string getAcctNum(string cardNum);
    void clearFileContents(string filename);
    void writeStringToFile(string filename, string data);
    bool checkIfCardNumExists(string cardNum);
    MastercardInfo getSingleMCInfo(ifstream &infile);
    void setCurrentAccount();

    bool stringIsEmptyOrHasOnlyWS(string str);
    bool fileExists(string name);
    string substringAtPos(string str, int pos, char delim);
    void createFile(string filename);
    string convertCharToString(char c);
    bool cardExpired(string expiryDate);
public:
    bool setCurrentMastercard();
    bool subtractFromCard(float amount);
    bool addAmount(float amount);
    string getCardNumber();
    string getExpiryDate();
    string getCVC();
    string getCardType();
    void setCard(string cardNumber, string expiryDate, string cvc);
    Mastercard();
};


#endif // MASTERCARD_H

#include "account.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "utils.h"
#include "datahandler.h"

string Account::getAccountID() const
{
    return accountID;
}

string Account::getAccountName() const
{
    return accountName;
}

string Account::getEmail() const
{
    return email;
}

string Account::getPassword() const
{
    return password;
}

string Account::getFirstName() const
{
    return firstName;
}

char Account::getMiddleInitial() const
{
    return middleInitial;
}

string Account::getLastName() const
{
    return lastName;
}

string Account::getContactNo() const
{
    return contactNo;
}

Address Account::getShippingAddress() const
{
    return shippingAddress;
}
void Account::flushAccount()
{
    ofstream outfile;
    outfile.open((DataHandler::CHADA_DATABASE + "accounts/" + "ACCOUNT" + accountID + ".acct").data(), ios::out);
    if (outfile.is_open()){
        outfile << "Account ID:" << accountID << endl;
        outfile << "Username:" << accountName << endl;
        outfile << "Email:" << email << endl;
        outfile << "Password:" << password << endl;
        outfile << "First Name:" << firstName << endl;
        outfile << "Middle Initial:" << middleInitial << endl;
        outfile << "Last Name:" << lastName << endl;
        outfile << "Contact No.:" << contactNo << endl;
        outfile << "Address 1:" << shippingAddress.address1 << endl;
        outfile << "Address 2:" << shippingAddress.address2 << endl;
        outfile << "Town/City:" << shippingAddress.townOrCity << endl;
        outfile << "Region:" << shippingAddress.region << endl;
    }
    else {
        cerr << "Unable to create account file." << endl;
        exit(1);
    }
    outfile.close();
}

Account *Account::flushAndReturnAcct()
{
    ofstream outfile;
    outfile.open((DataHandler::CHADA_DATABASE + "accounts/" + "ACCOUNT" + accountID + ".acct").data(), ios::out);
    if (outfile.is_open()){
        outfile << "Account ID:" << accountID << endl;
        outfile << "Username:" << accountName << endl;
        outfile << "Email:" << email << endl;
        outfile << "Password:" << password << endl;
        outfile << "First Name:" << firstName << endl;
        outfile << "Middle Initial:" << middleInitial << endl;
        outfile << "Last Name:" << lastName << endl;
        outfile << "Contact No.:" << contactNo << endl;
        outfile << "Address 1:" << shippingAddress.address1 << endl;
        outfile << "Address 2:" << shippingAddress.address2 << endl;
        outfile << "Town/City:" << shippingAddress.townOrCity << endl;
        outfile << "Region:" << shippingAddress.region << endl;
    }
    else {
        cerr << "Unable to create account file." << endl;
        exit(1);
    }
    outfile.close();
    return this;
}

void Account::setFields(string accountID, string accountName, string email, string password, string firstName, char middleInitial,
                        string lastName, string contactNo, Address shippingAddress)
{
    if (code == passcode){
        this->accountID = accountID;
        this->accountName = accountName;
        this->email = email;
        this->password = password;
        this->firstName = firstName;
        this->middleInitial = middleInitial;
        this->lastName = lastName;
        this->accountName = accountName;
        this->contactNo = contactNo;
        this->shippingAddress = shippingAddress;
    }
    srand(time(NULL));
    code = rand() % 131231232123;
}

void Account::permitFieldSettings(string code)
{
    this->code = code;
}

void Account::signUp()
{

}

Account::Account()
{

}


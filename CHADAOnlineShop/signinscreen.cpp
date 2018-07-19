#include "signinscreen.h"
#include <iostream>
#include <string>
#include <fstream>
#include "utils.h"
#include "chadaonlineshopdisplay.h"
#include "selections.h"
#include "account.h"
using namespace std;

SignInScreen::SignInScreen()
{

}

SignInScreen::SignInScreen(DataHandler *dataHandler, SystemManager *sysManager)
{
    this->dataHandler = dataHandler;
    this->sysManager = sysManager;
}

string SignInScreen::generateAccountID()
{
    char *accountNum;
    bool finish = false;
    do {
        finish = true;
        accountNum = new char[13];
        genRandomID(accountNum, 13);
        vector<string> fileNames = getListOfFilesFromDirec(DataHandler::CHADA_DATABASE + "accounts/");
        for (int i = 0; i < fileNames.size(); i++){
            if (ifStringHasSubstring(fileNames.at(i), string(accountNum))) finish = false;
        }
    } while(!finish);
    return string(accountNum);
}

bool SignInScreen::checkIfEmailAndPasswordMatch(string email, string password)
{
    vector<string> accountFiles = getListOfFilesFromDirec(DataHandler::CHADA_DATABASE + "accounts/");
    for (int i = 0; i < accountFiles.size(); i++){
        ifstream infile;
        infile.open((DataHandler::CHADA_DATABASE + "accounts/" + accountFiles.at(i)).data(), ios::in);
        if (infile.is_open()){
            string fileEmail, filePassword;
            for (int i = 0; i < 3; i++){
                getline(infile >> ws, fileEmail);
            }
            removeSubstring(fileEmail, "Email:");
            if (email == fileEmail){
                getline(infile >> ws, filePassword);
                removeSubstring(filePassword, "Password:");
                if (password == filePassword) return true;
            }
        }
        else {
            cerr << "Error opening account file." << endl;
            exit(1);
        }
        infile.close();
    }
    return false;
}

void SignInScreen::setSSState(const SignScreenState &value)
{
    sSState = value;
}

void SignInScreen::displayScreen()
{
    switch (sSState){
    case NORMAL: {
        clearScreen();
        Selections wSelections;
        wSelections.setSInputType(NUMBERS);
        wSelections.putNumChoice("Sign In");
        wSelections.putNumChoice("Sign Up");
        wSelections.putNumChoice("Exit");
        cout << TEXT_ART << endl;
        cout << WELCOME_DISPLAY << endl;
        wSelections.displaySelections();
        string selectionStr = wSelections.select("What do you want to do? ");
        int selection = stoi(selectionStr);
        switch (selection){
        case 1:{
            sSState = SIGN_IN;
            signInCount = 0;
        }; break;
        case 2: sSState = SIGN_UP; break;
        case 3: sysManager->setCurrentScreen(NONE); break;
        default: break;
        }
    }; break;
    case SIGN_IN: {
        if (signInCount == 0){
            clearScreen();
            cout << "SIGN IN" << endl;
        }

        string email, password;
        cout << "Email: ";
        getline(cin >> ws, email);
        cout << "Password: ";
        password = acquirePassword();
        cout << endl;
        if (checkIfEmailAndPasswordMatch(email, password)){
//            renderLoadingAnimTxt();
            dataHandler->setLoadedAcct(email);
            sysManager->setCurrentScreen(SHOP_SCREEN);
            sSState = NORMAL;
        }
        else cout << "Email and password do not match." << endl;
        signInCount++;
    }; break;
    case SIGN_UP: {
        clearScreen();
        cout << "SIGN UP" << endl;
        cout << "Please fill in the following information to create a CHADA account." << endl;

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

        accountID = generateAccountID();
        account.setFields(accountID, accountName, email, password, firstName, middleInitial, lastName, contactNo, shippingAddress);
        account.flushAccount();
        cout << "You have successfully create a CHADA account. You can now use your account to sign in." << endl;
        enterToContinue();
        sSState = NORMAL;
    }; break;
    default: break;
    }
}


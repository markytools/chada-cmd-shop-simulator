#ifndef SIGNINSCREEN_H
#define SIGNINSCREEN_H

#include "account.h"
#include "systemmanager.h"
#include "datahandler.h"
#include <iostream>
using namespace std;

class DataHandler;
class SystemManager;

enum SignScreenState {
    NORMAL, SIGN_IN, SIGN_UP
};

class SignInScreen : public Screen
{
    int signInCount;

    DataHandler *dataHandler;
    SystemManager *sysManager;
    SignScreenState sSState;

    string generateAccountID();
    bool checkIfEmailAndPasswordMatch(string email, string password);
public:
    void setSSState(const SignScreenState &value);
    void displayScreen();
    SignInScreen();
    SignInScreen(DataHandler *dataHandler, SystemManager *sysManager);
};

#endif // SIGNINSCREEN_H

#ifndef CHADAONLINESHOPDISPLAY_H
#define CHADAONLINESHOPDISPLAY_H

#include "screen.h"
#include "datahandler.h"
#include "signinscreen.h"
#include "systemmanager.h"
#include "shopscreen.h"
#include "sellerscreen.h"

class Screen;
class SignInScreen;
class DataHandler;
class ShopScreen;
class SellerScreen;

class CHADAOnlineShopDisplay
{
    Screen *currentScreen;
    SignInScreen *signInScreen;
    ShopScreen *shopScreen;
    SellerScreen *sellerScreen;

    DataHandler *dataHandler;
    SystemManager *sysManager;

    void initScreens();
    void updateScreen();
public:
    void displayCurrentScreen();
    CHADAOnlineShopDisplay();
};

#endif // CHADAONLINESHOPDISPLAY_H

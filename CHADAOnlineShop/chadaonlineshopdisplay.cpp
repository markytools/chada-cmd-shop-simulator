#include "chadaonlineshopdisplay.h"
#include <iostream>
using namespace std;

void CHADAOnlineShopDisplay::initScreens()
{
    dataHandler = new DataHandler();
    sysManager = new SystemManager();
    signInScreen = new SignInScreen(dataHandler, sysManager);
    signInScreen->setSSState(NORMAL);
    shopScreen = new ShopScreen(dataHandler, sysManager);
    shopScreen->setShopScreenState(HOME);
    sellerScreen = new SellerScreen(dataHandler, sysManager);

    currentScreen = signInScreen;
    sysManager->setCurrentScreen(SIGN_IN_SCREEN);
}

void CHADAOnlineShopDisplay::updateScreen()
{
    switch (sysManager->getScreenID()){
    case NONE: break;
    case SIGN_IN_SCREEN: currentScreen = signInScreen; break;
    case SHOP_SCREEN: currentScreen = shopScreen; break;
    case SELLER_SCREEN: currentScreen = sellerScreen; break;
    default: break;
    }
}

void CHADAOnlineShopDisplay::displayCurrentScreen()
{
    while (sysManager->getScreenID() != NONE){
        updateScreen();
        currentScreen->displayScreen();
    }
}

CHADAOnlineShopDisplay::CHADAOnlineShopDisplay()
{
    initScreens();
}


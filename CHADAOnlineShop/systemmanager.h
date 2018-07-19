#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

enum ScreenID {
    NONE, SIGN_IN_SCREEN, SHOP_SCREEN, SELLER_SCREEN
};

class SystemManager
{
    ScreenID screenID;
public:
    void setCurrentScreen(ScreenID screenID);
    ScreenID getScreenID() const;
    SystemManager();
};

#endif // SYSTEMMANAGER_H

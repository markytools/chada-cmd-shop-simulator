#include "systemmanager.h"


ScreenID SystemManager::getScreenID() const
{
    return screenID;
}

void SystemManager::setCurrentScreen(ScreenID screenID)
{
    this->screenID = screenID;
}

SystemManager::SystemManager()
{

}

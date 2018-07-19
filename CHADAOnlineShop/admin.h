#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "datahandler.h"
using namespace std;

class DataHandler;

class Admin
{
    DataHandler *dataHandler;
    string adminID;
    bool checkIfCorrectAdminID(string adminID);
public:
    bool displayAdmin(string adminID);
    Admin(DataHandler *dataHandler);
};

#endif // ADMIN_H

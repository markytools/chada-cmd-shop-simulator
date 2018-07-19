#include "admin.h"
#include <fstream>
#include "utils.h"
#include "datahandler.h"
#include <iomanip>
#include "selections.h"
#include "windows.h"
#include <string>

//5ZY4HSUIYKHTP

bool Admin::checkIfCorrectAdminID(string adminID)
{
    ifstream infile;
    string direc = DataHandler::CHADA_DATABASE + "system/admin/admin.chada";
    infile.open(direc.data(), ios::in);
    if (infile.is_open()){
        string text;
        infile >> text;
        if (text == adminID){
            infile.close();
            return true;
        }
    }
    else {
        cerr << "Error opening admin file." << endl;
        exit(1);
    }
    infile.close();
    return true;
}

bool Admin::displayAdmin(string admin)
{
    clearScreen();
    if (checkIfCorrectAdminID(admin)){
        bool exit = false;
        while (!exit){
            vector<Item> items = dataHandler->getItemDataHandler()->getAllItems();
            vector<Item> pendingItems;
            for (Item item : items){
                if (item.getCategory().status == PENDING_STATUS) pendingItems.push_back(item);
            }

            cout << "\t\t---LIST OF PENDING ITEMS---" << endl;
            cout << left
                 << setw(5) << "NO."
                 << setw(50) << "ITEM NAME"
                 << setw(20) << "STATUS" << endl;

            for (int i = 0; i < pendingItems.size(); i++){
                Item item = pendingItems[i];
                cout << left
                     << setw(5) << i + 1
                     << setw(50) << limitStringSize(item.getItemName(), 45)
                     << setw(20) << PENDING_STATUS << endl;
            }
            if (pendingItems.size() == 0) cout << "No pending items." << endl;

            cout << endl;
            cout << "Hello, Admin " << dataHandler->getLoadedAcct()->getFirstName() << " " << dataHandler->getLoadedAcct()->getLastName() << "!";
            cout << endl;

            Selections selections;
            selections.setSInputType(NUMBERS);
            selections.putNumChoice("Approve an Item");
            selections.putNumChoice("Deny an Item");
            selections.putNumChoice("Preview Item Picture/s");
            selections.putNumChoice("Back");
            selections.displaySelections();
            string selection = selections.select("---->> ");
            int num = stoi(selection);
            switch (num){
            case 1: {
                if (pendingItems.size() != 0){
                    int num;
                    do {
                        cout << "Type the Item number to APPROVE: ";
                        cin >> num;
                        if (num >= 1 && num <= pendingItems.size()) break;
                        cout << "Invalid Input" << endl;
                    } while (1);
                    Item item = pendingItems[num - 1];
                    Category category = item.getCategory();
                    category.status = ON_SALE_STATUS;
                    item.setCategory(category);
                    ItemInfo itemInfo = dataHandler->getItemDataHandler()->getItemInfo();
                    itemInfo.flushItemInfo(new Item(item), itemInfo.getDefaultImages(item.getItemID()));
                }
                else cout << "No pending items." << endl;
            }; break;
            case 2: {
                if (pendingItems.size() != 0){
                    int num;
                    do {
                        cout << "Type the Item number to DENY: ";
                        cin >> num;
                        if (num >= 1 && num <= pendingItems.size()) break;
                        cout << "Invalid Input" << endl;
                    } while (1);
                    Item item = pendingItems[num - 1];
                    Category category = item.getCategory();
                    category.status = ON_SALE_STATUS;
                    item.setCategory(category);
                    ItemInfo itemInfo = dataHandler->getItemDataHandler()->getItemInfo();
                    itemInfo.flushItemInfo(new Item(item), itemInfo.getDefaultImages(item.getItemID()));
                }
                else cout << "No pending items." << endl;
            }; break;
            case 3: {
                if (pendingItems.size() != 0){
                    int num;
                    do {
                        cout << "Type the Item number to preview its image: ";
                        cin >> num;
                        if (num >= 1 && num <= pendingItems.size()) break;
                        cout << "Invalid Input" << endl;
                    } while (1);
                    Item item = pendingItems[num - 1];
                    string imageDirectory = DataHandler::CHADA_DATABASE + "items/" + item.getItemID() + "/images/0.jpg";
                    ShellExecuteA(0, 0, imageDirectory.c_str(), 0, 0 , SW_SHOW );
                }
                else cout << "No pending items." << endl;
            }; break;
            case 4: {
                exit = true;
            }; break;
            default: break;
            }

            clearScreen();
        }
    }
    clearScreen();
}

Admin::Admin(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
}


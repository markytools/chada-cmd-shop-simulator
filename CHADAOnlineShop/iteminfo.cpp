#include "iteminfo.h"
#include <fstream>
#include <string>
#include "datahandler.h"
#include <windows.h>
#include "item.h"
#include "utils.h"
#include "stdio.h"

//only updates one deletion
void ItemInfo::updateImageNames(string directory)
{
    vector<string> files = getListOfFilesFromDirec(directory);
    int takes = 0;
    while (takes != files.size()){
        string targetPicName = directory + numberToString(takes, 0) + ".jpg";
        if (fileExists(targetPicName)){
            takes++;
            continue;
        }
        else {
            for (int i = takes; i < files.size(); i++){
                string formerFileName = directory + numberToString(i + 1, 0) + ".jpg";
                string laterFileName = directory + numberToString(i, 0) + ".jpg";
                rename(formerFileName.data(), laterFileName.data());
            }
            break;
        }
    }
}

vector<ImageReplacementInfo> ItemInfo::getDefaultImages(string itemID)
{
    vector<ImageReplacementInfo> imageInfos;
    string directory = DataHandler::CHADA_DATABASE + "items/" + itemID + "/images/";
    vector<string> fileNames = getListOfFilesFromDirec(directory);
    for (int i = 0; i < fileNames.size(); i++){
        ImageReplacementInfo iRInfo;
        iRInfo.code = i;
        iRInfo.imageDirec = directory + numberToString(i, 0) + ".jpg";
        imageInfos.push_back(iRInfo);
    }
    return imageInfos;
}

void ItemInfo::flushItemInfo(Item *item, vector<ImageReplacementInfo> imageReplacements)
{
    ofstream infoFile1, infoFile2, infoFile3, reviewsFile;

    infoFile1.open((DataHandler::CHADA_DATABASE + "items/" + item->getItemID() + "/info1.chada").data(), ios::out);
    if (infoFile1.is_open()){
        infoFile1 << "Item Name:" << item->getItemName() << endl;
        infoFile1 << "Item Condition:" << item->getItemCondition() << endl;
        infoFile1 << "Original Price:" << item->getOriginalPrice() << endl;
        infoFile1 << "Discounted Price:" << item->getDiscountedPrice() << endl;
        infoFile1 << "Postage:" << item->getPostage() << endl;
        infoFile1 << "Item Location:" << item->getItemLocation() << endl;
        infoFile1 << "Returns:" << item->getReturns() << endl;
        infoFile1 << "Item Description:" << item->getItemDescription() << endl;
        infoFile1 << "Item ID:" << item->getItemID() << endl;
        infoFile1 << "Seller ID:" << item->getSellerID() << endl;
        infoFile1 << "Rating:" << item->getRating() << endl;
        infoFile1 << "Stocks:" << item->getStocks() << endl;
    }
    else {
        cerr << "Unable to create info file 1." << endl;
        exit(1);
    }

    infoFile2.open((DataHandler::CHADA_DATABASE + "items/" + item->getItemID() + "/info2.chada").data(), ios::out);
    if (infoFile2.is_open()){
        infoFile2 << "Main Category:" << item->getCategory().mainCategory << endl;

        infoFile2 << "Sub Category:";
        for (int i = 0; i < item->getCategory().subCategory.size(); i++){
            infoFile2 << item->getCategory().subCategory[i] << ",";
        }
        infoFile2 << endl;
        infoFile2 << "Status:" << item->getCategory().status << endl;
        infoFile2 << "No. of Views:" << item->getCategory().noOfViews << endl;
    }
    else {
        cerr << "Unable to create info file 2." << endl;
        exit(1);
    }

    if (item->getCategory().status == "TEST ITEM"){
        infoFile3.open((DataHandler::CHADA_DATABASE + "items/" + item->getItemID() + "/info3.chada").data(), ios::out);
        if (infoFile3.is_open()){
            infoFile3 << "Username:" << item->getTestItemInfo().username << endl;
            infoFile3 << "Email Address:" << item->getTestItemInfo().email << endl;
            infoFile3 << "Contact No:" << item->getTestItemInfo().contactNo << endl;
        }
        else {
            cerr << "Unable to create info file 3." << endl;
            exit(1);
        }
    }

    reviewsFile.open((DataHandler::CHADA_DATABASE + "items/" + item->getItemID() + "/reviews.chada").data(), ios::out);
    if (reviewsFile.is_open()){
        for (int i = 0; i < item->getReviews().size(); i++){
            Reviews review = item->getReviews().at(i);
            reviewsFile << "Account ID:" << review.accountID << endl;
            reviewsFile << "Account Name:" << review.name << endl;
            reviewsFile << "Account Rating:" << review.rating << endl;
            reviewsFile << "Account Review:" << review.review << endl;
            reviewsFile << "Time Submitted:" << review.timeSubmitted << endl;
            reviewsFile << endl;
        }
    }
    else {
        cerr << "Unable to create review file." << endl;
        exit(1);
    }

    infoFile1.close();
    infoFile2.close();
    infoFile3.close();
    reviewsFile.close();

    string imageRootDirectory = DataHandler::CHADA_DATABASE + "items/" + item->getItemID() + "/images/";
    for (int i = 0; i < imageReplacements.size(); i++){
        ImageReplacementInfo iRInfo = imageReplacements[i];
        if (ifStringHasSubstring(iRInfo.imageDirec, imageRootDirectory)){
            if (iRInfo.code == -1){
                remove(iRInfo.imageDirec.c_str());
                updateImageNames(imageRootDirectory);
            }
            else continue;
        }
        else {
            if (iRInfo.code == -1){
                copyFileToPath(iRInfo.imageDirec, imageRootDirectory
                               + numberToString(getListOfFilesFromDirec(imageRootDirectory).size(), 0) + ".jpg");
            }
            else {
                copyFileToPath(iRInfo.imageDirec, imageRootDirectory + numberToString(iRInfo.code, 0) + ".jpg");
            }
        }
    }
}

ItemInfo::ItemInfo()
{

}

void ItemInfo::buyItem(Item item, int amount)
{
    int stockLeft = item.getStocks() - amount;

}


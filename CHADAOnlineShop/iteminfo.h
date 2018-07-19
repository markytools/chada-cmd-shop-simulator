#ifndef ITEMINFO_H
#define ITEMINFO_H

#include "item.h"

//-1 = new image = add
//-1 = same image = delete and rename
struct ImageReplacementInfo {
    string imageDirec;
    int code;
};

class ItemInfo
{
    void updateImageNames(string directory);
public:
    vector<ImageReplacementInfo> getDefaultImages(string itemID);
    void flushItemInfo(Item *item, vector<ImageReplacementInfo> imageReplacements);
    void buyItem(Item item, int amount);
    ItemInfo();
};

#endif // ITEMBUYER_H

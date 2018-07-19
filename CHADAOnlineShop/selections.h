#ifndef SELECTIONS_H
#define SELECTIONS_H

#include <map>
#include <ostream>
#include <vector>
using namespace std;

enum SelectionInputType {
    LETTERS, NUMBERS, BOTH
};

class Selections
{
    string adminStr = "P";
    SelectionInputType sInputType;
    vector<string> numList;
    vector<string> letterListA;
    vector<string> letterListB;
public:
    string numListTitle;
    string letterListATitle;
    string letterListBTitle;

    void displaySelections();
    void displaySelections(bool displayNums);
    string select(string selectionMsg);
    string specialSelect(string selectionMsg);
    void clearSelections();
    void putNumChoice(string choiceDesc);
    void putLetterChoiceA(string choiceDesc);
    void putLetterChoiceB(string choiceDesc);
    Selections();

    void setSInputType(const SelectionInputType &value);
};

#endif // SELECTIONS_H

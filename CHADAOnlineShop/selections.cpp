#include "selections.h"
#include "utils.h"
#include <iostream>
#include <string>
using namespace std;


void Selections::setSInputType(const SelectionInputType &value)
{
    sInputType = value;
}

void Selections::displaySelections()
{
    switch (sInputType){
    case NUMBERS: {
        if (numListTitle.size() != 0) cout << numListTitle << endl;
        for (int i = 0; i < numList.size(); i++){
            cout << i + 1 << " - " << numList.at(i) << endl;
        }
    }; break;
    case LETTERS: {
        if (letterListATitle.size() != 0) cout << letterListATitle << endl;
        for (int i = 0; i < letterListA.size(); i++){
            cout << (char)(i + 65) << " - " << letterListA.at(i) << endl;
        }
        cout << endl;
        if (letterListBTitle.size() != 0) cout << letterListBTitle << endl;
        for (int i = 0; i < letterListB.size(); i++){
            cout << (char)(i + 65 + letterListA.size()) << " - " << letterListB.at(i) << endl;
        }
    }; break;
    case BOTH: {
        if (numListTitle.size() != 0) cout << numListTitle << endl;
        for (int i = 0; i < numList.size(); i++){
            cout << i + 1 << " - " << numList.at(i) << endl;
        }
        cout << endl;
        if (letterListATitle.size() != 0) cout << letterListATitle << endl;
        for (int i = 0; i < letterListA.size(); i++){
            cout << (char)(i + 65) << " - " << letterListA.at(i) << endl;
        }
        cout << endl;
        if (letterListBTitle.size() != 0) cout << letterListBTitle << endl;
        for (int i = 0; i < letterListB.size(); i++){
            cout << (char)(i + 65 + letterListA.size()) << " - " << letterListB.at(i) << endl;
        }
    }; break;
    default: break;
    }
}

//use only for both
void Selections::displaySelections(bool displayNums)
{
    if (displayNums){
        if (numListTitle.size() != 0) cout << numListTitle << endl;
        for (int i = 0; i < numList.size(); i++){
            cout << i + 1 << " - " << numList.at(i) << endl;
        }
    }
    cout << endl;
    if (letterListATitle.size() != 0) cout << letterListATitle << endl;
    for (int i = 0; i < letterListA.size(); i++){
        cout << (char)(i + 65) << " - " << letterListA.at(i) << endl;
    }
    cout << endl;
    if (letterListBTitle.size() != 0) cout << letterListBTitle << endl;
    for (int i = 0; i < letterListB.size(); i++){
        cout << (char)(i + 65 + letterListA.size()) << " - " << letterListB.at(i) << endl;
    }
}

string Selections::select(string selectionMsg)
{
    string input;

    switch (sInputType){
    case NUMBERS: {
        do {
            cout << selectionMsg;
            getline(cin >> ws, input);
            if (isContactNumFormat(input)){
                int selection = stoi(input);
                if (selection >= 1 && selection <= numList.size()) break;
                cout << "Invalid Input." << endl;
            }
        } while (1);
    }; break;
    case LETTERS: {
        do {
            cout << selectionMsg;
            getline(cin >> ws, input);
            if (isLettersOnly(input)){
                if (input.size() == 1){
                    int letterEq = int(input.c_str()[0]);
                    int minLetter = 65;
                    int maxLetter = 65 + letterListA.size() + letterListB.size();

                    if (letterEq >= minLetter && letterEq <= maxLetter) break;
                    else if (letterEq >= minLetter + 32 && letterEq <= maxLetter + 32){
                        input = convertCharToString(char(int(input.c_str()[0]) - 32));
                        break;
                    }
                    else cout << "Invalid Input." << endl;
                }
                else cout << "Invalid Input." << endl;
            }
            else cout << "Invalid Input." << endl;
        } while (1);
    }; break;
    case BOTH: {
        do {
            cout << selectionMsg;
            getline(cin >> ws, input);
            if (isContactNumFormat(input)){
                int selection = stoi(input);
                if (selection >= 1 && selection <= numList.size()) break;
                cout << "Invalid Input." << endl;
            }
            else if (isLettersOnly(input)){
                if (input.size() == 1){
                    int letterEq = int(input.c_str()[0]);
                    int minLetter = 65;
                    int maxLetter = 65 + letterListA.size() + letterListB.size();

                    if (letterEq >= minLetter && letterEq <= maxLetter) break;
                    else if (letterEq >= minLetter + 32 && letterEq <= maxLetter + 32){
                        input = convertCharToString(char(int(input.c_str()[0]) - 32));
                        break;
                    }
                    else cout << "Invalid Input." << endl;
                }
                else cout << "Invalid Input." << endl;
            }
            else cout << "Invalid Input." << endl;
        } while (1);
    }; break;
    default: break;
    }

    return input;
}

string Selections::specialSelect(string selectionMsg)
{
    string input;

    switch (sInputType){
    case NUMBERS: {
        do {
            cout << selectionMsg;
            getline(cin >> ws, input);
            if (isContactNumFormat(input)){
                int selection = stoi(input);
                if (selection >= 1 && selection <= numList.size()) break;
                cout << "Invalid Input." << endl;
            }
        } while (1);
    }; break;
    case LETTERS: {
        do {
            cout << selectionMsg;
            getline(cin >> ws, input);
            if (isLettersOnly(input)){
                if (input.size() == 1){
                    int letterEq = int(input.c_str()[0]);
                    int minLetter = 65;
                    int maxLetter = 65 + letterListA.size() + letterListB.size();
                    if (input == adminStr) break;
                    if (letterEq >= minLetter && letterEq <= maxLetter) break;
                    else if (letterEq >= minLetter + 32 && letterEq <= maxLetter + 32){
                        input = convertCharToString(char(int(input.c_str()[0]) - 32));
                        break;
                    }
                    else cout << "Invalid Input." << endl;
                }
                else cout << "Invalid Input." << endl;
            }
            else cout << "Invalid Input." << endl;
        } while (1);
    }; break;
    case BOTH: {
        do {
            cout << selectionMsg;
            getline(cin >> ws, input);
            if (isContactNumFormat(input)){
                int selection = stoi(input);
                if (selection >= 1 && selection <= numList.size()) break;
                cout << "Invalid Input." << endl;
            }
            else if (isLettersOnly(input)){
                if (input.size() == 1){
                    int letterEq = int(input.c_str()[0]);
                    int minLetter = 65;
                    int maxLetter = 65 + letterListA.size() + letterListB.size();
                    if (input == adminStr) break;
                    if (letterEq >= minLetter && letterEq <= maxLetter) break;
                    else if (letterEq >= minLetter + 32 && letterEq <= maxLetter + 32){
                        input = convertCharToString(char(int(input.c_str()[0]) - 32));
                        break;
                    }
                    else cout << "Invalid Input." << endl;
                }
                else cout << "Invalid Input." << endl;
            }
            else cout << "Invalid Input." << endl;
        } while (1);
    }; break;
    default: break;
    }

    return input;
}

void Selections::clearSelections()
{
    numList.clear();
    letterListA.clear();
    letterListB.clear();
}

void Selections::putNumChoice(string choiceDesc)
{
    numList.push_back(choiceDesc);
}

void Selections::putLetterChoiceA(string choiceDesc)
{
    letterListA.push_back(choiceDesc);
}

void Selections::putLetterChoiceB(string choiceDesc)
{
    letterListB.push_back(choiceDesc);
}

Selections::Selections()
{

}


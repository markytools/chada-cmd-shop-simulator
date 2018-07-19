#include<iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>
#include "utils.h"
#include <vector>
#include <conio.h>
#include "dirent.h"
using namespace std;

void clearScreen(){
    if (system("CLS")) system("clear");
}

void renderLoadingAnimTxt(){
    cout << "LOADING.";
    long double startTime = time(0) * 1000;
    while (false || (time(0) * 1000 - startTime) < 50);
    cout<<'\r'<< string(50, ' ') <<'\r';

    cout << "LOADING..";
    startTime = time(0) * 1000;
    while (false || (time(0) * 1000 - startTime) < 50);
    cout<<'\r'<< string(50, ' ') <<'\r';

    cout << "LOADING...";
    startTime = time(0) * 1000;
    while (false || (time(0) * 1000 - startTime) < 50);
    cout<<'\r'<< string(50, ' ') <<'\r';

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void enterToContinue(){
    do {
        cout << "Press enter to continue.......(If does not continue, press enter again.)" << endl;
        cin.ignore();
        string temp;
        getline(cin, temp);
        if (temp.empty()) break;
    } while (1);
}

string getCurrentTime(){
    time_t theTime = time(NULL);
    struct tm * aTime = localtime(&theTime);

    int day = aTime -> tm_mday;
    int month = aTime -> tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    int year = aTime -> tm_year + 1900; // Year is # years since 1900

    ostringstream strs1;
    strs1 << day;
    string strDate = strs1.str();

    ostringstream strs2;
    strs2 << month;
    string strMonth = strs2.str();

    ostringstream strs3;
    strs3 << year;
    string strYear = strs3.str();
    return strDate + "/" + strMonth + "/" + strYear;
}

string substringAtPos(string str, int pos, char delim){

    string finalStr = "";
    for (int i = pos; i < str.length(); i++){
        if (str[i] != delim){
            finalStr += str[i];
        }
        else break;
    }
    return finalStr;
}

string convertCharToString(char c){
    stringstream ss;
    string target;
    ss << c;
    ss >> target;
    return target;
}

int getdir (string dir, vector<string> &files){
    DIR *dp;
    struct dirent *dirp;
    if  ((dp  = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

vector<string> getListOfFilesFromDirec(string directory){
    string dir = string(directory);
    vector<string> files = vector<string>();
    getdir(dir,files);
    if (files.size() >= 2) files.erase(files.begin(), files.begin() + 2);
    return files;
}

void removeSubstring(string &str, string substr){
    if (str.size() >= substr.size()){
        string::size_type i = str.find(substr);

        if (i != std::string::npos)
           str.erase(i, substr.length());
    }
}

bool isContactNumFormat(string str){
    return str.find_first_not_of("+0123456789") == std::string::npos;
}

bool isLettersOnly(string str){
    return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

bool isLettersAndNumbersOnly(string str){
    return str.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

bool ifStringHasSubstring(string str, string substr){
    if (str.find(substr) != std::string::npos) {
        return true;
    }
    return false;
}

bool checkEmailHasCorrectFormat(string email){
    if (ifStringHasSubstring(email, "@gmail.com") || ifStringHasSubstring(email, "@yahoo.com") || ifStringHasSubstring(email, "@outlook.com")
             || ifStringHasSubstring(email, "@ymail.com") || ifStringHasSubstring(email, "@aol.com") || ifStringHasSubstring(email, "@zoho.com")
            || ifStringHasSubstring(email, "@mail.com")){
        if (isLettersAndNumbersOnly(substringAtPos(email, 0, '@'))) return true;
    }
    return false;
}

bool fileExists(string &name){
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

string acquirePassword(){
    int c;
    string password;
    do {
        c = getch();
        switch(c){
        case 0: getch(); break;
        case '\b': {
            if (password.size() != 0){
                cout << "\b \b";
                password.erase(password.size() - 1, 1);
            }
        }; break;
        default: {
            if(isalnum(c) || ispunct(c)){
                password += c;
                cout << "*";
            }
        }; break;
        }
    }
    while(c != '\r');
    return password;
}

void genRandomID(char *s, const int len){
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
}

string toLowerString(string str){
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

bool isFileEmpty(ifstream& pFile){
    return pFile.peek() == ifstream::traits_type::eof();
}

string limitStringSize(string str, int size){
    string newStr = "";
    if (str.length() > size){
        for (int i = 0; i < size; i++){
            if (i >= size - 3){
                newStr += ".";
            }
            else newStr += str[i];
        }
    }
    else return str;
    return newStr;
}

string numberToString(float number, int prec){
    ostringstream strs;
    strs << setprecision(prec) << fixed << number;
    return strs.str();
}

//Replaces file if it exists
bool copyFileToPath(string src, string path){
    BOOL b = CopyFile(src.c_str(), path.c_str(), FALSE);
    if (!b) {
        cout << "Error: " << GetLastError() << endl;
    } else {
    }
    if (!b) return false;
    else return true;
}

void createFileIfNotExist(string filename){
    if (!fileExists(filename)){
        ofstream ofs;
        ofs.open(filename.data(), std::ofstream::out);
        ofs.close();
    }
}

bool checkIfVectorHasItem(vector<string> items, string item){
    for (string type : items){
        if (type == item) return true;
    }
    return false;
}

bool deleteFolderOnly(string folderName){
    wstring wStr(folderName.length(), L' ');
    std::copy(folderName.begin(), folderName.end(), wStr.begin());

    SHFILEOPSTRUCTW fileOperation;
    fileOperation.wFunc = FO_DELETE;
    fileOperation.pFrom = wStr.c_str();
    fileOperation.fFlags = FOF_NO_UI | FOF_NOCONFIRMATION;

    int result = ::SHFileOperationW(&fileOperation);
    if  (result != 0) return false;
    return true;
}


bool deleteFileOnly(string fileName){
    remove(fileName.c_str());
}

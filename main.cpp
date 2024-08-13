#include <iostream>
#include <sstream>
#include "AVL.h"
using namespace std;

string checkValidName(string& name) {
    int count = 0;
    for (int i = 0; i < name.size(); i++) {
        if (isalpha(name[i]) || isspace(name[i])) {
            count += 1;
        }
    }
    if (count == name.length()) {
        return "successful";
    }
    else {
        return "unsuccessful";
    }
}

string checkValidID(string& ufid) {
    int check8 = 0;
    if (ufid.size() == 8) {
        for (int i = 0; i < 8; i++) {
            if (isdigit(ufid[i])) {
                check8 += 1;
            }
        }
        if (check8 == 8)
            return "successful";
        else
            return "unsuccessful";
    }
    else {
        return "unsuccessful";
    }
}

int main() {
    AVLTree tree;

    // read the number of commands
    int count = 0;
    int num;
    cin >> num;

    // for each command, execute it on tree
    while (count <= num) {

        string enterLine;
        getline(cin, enterLine);

        istringstream inStream(enterLine);

        string function;
        getline(inStream, function, ' ');

        if (function == "insert") {
            string next;
            getline(inStream, next, '"');

            string name;
            getline(inStream, name, '"');

            string junk;
            getline(inStream, junk, ' ');

            string ufid;
            getline(inStream, ufid);

            // call the functions
            string checkID = checkValidID(ufid);
            string checkName = checkValidName(name);
            if (checkID == "unsuccessful" || checkName == "unsuccessful") {
                cout << "unsuccessful" << endl;
            }
            else {
                tree.insertNAMEID(name, ufid);
            }
        }
        else if (function == "remove") {
            string ENTERufid;
            getline(inStream, ENTERufid);

            // call the functions
            string checkID = checkValidID(ENTERufid);
            if (checkID == "unsuccessful") {
                cout << "unsuccessful" << endl;
            }
            else {
                // call the remove function
                tree.removeID(ENTERufid);
            }
        }
        else if (function == "search") {

            string checking;
            getline(inStream, checking);

            if (checking.size() == 8 && isdigit(checking[0])) {

                // call the function
                string checkID = checkValidID(checking);
                if (checkID == "unsuccessful") {
                    cout << "unsuccessful" << endl;
                }
                else {
                    tree.searchID(checking);
                }
            }
            else {
                string searchName = checking.substr(1);
                istringstream in(searchName);

                string mainName;
                getline(in, mainName, '"');

                // call the function
                string checkName = checkValidName(mainName);
                if (checkName == "unsuccessful") {
                    cout << "unsuccessful" << endl;
                }
                else {
                    tree.searchName(mainName);
                }
            }
        }
        else if (function == "printInorder") {
            tree.printInorder();
        }
        else if (function == "printPreorder") {
            tree.printPreorder();
        }
        else if (function == "printPostorder") {
            tree.printPostorder();
        }
        else if (function == "printLevelCount") {
            int level = tree.printLevelCount();
            cout << level << endl;
        }
        else if (function == "removeInorder") {
            string number;
            getline(inStream, number);
            int getNumber = stoi(number);

            tree.removeInorder(getNumber);
        }
        count++;
    }
    return 0;
}

//|                    ___
//|     ___======____=/--=)
//|   /T            \_--===)
//|   [ \ (0)   \~    \_-==)
//|    \      / )J~~    \-=)
//|     \\___/  )JJ~~    \)
//|      \_____/JJJ~~~     \
//|      / \  , \J~~~~      \
//|     (-\)\=|\\\~~~        L__
//|     (\\)  (\\\)_           \==__
//|      \V    \\\) ===_____   \\\\\\
//|             \V)     \_) \\\\JJ\J\)
//|                         /J\JT\JJJJ)
//|                         (JJJ| \UUU)
//|                          (UU)

// <---------- Testing ---------->
// <---------- Testing ---------->
// <---------- Testing ---------->

//    string enterLine;
//    getline(cin, enterLine);
//    cout << endl << enterLine << endl << endl;
//
//    istringstream inStream(enterLine);
//
//    string function;
//    inStream >> function;
//    cout << function << endl;
//
//    string next;
//    getline(inStream, next, '"');
//    cout << next << endl;
//
//    string name;
//    getline(inStream, name, '"');
//    cout << name << endl;
//
//    string junk;
//    getline(inStream, junk, ' ');
//    cout << junk << endl;
//
//    string ufid;
//    getline(inStream, ufid);
//    cout << ufid << endl;


// <----- for the remove ID function ----->

//    string line;
//    getline(cin, line);
//    cout << line << endl;
//
//    istringstream in(line);
//
//    string function;
//    in >> function;
//    cout << function << endl;
//
//    string number;
//    in >> number;
//    cout << number << endl;

//    string line;
//    getline(cin, line);
//    cout << endl << line << endl << endl;
//
//    istringstream in(line);
//
//    string function;
//    getline(in, function, ' ');
//    cout << function << endl;
//
//    string junk;
//    getline(in, junk, ' ');
//
//    string number;
//    getline(in, number);
//    cout << number << endl;
//
//    if (number.size() == 8 && isdigit(number[0])) {
//        cout << "god" << endl;
//    }
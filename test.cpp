// #include "main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "AVL.h"
#include <iostream>
#include <sstream>
#include <algorithm>

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

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

void mainLogic(string enterLine, AVLTree& tree) {

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
        cout << to_string(level) << endl;
    }
    else if (function == "removeInorder") {
        string number;
        getline(inStream, number);
        int getNumber = stoi(number);

        tree.removeInorder(getNumber);
    }
}

TEST_CASE("My First Test checking if CATCH 2 is set up right", "[flag]"){

    AVLTree tree;   // Create a Tree object

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("insert \"Neil Patel\" 12345678", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
	REQUIRE(output.str() == "successful\n");
}

TEST_CASE("(1)insert incorrect name", "[flag]"){

    AVLTree tree;   // Create a Tree object

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("insert \"9eil Pa8tel 123\" 12345678", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "unsuccessful\n");
}

TEST_CASE("(2)insert incorrect ID", "[flag]"){

    AVLTree tree;   // Create a Tree object

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("insert \"Neil Patel\" 123456789", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "unsuccessful\n");
}

TEST_CASE("(3)insert incorrect ID (Part2)", "[flag]"){

    AVLTree tree;   // Create a Tree object

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("insert \"Neil Patel\" 1+3AbC7#", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "unsuccessful\n");
}

TEST_CASE("(4)remove a bad ID", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"Neil Patel\" 99554477", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("remove 9955447a", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "unsuccessful\n");
}

TEST_CASE("(5)search a bad name", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"Neil Patel\" 88886666", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("search \"Neil 8 Patel\"", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "unsuccessful\n");
}

TEST_CASE("(1)edge case, remove a node that doesn't exist in AVL tree", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000001", tree);
    mainLogic("insert \"b\" 00000002", tree);
    mainLogic("insert \"c\" 00000003", tree);
    mainLogic("insert \"d\" 00000004", tree);
    mainLogic("insert \"e\" 00000005", tree);
    mainLogic("insert \"f\" 00000006", tree);
    mainLogic("insert \"g\" 00000007", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("remove 00000008", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "unsuccessful\n");
}

TEST_CASE("(2)edge case, remove inorder N node. where N is > the number of nodes in the tree", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000001", tree);
    mainLogic("insert \"b\" 00000002", tree);
    mainLogic("insert \"c\" 00000003", tree);
    mainLogic("insert \"d\" 00000004", tree);
    mainLogic("insert \"e\" 00000005", tree);
    mainLogic("insert \"f\" 00000006", tree);
    mainLogic("insert \"g\" 00000007", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("removeInorder 10", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "unsuccessful\n");
}

TEST_CASE("(3)edge case, remove a node where inorder successor is the right child", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000001", tree);
    mainLogic("insert \"b\" 00000002", tree);
    mainLogic("insert \"c\" 00000003", tree);

    mainLogic("remove 00000002", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printInorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "a, c\n");
}

TEST_CASE("(1)right rotation CHECKING", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000005", tree);
    mainLogic("insert \"b\" 00000006", tree);
    mainLogic("insert \"c\" 00000007", tree);
    mainLogic("insert \"d\" 00000008", tree);
    mainLogic("insert \"e\" 00000009", tree);
    mainLogic("insert \"f\" 00000010", tree);
    mainLogic("insert \"g\" 00000011", tree);

    mainLogic("insert \"x\" 00000004", tree);
    mainLogic("insert \"z\" 00000003", tree);   // here the tree is left skewed, So rotation

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printInorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "z, x, a, b, c, d, e, f, g\n");
}

TEST_CASE("(2)left rotation CHECKING", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000005", tree);
    mainLogic("insert \"b\" 00000006", tree);
    mainLogic("insert \"c\" 00000007", tree);
    mainLogic("insert \"d\" 00000008", tree);
    mainLogic("insert \"e\" 00000009", tree);
    mainLogic("insert \"f\" 00000015", tree);
    mainLogic("insert \"g\" 00000016", tree);

    mainLogic("insert \"x\" 00000011", tree);
    mainLogic("insert \"z\" 00000013", tree);   // here the tree is right skewed, So rotation

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printInorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "a, b, c, d, e, x, z, f, g\n");
}

TEST_CASE("(3)left right rotation CHECKING", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000005", tree);
    mainLogic("insert \"b\" 00000006", tree);
    mainLogic("insert \"c\" 00000007", tree);
    mainLogic("insert \"d\" 00000008", tree);
    mainLogic("insert \"e\" 00000009", tree);
    mainLogic("insert \"f\" 00000012", tree);
    mainLogic("insert \"g\" 00000016", tree);

    mainLogic("insert \"x\" 00000014", tree);
    mainLogic("insert \"z\" 00000015", tree);   // here the tree is left right skewed, So rotation

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printInorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "a, b, c, d, e, f, x, z, g\n");
}

TEST_CASE("(4)right left rotation CHECKING", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000002", tree);
    mainLogic("insert \"b\" 00000004", tree);
    mainLogic("insert \"c\" 00000005", tree);
    mainLogic("insert \"d\" 00000011", tree);
    mainLogic("insert \"e\" 00000012", tree);
    mainLogic("insert \"f\" 00000014", tree);
    mainLogic("insert \"g\" 00000016", tree);

    mainLogic("insert \"x\" 00000008", tree);
    mainLogic("insert \"z\" 00000007", tree);   // here the tree is right left skewed, So rotation

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printInorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "a, b, c, z, x, d, e, f, g\n");
}

TEST_CASE("(1)deletion cases (no children)", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000001", tree);
    mainLogic("insert \"b\" 00000002", tree);
    mainLogic("insert \"c\" 00000003", tree);
    mainLogic("insert \"d\" 00000004", tree);
    mainLogic("insert \"e\" 00000005", tree);
    mainLogic("insert \"f\" 00000006", tree);
    mainLogic("insert \"g\" 00000007", tree);

    mainLogic("remove 00000003", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printPostorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "a, b, e, g, f, d\n");
}

TEST_CASE("(2)deletion cases (1 child)", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000001", tree);
    mainLogic("insert \"b\" 00000002", tree);
    mainLogic("insert \"c\" 00000003", tree);
    mainLogic("insert \"d\" 00000004", tree);
    mainLogic("insert \"e\" 00000005", tree);
    mainLogic("insert \"f\" 00000006", tree);
    mainLogic("insert \"g\" 00000007", tree);

    mainLogic("remove 00000006", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printPostorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "a, c, b, e, g, d\n");
}

TEST_CASE("(3)deletion cases (2 children)", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000001", tree);
    mainLogic("insert \"b\" 00000002", tree);
    mainLogic("insert \"c\" 00000003", tree);
    mainLogic("insert \"d\" 00000004", tree);
    mainLogic("insert \"e\" 00000005", tree);
    mainLogic("insert \"f\" 00000006", tree);
    mainLogic("insert \"g\" 00000007", tree);

    mainLogic("remove 00000004", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printPostorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "a, c, b, g, f, e\n");
}

TEST_CASE("TEST PRINT LEVEL COUNT", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000001", tree);
    mainLogic("insert \"b\" 00000002", tree);
    mainLogic("insert \"c\" 00000003", tree);
    mainLogic("insert \"d\" 00000004", tree);
    mainLogic("insert \"e\" 00000005", tree);
    mainLogic("insert \"f\" 00000006", tree);
    mainLogic("insert \"g\" 00000007", tree);

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printLevelCount", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "3\n");
}

//TEST_CASE("Insert 100 remove 10", "[flag]"){
//
//    AVLTree tree;   // Create a Tree object
//    vector<int> IDs;
//
//    for (int i = 0; i < 100; i++) {
//        int randomInput = 10000000 % rand();
//        if (count(IDs.begin(), IDs.end(), randomInput) == 0) {
//
//            IDs.push_back(randomInput);
//            tree.insertNAMEID(to_string(randomInput), to_string(randomInput));
//        }
//    }
//    sort(IDs.begin(), IDs.end());
//
//    stringstream output;
//    streambuf* coutBuffer = cout.rdbuf();
//    cout.rdbuf(output.rdbuf());
//
//    mainLogic("printInorder", tree);
//
//    cout.rdbuf(coutBuffer);
//
//    string expectedOutput;
//    for (int i = 0; i < IDs.size(); i++) {
//        if (i != 0)
//            expectedOutput += ", ";
//        expectedOutput += to_string(IDs.at(i));
//    }
//    expectedOutput += "\n";
//
//    REQUIRE(output.str() == expectedOutput);
//
//    for (int i = 0; i < 10; i++) {
//        int random = IDs.size() % rand();
//        tree.removeInorder(random);
//        IDs.erase(IDs.begin() + random);
//    }
//
//    stringstream output;
//    streambuf* coutBuffer = cout.rdbuf();
//    cout.rdbuf(output.rdbuf());
//
//    mainLogic("printInorder", tree);
//
//    cout.rdbuf(coutBuffer);
//
//    std::stringstream expectedOutput;
//    for (int i = 0; i < IDs.size(); ++i) {
//        if (i != 0)
//            expectedOutput << ", ";
//        expectedOutput << IDs[i];
//    }
//    string names = expectedOutput.str() + "\n";
//
//    REQUIRE(output);
//    REQUIRE(output.str() == names);
//}

TEST_CASE("Insert 100 remove 10 part2", "[flag]"){

    AVLTree tree;   // Create a Tree object
    mainLogic("insert \"a\" 00000001", tree);
    mainLogic("insert \"b\" 00000002", tree);
    mainLogic("insert \"c\" 00000003", tree);
    mainLogic("insert \"d\" 00000004", tree);
    mainLogic("insert \"e\" 00000005", tree);
    mainLogic("insert \"f\" 00000006", tree);
    mainLogic("insert \"g\" 00000007", tree);
    mainLogic("insert \"h\" 00000008", tree);
    mainLogic("insert \"i\" 00000009", tree);
    mainLogic("insert \"j\" 00000010", tree);
    mainLogic("insert \"k\" 00000011", tree);
    mainLogic("insert \"u\" 00000012", tree);
    mainLogic("insert \"l\" 00000013", tree);
    mainLogic("insert \"m\" 00000014", tree);
    mainLogic("insert \"n\" 00000015", tree);
    mainLogic("insert \"o\" 00000016", tree);
    mainLogic("insert \"p\" 00000017", tree);
    mainLogic("insert \"q\" 00000018", tree);
    mainLogic("insert \"r\" 00000019", tree);
    mainLogic("insert \"s\" 00000020", tree);
    mainLogic("insert \"t\" 00000021", tree);
    mainLogic("insert \"v\" 00000022", tree);
    mainLogic("insert \"w\" 00000023", tree);
    mainLogic("insert \"x\" 00000024", tree);
    mainLogic("insert \"y\" 00000025", tree);

    mainLogic("insert \"aa\" 00000026", tree);
    mainLogic("insert \"bb\" 00000027", tree);
    mainLogic("insert \"cc\" 00000028", tree);
    mainLogic("insert \"dd\" 00000029", tree);
    mainLogic("insert \"ee\" 00000030", tree);
    mainLogic("insert \"ff\" 00000031", tree);
    mainLogic("insert \"gg\" 00000032", tree);
    mainLogic("insert \"hh\" 00000033", tree);
    mainLogic("insert \"ii\" 00000034", tree);
    mainLogic("insert \"jj\" 00000035", tree);
    mainLogic("insert \"kk\" 00000036", tree);
    mainLogic("insert \"ll\" 00000037", tree);
    mainLogic("insert \"mm\" 00000038", tree);
    mainLogic("insert \"nn\" 00000039", tree);
    mainLogic("insert \"oo\" 00000040", tree);
    mainLogic("insert \"pp\" 00000041", tree);
    mainLogic("insert \"qq\" 00000042", tree);
    mainLogic("insert \"rr\" 00000043", tree);
    mainLogic("insert \"ss\" 00000044", tree);
    mainLogic("insert \"tt\" 00000045", tree);
    mainLogic("insert \"uu\" 00000046", tree);
    mainLogic("insert \"vv\" 00000047", tree);
    mainLogic("insert \"ww\" 00000048", tree);
    mainLogic("insert \"xx\" 00000049", tree);
    mainLogic("insert \"yy\" 00000050", tree);

    mainLogic("insert \"aaa\" 00000051", tree);
    mainLogic("insert \"bbb\" 00000052", tree);
    mainLogic("insert \"ccc\" 00000053", tree);
    mainLogic("insert \"ddd\" 00000054", tree);
    mainLogic("insert \"eee\" 00000055", tree);
    mainLogic("insert \"fff\" 00000056", tree);
    mainLogic("insert \"ggg\" 00000057", tree);
    mainLogic("insert \"hhh\" 00000058", tree);
    mainLogic("insert \"iii\" 00000059", tree);
    mainLogic("insert \"jjj\" 00000060", tree);
    mainLogic("insert \"kkk\" 00000061", tree);
    mainLogic("insert \"lll\" 00000062", tree);
    mainLogic("insert \"mmm\" 00000063", tree);
    mainLogic("insert \"nnn\" 00000064", tree);
    mainLogic("insert \"ooo\" 00000065", tree);
    mainLogic("insert \"ppp\" 00000066", tree);
    mainLogic("insert \"qqq\" 00000067", tree);
    mainLogic("insert \"rrr\" 00000068", tree);
    mainLogic("insert \"sss\" 00000069", tree);
    mainLogic("insert \"ttt\" 00000070", tree);
    mainLogic("insert \"uuu\" 00000071", tree);
    mainLogic("insert \"vvv\" 00000072", tree);
    mainLogic("insert \"www\" 00000073", tree);
    mainLogic("insert \"xxx\" 00000074", tree);
    mainLogic("insert \"yyy\" 00000075", tree);

    mainLogic("insert \"aaaa\" 00000076", tree);
    mainLogic("insert \"bbbb\" 00000077", tree);
    mainLogic("insert \"cccc\" 00000078", tree);
    mainLogic("insert \"dddd\" 00000079", tree);
    mainLogic("insert \"eeee\" 00000080", tree);
    mainLogic("insert \"ffff\" 00000081", tree);
    mainLogic("insert \"gggg\" 00000082", tree);
    mainLogic("insert \"hhhh\" 00000083", tree);
    mainLogic("insert \"iiii\" 00000084", tree);
    mainLogic("insert \"jjjj\" 00000085", tree);
    mainLogic("insert \"kkkk\" 00000086", tree);
    mainLogic("insert \"llll\" 00000087", tree);
    mainLogic("insert \"mmmm\" 00000088", tree);
    mainLogic("insert \"nnnn\" 00000089", tree);
    mainLogic("insert \"oooo\" 00000090", tree);
    mainLogic("insert \"pppp\" 00000091", tree);
    mainLogic("insert \"qqqq\" 00000092", tree);
    mainLogic("insert \"rrrr\" 00000093", tree);
    mainLogic("insert \"ssss\" 00000094", tree);
    mainLogic("insert \"tttt\" 00000095", tree);
    mainLogic("insert \"uuuu\" 00000096", tree);
    mainLogic("insert \"vvvv\" 00000097", tree);
    mainLogic("insert \"wwww\" 00000098", tree);
    mainLogic("insert \"xxxx\" 00000099", tree);
    mainLogic("insert \"yyyy\" 00000100", tree);

    for (int i = 0; i < 10; i++) {
        // string index = to_string(i);
        // mainLogic("removeInorder index", tree);
        tree.removeInorder(i);
    }

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    mainLogic("printInorder", tree);

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == "b, d, f, h, j, u, m, o, q, s, t, v, w, x, y, aa, bb, cc, dd, ee, ff, gg, hh, ii, jj, kk, ll, mm, nn, oo, pp, qq, rr, ss, tt, uu, vv, ww, xx, yy, aaa, bbb, ccc, ddd, eee, fff, ggg, hhh, iii, jjj, kkk, lll, mmm, nnn, ooo, ppp, qqq, rrr, sss, ttt, uuu, vvv, www, xxx, yyy, aaaa, bbbb, cccc, dddd, eeee, ffff, gggg, hhhh, iiii, jjjj, kkkk, llll, mmmm, nnnn, oooo, pppp, qqqq, rrrr, ssss, tttt, uuuu, vvvv, wwww, xxxx, yyyy\n");
}
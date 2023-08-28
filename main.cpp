#include "AVL.h"


/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

int main() {
    AVLTree tree;
    int numCommands;
    cin >> numCommands;

    int execute = 0;
    while (numCommands >= execute) {
        string input;
        getline(cin, input);
        string command = input.substr(0, input.find(' '));

        if (command == "insert") {
            size_t start = input.find('"') + 1;  // parsing input
            size_t end = input.find('"', start);
            string name = input.substr(start, end - start);
            string ID = input.substr(end + 2);
            bool stop = false;
            for (char ch : name) {
                if (!isalpha(ch) && !isspace(ch)) { // checks name is valid
                    stop = true;
                }
            }
            regex constraints("[0-9]{8,8}");  // verify ID meets constraints
            smatch match;
            auto it = find(tree.inOrder.begin(), tree.inOrder.end(), stoi(ID));
            if (ID.length() != 8 || !regex_match(ID,match,constraints) || stop) {
                cout << "unsuccessful" << endl;
            }
            else if (it != tree.inOrder.end()) {  // checks for repeats
                cout << "unsuccessful" << endl;
            }
            else {
                tree.insert(name, stoi(ID));
            }
        }
        else if (command == "search") {
            string toSearch = input.substr(input.find(' ' ) + 1);
            regex constraints("[0-9]{8,8}");  // verify ID meets constraints
            smatch match;
            if (regex_match(toSearch, match, constraints)) {  // searching using ID
                if (toSearch.length() != 8) {
                    cout << "unsuccessful" << endl;
                } else {
                    cout << tree.search(stoi(toSearch)) << endl;
                }
            }
            else { // searching using name
                size_t start = input.find('"') + 1;
                size_t end = input.find('"', start);
                string name = input.substr(start, end - start);
                tree.search(name);
            }
        }
        else if (command == "remove") {
            string toRemove = input.substr(input.find(' ') + 1);
            regex constraints("[0-9]{8,8}");  // verify ID meets constraints
            smatch match;
            if (toRemove.length() != 8 || !regex_match(toRemove, match, constraints)) {  // searching using ID
                cout << "unsuccessful" << endl;
            }
            else {
                tree.remove(stoi(toRemove));
            }
        }
        else if (command == "removeInorder") {
            string N = input.substr(input.find(' ') + 1);
            regex pattern("[0-9]+");  // verify N is int
            smatch match;
            if (!regex_match(N,match,pattern)) {
                cout << "unsuccessful" << endl;
            }
            else {
                int toRemove = stoi(N);
                tree.removeInorder(toRemove);
            }
        }
        else if (command == "printInorder") {
            tree.printInorder();
        }
        else if (command == "printPreorder") {
            tree.printPreorder();
        }
        else if (command == "printPostorder") {
            tree.printPostorder();
        }
        else if (command == "printLevelCount") {
            tree.printLevelCount();
        }
        execute++;
    }
    return 0;
}


#include <stringutils.h>
#include <trie.h>
#include <userinterface.h>

#include <iostream>
using namespace std;

void userInterface(Trie &trie) {
    cout << "|||\t\tWelcome to Hashmap-uh!\t\t|||" << endl;
    int choice;
    while (1) {
        cout << "Enter -9999 to exit" << endl;
        cout << "Enter 1 to search for a title" << endl;
        cout << "Enter 2 to search for a phrase" << endl;
        cout << "Enter 3 to search for a date" << endl;
        cout << "Enter 4 to search for suggestions" << endl;
        cin >> choice;
        string inputQuery;
        if (choice == -9999) break;
        switch (choice) {
            case 1:
                cout << "Enter a title: " << endl;
                cin >> inputQuery;

                if (trie.search(lowerAndRemoveSpace(inputQuery))) {
                    cout << inputQuery << " found" << endl;
                } else {
                    cout << inputQuery << " not found!" << endl;
                }

                break;
            case 2:
                cout << "Search for a phrase: " << endl;
                break;
            case 3:
                cout << "Logic for search by date: " << endl;
                break;

            case 4:
                cout << "Logic for search by title suggestions: " << endl;
                cout << "Enter a word: " << endl;
                cin >> inputQuery;
                cout << "Suggestions: " << endl;
                trie.prefixSearch(trie.root, lowerAndRemoveSpace(inputQuery));
                break;

            default:
                cout << "Invalid choice. Try again: " << endl;
                break;
        }
        }
}

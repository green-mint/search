#include <stringutils.h>
#include <trie.h>
#include <userinterface.h>

#include <iostream>
using namespace std;

void userInterface(Trie &trie)
{
    cout << "|||\t\tWelcome to Hashmap-uh!\t\t|||" << endl;
    int choice;
    while (1)
    {
        cout << "Enter -9999 to exit" << endl;
        cout << "Enter 1 to search for a title" << endl;
        cout << "Enter 2 to search for a phrase" << endl;
        cout << "Enter 3 to search for a date" << endl;
        cout << "Enter 4 to search for suggestions" << endl;
        cin >> choice;
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
        string inputQuery;
        if (choice == -9999)
            break;
        switch (choice)
        {
        case 1:
            cout << "Enter a title: " << endl;
            // cin >> inputQuery;

            // getline(inputQuery,128);
            // cin.getline(inputQuery,s);
            // cin.clear();

            getline(cin,inputQuery);

            if (trie.search(inputQuery))
            {
                cout << inputQuery << " found" << endl;
            }
            else
            {
                cout << inputQuery << " not found!" << endl;
            }
            cin.clear();
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
            // cin.getline(inputQuery,str);
            // cin.clear();

            // cin >> inputQuery;
            getline(cin,inputQuery);

            cout << "Suggestions: " << endl;
            trie.prefixSearch(trie.root, inputQuery);

            break;

        default:
            cout << "Invalid choice. Try again: " << endl;
            break; 
        }
    }
}

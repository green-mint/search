
#include <HashTable.h>
#include <fstream>
#include <unordered_map>
#include <indexing.h>

using namespace std;

void generateLexicon(unordered_map<string, int> &lexiconMap,
    unordered_map<string, char> stopWords) {
    cout << "Generating lexicon..." << endl;
    int wordID = 1;

    // read each file line by line
    // for each word in line
    //   if word is not in lexicon and is not a stopword
    //     add word to lexicon
    //   else
    //     increment the index of the word in the lexicon

    string inputFile = "data/articles/2.txt";

    ifstream file;
    file.open(inputFile);

    if (!file.is_open()) {
        cout << "input file cannot be opened" << endl;
        return;
    }
    string word;
    while (file >> word) {
        if (!stopWords[word])
            if (!lexiconMap[word]) lexiconMap[word] = wordID++;
    }

    file.close();

    ofstream output;
    string lexicon_file = "data/indexing/lexicon.csv";
    output.open(lexicon_file);
    if (!output.is_open()) {
        cout << "output file cannot be opened" << endl;
        return;
    }

    unordered_map<string, int>::iterator it;
    for (it = lexiconMap.begin(); it != lexiconMap.end(); it++) {
        cout << it->first << ", " << it->second << endl;
        output << it->first << ", " << it->second << "\n";
    }

    // [fileId, frequency], wordID

    // wordID, [fileId, frequency]

    output.close();
}

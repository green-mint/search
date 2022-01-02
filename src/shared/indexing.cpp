
#include <HashTable.h>
#include <fstream>
#include <unordered_map>

#include "../include/csv.h"
#include "../include/utils.h"
using namespace std;

void generateLexicon(const string &metadataFilename,
                     unordered_map<string, int> &lexiconMap,
                     unordered_map<string, char> &stopWords) {
    cout << "Generating lexicon..." << endl;
    int wordID = 1;

    // read each file line by line
    // for each word in line
    //   if word is not in lexicon and is not a stopword
    //     add word to lexicon
    //   else
    //     increment the index of the word in the lexicon

    io::CSVReader<1, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>>
        in(metadataFilename.c_str());

    in.read_header(io::ignore_extra_column, "filename");

    string filename;
    int iterations = 0;
    while (in.read_row(filename)) {
        if (iterations > 5) break;
        iterations++;
        string inputFile = "data/articles/";

        // main loop
        inputFile += filename;

        ifstream file;
        file.open(inputFile);

        if (!file.is_open()) {
            cout << "input file cannot be opened" << endl;
            return;
        }
        string originalWord;
        while (file >> originalWord) {
            string stemmedWord;
            stemWord(originalWord, stemmedWord);

            if (!stopWords[stemmedWord])
                if (!lexiconMap[stemmedWord])
                    lexiconMap[stemmedWord] = wordID++;
        }

        file.close();
    }

    ofstream output;
    string lexicon_file = "data/indexing/lexicon.csv";
    output.open(lexicon_file);
    if (!output.is_open()) {
        cout << "output file cannot be opened" << endl;
        return;
    }

    unordered_map<string, int>::iterator it;
    for (it = lexiconMap.begin(); it != lexiconMap.end(); it++) {
        // cout << it->first << ", " << it->second << endl;
        output << it->first << ", " << it->second << "\n";
    }

    // [fileId, frequency], wordID

    // wordID, [fileId, frequency]

    output.close();
}

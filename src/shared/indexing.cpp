
#include <HashTable.h>
#include <fstream>
#include <unordered_map>
#include <indexing.h>
#include <paths.h>

#include <csv.h>
#include <utils.h>

using namespace std;

void generateLexicon(const string &metadataFilename,
  unordered_map<string, uint32_t> &lexiconMap,
  unordered_map<string, char> &stopWords) {

  cout << "Generating lexicon..." << endl;
  uint32_t wordId = 1;

  // read each file line by line
  // for each word in line
  //   if word is not in lexicon and is not a stopword
  //     add word to lexicon
  //   else
  //     increment the index of the word in the lexicon

  io::CSVReader<1, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(metadataFilename.c_str());

  in.read_header(io::ignore_extra_column, "filename");

  int iterations = 0;

  string filename;
  cout << "Reading metadata" << endl;
  while (in.read_row(filename)) {
    if (iterations > 100000) break;
    iterations++;

    // main loop
    string inputFile = CLEANED_ARTICLES_DIR + filename;

    ifstream file;
    file.open(inputFile);

    if (!file.is_open()) {
      cout << "ERROR: Input file cannot be opened" << endl;
      return;
    }

    string originalWord;
    string stemmedWord;

    // cout << "Filename: " << filename << endl;
    while (file >> originalWord) {
      stemWord(originalWord, stemmedWord);

      if (!stopWords[stemmedWord])
        if (!lexiconMap[stemmedWord])
          lexiconMap[stemmedWord] = wordId++;
    }

    file.close();
  }
  // Skipping the writing part 
  return;

  ofstream output;
  string lexiconFilename = INDEXING_DIR + "lexicon.csv";

  cout << "Writing to " << lexiconFilename << endl;

  output.open(lexiconFilename);
  if (!output.is_open()) {
    cout << "ERROR: Output file cannot be opened" << endl;
    return;
  }

  output << "word,wordId" << endl;
  for (auto &it : lexiconMap) {
    // cout << it->first << ", " << it->second << endl;
    output << it.first << "," << it.second << "\n";
  }

  // [fileId, frequency], wordId

  // wordId, [fileId, frequency]

  output.close();
}

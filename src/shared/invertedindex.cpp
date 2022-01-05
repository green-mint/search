
#include <invertedindex.h>

void InvertedIndex::addWord(const uint32_t wordId, uint32_t fileId, size_t position) {
  // if (index.find(word) == index.end()) {
  //   // No such word in the index
  //   FilesMap wordMap;
  //   index[word] = wordMap;
  // }
  // Word exists in the index
  FilesMap &wordMap = index[wordId];
  if (wordMap.files.find(fileId) == wordMap.files.end()) {
    // No such file in the word map
    // FilesMap::WordDetail fileMap;
    // fileMap.frequency = 1;
    // fileMap.positions.push_back(position);
    wordMap.files[fileId].frequency = 1;
    wordMap.files[fileId].positions.push_back(position);
  }
  else {
    // File exists in the word map
    FilesMap::WordDetail &fileMap = wordMap.files[fileId];
    fileMap.frequency++;
    fileMap.positions.push_back(position);
  }
}

InvertedIndex::FilesMap &InvertedIndex::searchWord(const uint32_t wordId) {
  return index[wordId];
}

void InvertedIndex::deleteWord(const uint32_t wordId) {
  index.erase(wordId);
}

void InvertedIndex::print() {
  for (auto it = index.begin(); it != index.end(); ++it) {
    cout << it->first << ": ";
    for (auto it2 = it->second.files.begin(); it2 != it->second.files.end(); ++it2) {
      cout << it2->first << ": " << it2->second.frequency << " ";
    }
    cout << endl;
  }
}

void populateInvertedIndex(InvertedIndex &invertedIndex, unordered_map<string, uint32_t> &lexicon, unordered_map<uint32_t, ArticleMeta> &metadata) {
  size_t filesread = 0;
  for (auto it : metadata) {
    uint32_t fileId = it.first;
    ArticleMeta &article = it.second;

    ifstream file(CLEANED_ARTICLES_DIR + article.filename);
    string line;

    char *segment;
    string originalWord;
    string stemmedWord;
    size_t position = 0;
    while (getline(file, line)) {
      position = 0;
      for (segment = strtok((char *) line.c_str(), " "); segment != NULL; segment = strtok(NULL, " ")) {
        originalWord = string(segment);
        stemWord(originalWord, stemmedWord);

        if (lexicon.find(stemmedWord) == lexicon.end()) {
          // Word not found in the lexicon
          continue;
        }

        uint32_t wordId = lexicon[stemmedWord];
        invertedIndex.addWord(wordId, fileId, position);
        ++position;
      }

      // cout << "Processed " << article.filename << endl;
    }
    if (++filesread == 100000) break;
  }
}


void InvertedIndex::writeToFile(const string &filename) {
  ofstream file(filename);
  file << "wordId" << "," << "fileId" << "," << "frequency" << "," << "positions" << endl;
  string wordId, fileId, frequency, positions;
  positions.reserve(256);

  for (auto &it0 : index) {
    for (auto &it1 : it0.second.files) {
      // wordId = to_string( it0.first;
      // fileId = it1.first;
      // frequency = it1.second.frequency;

      wordId = to_string(it0.first);
      fileId = it1.first;
      frequency = to_string(it1.second.frequency);

      positions = "\"";
      for (auto &it2 : it1.second.positions) {
        positions += to_string(it2) + ",";
      }
      positions += "\"";

      file << wordId << "," << fileId << "," << frequency << "," << positions << endl;
      // cout << it0.first << ": file: " << it1.first << " frequency: " << it1.second.frequency << " positions:[";
      // for (auto &it2 : it1.second.positions) {
      //   cout << it2 << ",";
      // }
      // cout << "]" << endl;
    }
  }
  file.close();
}

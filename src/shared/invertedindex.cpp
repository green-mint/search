
#include <invertedindex.h>

void InvertedIndex::addWord(const string &word, string &fileId, size_t position) {
  if (index.find(word) == index.end()) {
    // No such word in the index
    FilesMap wordMap;
    index[word] = wordMap;
  }
  // Word exists in the index
  FilesMap &wordMap = index[word];
  if (wordMap.files.find(fileId) == wordMap.files.end()) {
    // No such file in the word map
    FilesMap::WordDetail fileMap;
    fileMap.frequency = 1;
    wordMap.files[fileId] = fileMap;
  }
  else {
    // File exists in the word map
    FilesMap::WordDetail &fileMap = wordMap.files[fileId];
    fileMap.frequency++;
    fileMap.positions.push_back(position);
  }
}

InvertedIndex::FilesMap &InvertedIndex::searchWord(const string &word) {
  return index[word];
}

void InvertedIndex::deleteWord(const string &word) {
  index.erase(word);
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

void populateInvertedIndex(InvertedIndex &invertedIndex, unordered_map<string, Article> &metadata) {
  size_t filesread = 0;
  for (auto it : metadata) {
    string fileId = it.first;
    Article &article = it.second;

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
        invertedIndex.addWord(stemmedWord, fileId, position);
        ++position;
      }

      // cout << "Processed " << article.filename << endl;
    }
    if (++filesread == 20) break;
  }
}

#include <iostream>
#include <stringutils.h>
#include <regex>

using namespace std;

string &toLower(string &text) {
  for (int i = 0; text[i]; i++) {
    text[i] = tolower(text[i]);
  }

  return text;
}

string &lowerAndRemoveSpace(string &text) {
  std::regex r("\\s+");
  text = std::regex_replace(text, r, "");
  for (int i = 0; text[i]; i++) {
    text[i] = tolower(text[i]);
  }

  return text;
}

bool checkTitle(string title)
{
  bool isOkay = true;
  for (u_int i = 0; i < title.length(); i++)
  {
    if ((title[i] <= 'z' && title[i] >= 'a') || title[i] == ' ')
      continue;
    else
    {
      isOkay = false;
    }
  }

  return isOkay;
}

void splitString(const string &input, char delimiter, DoublyLinkedList<string> &output) {
  stringstream ss(input);
  string item;
  while (getline(ss, item, delimiter)) {
    output.push_back(item);
  }
}

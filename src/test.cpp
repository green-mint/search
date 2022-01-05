#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <streambuf>
#include <iterator>
// #include <linkedlist.h>

using namespace std;

struct Article {
  string name;
};

int main() {
  unordered_set <string> articles0;
  articles0.insert(string{ "a" });
  articles0.insert(string{ "b" });
  articles0.insert(string{ "c" });

  unordered_set <string> articles1;
  articles1.insert(string{ "a" });
  articles1.insert(string{ "b" });


  auto  intersection = set_intersection(articles0.begin(), articles0.end(), articles1.begin(), articles1.end(), ostream_iterator<string>(cout, "\n"));

  // for (auto &it : intersection) {
  //   cout << it << endl;
  // }
}

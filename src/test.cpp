#include <iostream>
#include <unordered_map>
#include <csv.h>

using namespace std;

struct Article {
  string name;
};



void foo(unordered_map<string, uint32_t> &some_map) {
  some_map["bar"] = 0;
  some_map["baz"] = 1;
}

int main() {
  unordered_map<string, uint32_t> some_map;
  foo(some_map);

  for (auto &it : some_map) {
    cout << it.first << " " << it.second << endl;
  }
  string key = "foo";
  cout << "foo" << " " << some_map[key] << endl;
}

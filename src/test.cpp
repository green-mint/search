#include <iostream> 
#include <hashmap.h>

using namespace std;

struct Article {
  string name;
  Article(string _name = "") {
    name = _name;
  }
};

int main() {
  HashMap<string, Article> hm(10);

  hm.insert("hello", { "Hello" });
  hm.insert("bish", { "bish" });
  hm.insert("bish", { "bish" });
  hm.insert("bish", { "bish" });
  hm.insert("bish", { "bish" });
  hm.insert("bish", { "bish" });
  hm.insert("bish", { "bish" });
  hm.insert("bish", { "bish" });

  cout << hm["bish"].name << endl;

  hm["bish"] = { "bish123" };
  cout << hm["hello"].name << endl;
  cout << hm["bish"].name << endl;
}

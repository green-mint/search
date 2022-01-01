#include <iostream>
#include "../include/csv.h"

using namespace std;

int main() {
  cout << "Hashmap-uh!" << endl;

  const unsigned int col_count = 3;
  const char *filename = "data/sample.csv";
  io::CSVReader<col_count> in(filename);

  in.read_header(io::ignore_extra_column, "name", "cms", "snake_level");
  string name; string cms; int snake_level;
  while (in.read_row(name, cms, snake_level)) {
    std::cout << name << " " << cms << " " << snake_level << std::endl;
  }
}

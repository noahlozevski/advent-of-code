#include <array>
#include <cctype>
#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <queue>
#include <string>        // for std::string && getline();
#include <unordered_map> // for std::unordered_map
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  std::string line;

  while (std::getline(file, line)) {

    line.append();
  }

  return 0;
}

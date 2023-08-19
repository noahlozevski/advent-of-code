#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <string>   // for std::string && getline();

struct Range {
  int low;
  int high;
};

Range *parseRange(std::string str) {
  Range *range = new Range();
  int delim = str.find("-");
  range->low = std::stoi(str.substr(0, delim));
  range->high = std::stoi(str.substr(delim + 1, str.size()));
  return range;
}

bool isInRange(const int num, const Range *range) {
  return (num >= range->low && num <= range->high);
}

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  std::string line;
  int count = 0;

  while (std::getline(file, line)) {
    // parse the lines
    const int sep = line.find(",");
    const Range *first = parseRange(line.substr(0, sep));
    const Range *second = parseRange(line.substr(sep + 1, line.size()));
    std::cout << line << std::endl;
    std::cout << "First: " << first->low << " " << first->high << std::endl;
    std::cout << "Second: " << second->low << " " << second->high << std::endl;
    std::cout << "--------------------------" << std::endl;

    if (isInRange(first->low, second) || isInRange(first->high, second) ||
        isInRange(second->low, first) || isInRange(second->high, first)) {
      std::cout << "Line " << line << " has some overlap" << std::endl;
      count++;
    }
  }
  std::cout << "Total: " << count << std::endl;
  return 0;
}

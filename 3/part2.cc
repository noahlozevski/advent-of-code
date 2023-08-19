#include <fstream>   // for std::ifstream && can allow read and write
#include <iostream>  // for std::cout
#include <set>       // for std::set
#include <stdexcept> // for std::invalid_argument
#include <string>    // for std::string && getline();

int get_priority(char letter) {
  return int(letter) >= int('A') && int(letter) <= int('Z')
             ? int(letter) - int('A') + 27
             : int(letter) - int('a') + 1;
}

int main(int argc, char *argv[]) {
  std::string curline;
  std::ifstream inputfile;

  inputfile.open("input.txt");
  if (inputfile.is_open()) {
    int sum = 0;
    uint line = 0;
    std::set<char> first;
    std::set<char> second;

    while (std::getline(inputfile, curline)) {
      for (int i = 0; i < curline.length(); i++) {
        if (line % 3 == 0) {
          // first elf

          first.insert(curline[i]);
        } else if (line % 3 == 1) {
          // second elf

          if (first.count(curline[i]) > 0) {
            second.insert(curline[i]);
          }
        } else {
          // third elf

          if (second.count(curline[i]) > 0) {
            sum += get_priority(curline[i]);
            std::cout << "Found: " << curline[i]
                      << " with priority: " << get_priority(curline[i])
                      << std::endl;

            // reset state for next set of 3 lines
            first.clear();
            second.clear();
            break;
          }
        }
      }

      line++;
    }

    std::cout << "Total: " << sum << std::endl;
  } else {
    std::cerr << "couldn't open file";
    return 1;
  }

  inputfile.close();
  return 0;
}

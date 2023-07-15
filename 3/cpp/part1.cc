#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <set>      // for std::set
#include <string>   // for std::string && getline();

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

    while (std::getline(inputfile, curline)) {
      const int secondCompartment = curline.length() / 2;
      std::set<char> letters;

      for (int i = 0; i < curline.length(); i++) {
        if (i < secondCompartment) {
          letters.insert(curline[i]);
        } else if (letters.count(curline[i]) > 0) {
          sum += get_priority(curline[i]);

          std::cout << "Found: " << curline[i]
                    << " with priority: " << get_priority(curline[i])
                    << std::endl;
          break;
        }
      }
    }

    std::cout << "Total: " << sum << std::endl;
  } else {
    std::cerr << "couldn't open file";
    return 1;
  }

  inputfile.close();
  return 0;
}

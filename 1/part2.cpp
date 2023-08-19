// goal find elf with the most calories

#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <string>   // for std::string && getline();

int main(int argc, char *argv[]) {
    // the maxes, ordered from most to least
    long long maxes[] = {0, 0, 0};
    // long long maxes[] = {3,2,1};
    long long newmax = 0;
    uint currentelf = 1;

    std::string curline;
    std::ifstream inputfile;

    inputfile.open("input.txt");

    if (inputfile.is_open()) {
      while (std::getline(inputfile, curline)) {
        if (curline.size() <= 0) {
          // we just reached the end of the group of numbers for the last elf
          for (int i = 0; i < 3; i++) {
            // here, we are maintaining a sorted list of max values
            if (newmax > maxes[i]) {
              const int previousmaximum = maxes[i];
              maxes[i] = newmax;
              newmax = previousmaximum;
            }
          }

          // output the sum for the elf, and increment the number for the next
          // elf
          std::cout << "elf #" << currentelf++ << ": " << newmax << '\n';
          // reset the current sum for the next elf
          newmax = 0;
        } else {
          // accumulate the sum of the elf's inventory
          newmax += std::stoi(curline);
        }
      }
      inputfile.close();


      // output the total sum of the maxes
      long long totalsum = 0;
      for (int i = 0; i < 3; i++) {
        totalsum += maxes[i];
        std::cout << "max #" << i << ": " << maxes[i] << '\n';
      }
      std::cout << "the total max sum is " << totalsum << '\n';

    } else {
      std::cerr << "couldn't open file";
      return 1;
    }
    return 0;
}

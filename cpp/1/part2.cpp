// Goal find elf with the most calories

#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <string>   // for std::string && getline();

int main(int argc, char *argv[]) {
    // the maxes, ordered from most to least
    long long maxes[] = {0, 0, 0};
    // long long maxes[] = {3,2,1};
    long long newMax = 0;
    uint currentElf = 1;

    std::string curLine;
    std::ifstream inputFile;

    inputFile.open("input.txt");

    if (inputFile.is_open()) {
      while (std::getline(inputFile, curLine)) {
        if (curLine.size() <= 0) {
          // we just reached the end of the group of numbers for the last elf
          for (int i = 0; i < 3; i++) {
            // Here, we are maintaining a sorted list of max values
            if (newMax > maxes[i]) {
              const int previousMaximum = maxes[i];
              maxes[i] = newMax;
              newMax = previousMaximum;
            }
          }

          // output the sum for the elf, and increment the number for the next
          // elf
          std::cout << "Elf #" << currentElf++ << ": " << newMax << '\n';
          // reset the current sum for the next elf
          newMax = 0;
        } else {
          // accumulate the sum of the elf's inventory
          newMax += std::stoi(curLine);
        }
      }
      inputFile.close();


      // output the total sum of the maxes
      long long totalSum = 0;
      for (int i = 0; i < 3; i++) {
        totalSum += maxes[i];
        std::cout << "Max #" << i << ": " << maxes[i] << '\n';
      }
      std::cout << "The total max sum is " << totalSum << '\n';

    } else {
      std::cerr << "couldn't open file";
      return 1;
    }
    return 0;
}

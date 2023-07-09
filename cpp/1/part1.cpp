// Goal find elf with the most calories

/*
  Possible solution:
  search until a empty '\n'
  Add total and put into mem
  compare mem with next total
  if larger store else iterate
  return total
  O(n)
*/

#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <string>   // for std::string && getline();

// using namespace std
// "1230\n12321\n12312\n123212\n\n1231\n\n123";

int main(int argc, char *argv[]) {
  // (asssuming the default stream is the console)
  // fstream (full stream) istream (read stream) ostream (write stream)
  std::int64_t maxSum = 0;
  std::int64_t currentSum = 0;
  uint elfLineNumber = 1;
  // start with first elf
  uint elfWithMaxSum = elfLineNumber;

  std::string curLine;
  std::ifstream inputFile; // or std::ifstream inputFile ("random.txt",
                           // ios::in); <- no need for open
  inputFile.open(
      "random.txt" /* ios::in */); // switches to file stream for input,

  if (inputFile.is_open()) {
    while (std::getline(inputFile, curLine)) { // returns false of EOF | error
      if (curLine.size() <= 0) {
        // std::cout << "Really no number here!!";
        // we just reached the end of the group of numbers for the last elf
        if (currentSum > maxSum) {
          elfWithMaxSum = elfLineNumber;
          std::cout << "New maxx sum: " << maxSum;
        }
        maxSum = maxSum > currentSum ? maxSum : currentSum;
        // output the sum for the elf, and increment the number for the next elf
        std::cout << "Elf #" << elfLineNumber++ << ": " << currentSum << '\n';
        // reset the current sum for the next elf
        currentSum = 0;
      } else {
        // accumulate the sum of the elf's inventory
        currentSum += std::stoi(curLine);
      }
    }
    inputFile.close();

    std::cout << "The total max sum is " << maxSum << '\n';
    std::cout << "The elf number is: " << elfWithMaxSum << '\n';
    // answer is Elf #197: 69501
  } else {
    std::cerr << "couldn't open file";
    return 1;
  }

  return 0;
}

// basic file operations

// https://cplusplus.com/reference/string/string/find/
// https://cplusplus.com/doc/tutorial/files/

#include <iostream> // for std::cout
#include <string>   // for std::string, contains STL methods
#include <fstream>  // for std::ifstream
#include <vector>   // for std::vector, std::sort, std::set_intersection

#define TIME_TAKEN_HRS 5 // comp time amongst diff languages

int convertPriorityType (char itemChar) {
  int encoding { 0 };
  if (itemChar > '@' && itemChar < '[' ) {
    // capital letter
    encoding = itemChar - '@';

    // because lowercase has more priority
    encoding += 26;
  }
  else if (itemChar > '`' && itemChar < '{') {
    // lowercase letter
    encoding = itemChar - '`';
  } else {
    encoding = -10000;
  }

  return encoding;
}

int main () {
    std::ifstream myFile ("input.txt", std::ios::in);
    std::string currLine;
    int sum { 0 };

    if (myFile.is_open()) {
        while (getline(myFile, currLine)) {
            int length = currLine.length();
            // auto is needed because narrowing conversion will raise an error as length() returns a type of std::size_t
            const auto rucksackLength = length/2;

            // we now seperate 
            std::string secondRuckSack = currLine.substr(rucksackLength, length);
            currLine.erase(rucksackLength, rucksackLength);

            // and sort our ruckSacks
            std::sort(currLine.begin(), currLine.end());
            std::sort(secondRuckSack.begin(), secondRuckSack.end());

            // we use a vector becuase idk how else to implement it
            std::vector<char> setContainingMatchingLetters;

            // searches two sorted ranges to find matching values placing them into a vector
            std::set_intersection(currLine.begin(), currLine.end(), secondRuckSack.begin(), secondRuckSack.end(), std::back_inserter(setContainingMatchingLetters));
            sum += convertPriorityType(setContainingMatchingLetters[0]);
        }
    } else {
        std::cerr << "File could not open.\n";
        return 1;
    }
    std::cout << "The final sum is: " << sum << " \n";

    return 0;
}
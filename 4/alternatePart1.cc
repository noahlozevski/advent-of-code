#include <iostream>     // for std::cout
#include <fstream>      // for std::ifstream
#include <string>       // for std::string
#include <string_view>  // for std::string_view
#include <vector>       // for std::vector

#define TIME_WASTED_MINS 110 // comp time amongst diff langs

namespace Constants {
    enum Constants : short {
        firstIndex,
        secondIndex,
    };
}

inline std::vector<int> returnRangeOfValues (int currVal, int endVal) {
    std::vector<int> v;
    for (; currVal <= endVal; currVal++) {
        v.push_back(currVal);
    }
    return v;
}

inline bool doRangesOverlap (const std::vector<int>& v1, const std::vector<int>& v2) {
    // Benjamin Lindley https://stackoverflow.com/questions/6906521/how-to-check-whether-a-vector-is-a-subset-of-another-in-c
    return std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) || std::includes(v2.begin(), v2.end(), v1.begin(), v1.end());
}

int main () {
    std::ifstream myFile ("input.txt", std::ios::in);

    if (myFile) {
        std::array<std::string, 2> firstRange;
        std::array<std::string, 2> secondRange;
        int lineNum = 0;
        int matchCounter = 0;

        while (
            std::getline(myFile, firstRange[Constants::firstIndex], '-') && 
            std::getline(myFile, firstRange[Constants::secondIndex], ',') && 
            std::getline(myFile, secondRange[Constants::firstIndex], '-') &&
            std::getline(myFile, secondRange[Constants::secondIndex])
        ) {
            std::cout << ++lineNum << ": ";

            int smallestValOfFirstRange = stoi(firstRange[Constants::firstIndex]);
            int largestValOfFirstRange = stoi(firstRange[Constants::secondIndex]);
            std::vector<int> vFirstRange = returnRangeOfValues(smallestValOfFirstRange, largestValOfFirstRange);

            int smallestValOfSecondRange = stoi(secondRange[Constants::firstIndex]);
            int largestValOfSecondRange = stoi(secondRange[Constants::secondIndex]);
            std::vector<int> vSecondRange = returnRangeOfValues(smallestValOfSecondRange, largestValOfSecondRange);

            if (doRangesOverlap(vFirstRange, vSecondRange)) {
                std::cout << "Found a match!\n";
                ++matchCounter;
            } else 
                std::cout << "No match found.\n";
        }
        std::cout << matchCounter << " matches found\n";
        myFile.close();
    } else 
        std::cerr << "Could not open file!\n";
        return 1;

    return 0;
}
#include <iostream>     // for std::cout
#include <fstream>      // for std::ifstream
#include <string>       // for std::string
#include <string_view>  // for std::string_view
#include <vector>       // for std::vector
#include <array>        // for std::array
#include <algorithm>    // for std::find_first_of

#define TIME_WASTED_MINS 130 // comp time amongst diff langs

// new problem don't check for a complete overlap but just one overlap

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
    // this should really be optimized, we should not be creating vectors and new strings but i am too lazy to do it.
    // this will find the first occurence of a matching value which should allow the time complexity to be lower.
    // we return if there is a matching value in either of them which means there has to be a pair.
    // find_first_of returns the end of the first vector if the element is not found so we use the not operator indicating an overlap.
    return (std::find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end()) != v1.end());
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
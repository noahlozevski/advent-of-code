#include <iostream> // for std::cout
#include <string>   // for std::string, std::sort, std::set_intersection, STL methods
#include <fstream>  // for std::ifstream
#include <vector>   // for std::vector, STL methods

int convertPriorityType (char itemChar) {
    if (itemChar > '@' && itemChar < '[' ) {
        return itemChar - '@' + 26;
    }
    return itemChar - '`';
}

inline void sortStrings (std::string& str1, std::string& str2, std::string& str3) {
    std::sort(str1.begin(), str1.end());
    std::sort(str2.begin(), str2.end());
    std::sort(str3.begin(), str3.end());
} 

int main () {
    std::ifstream myFile ("input.txt", std::ios::in);
    int sum = 0;
    
    if (myFile.is_open()) {
        std::string currLine;
        int loopCounter = 0;

        // we'll store our groups of lines in this vector below
        std::vector<std::string> lineBuffer;

        // we'll store our groups of matching sets in these vectors below
        std::vector<char> matchingLettersOfFirstSet;
        std::vector<char> matchingLetters;

        while (getline(myFile, currLine)) {
            if (loopCounter == 2) {
                // sort our strings to allow them to be used in set_intersection
                sortStrings(lineBuffer[0], lineBuffer[1], currLine);

                // find matching values in two lines
                std::set_intersection(
                    currLine.begin(), 
                    currLine.end(), 
                    lineBuffer[0].begin(), 
                    lineBuffer[0].end(), 
                    std::back_inserter(matchingLettersOfFirstSet)
                );

                // find matching values by searching through our already matched values from before with the last unmatched line
                std::set_intersection(
                    matchingLettersOfFirstSet.begin(), 
                    matchingLettersOfFirstSet.end(), 
                    lineBuffer[1].begin(), 
                    lineBuffer[1].end(), 
                    std::back_inserter(matchingLetters)
                );
                
                // access the vector containing the matching element, assuming only one was found
                int priorityType = convertPriorityType(matchingLetters[0]);

                std::cout << "Found: " << matchingLetters[0] << " with priority type " << priorityType << ".\n";
                sum += priorityType;

                // clear our values in the vectors allowing for the next group of lines to be parsed in
                matchingLettersOfFirstSet.clear();
                matchingLetters.clear();
                lineBuffer.clear();

                loopCounter = 0;
            } else {
                // store the current line at the end of the vector
                lineBuffer.push_back(currLine);

                ++loopCounter;
            }
        }
    } else {
        std::cerr << "File could not open.\n";
        return 1;
    }
    std::cout << "The final sum is: " << sum << " \n";
    myFile.close();

    return 0;
}
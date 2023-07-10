#include <fstream>
#include <iostream>
#include <string>

int convertSignToNumerical(char elfSign) {
    int ret { 0 };
    switch (elfSign) {
        case 'A':
            ret = 1;
            break;
        case 'B':
            ret = 2;
            break;
        case 'C': 
            ret = 3;
            break;
        default:
            // just crash the program at this point no way im debugging this
            for(;;);
    }
    return ret;
}

int main () {
    std::ifstream myFile ("dataset.txt");
    std::string line;

    constexpr int win  { 6 };
    constexpr int draw { 3 };
    constexpr int loss { 0 };

    int combinedScore { 0 };

    // rock is     1
    // paper is    2
    // scissors is 3

    // we will index the arr by default at index 1

    int chooseSign[5] = { 3, 1, 2, 3, 1 };

    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            int chosenSignScore { 0 };
            char elfSignCharacter { line[0] };
            char gameOutcome { line[2] };

            // input handling
            int numericalElfSign { convertSignToNumerical(elfSignCharacter) };

            switch (gameOutcome) {
                case 'X': 
                    // loss
                    chosenSignScore = chooseSign[numericalElfSign-1];
                    combinedScore += loss + chosenSignScore; 
                    break;
                case 'Y': 
                    // draw
                    chosenSignScore = chooseSign[numericalElfSign];
                    combinedScore += draw + chosenSignScore; 
                    break;
                case 'Z': 
                    // win
                    chosenSignScore = chooseSign[numericalElfSign+1];
                    combinedScore += win + chosenSignScore; 
                    break;
                default: 
                    std::cerr << "Invalid input" << std::endl;
                    return 1;
            }
            
            // clear values to be safe
            elfSignCharacter = ' ';
            gameOutcome = ' ';
            chosenSignScore = 0;
            numericalElfSign = 0;
        }
    } else {
        std::cerr << "Could not open file!" << '\n';
        return 1;
    }
    std::cout << "The combined score is: " <<
    combinedScore << '\n';

    myFile.close();
    return 0;
}

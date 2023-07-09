#include <fstream>   // for std::ifstream && can allow read and write
#include <iostream>  // for std::cout
#include <stdexcept> // for std::invalid_argument
#include <string>    // for std::string && getline();

// constants
const static rock = 0;
const static paper = 1;
const static scissors = 2;

const static unordered_map<int, int> winningMoves;
winningMoves[rock] = paper;
winningMoves[paper] = scissors;
winningMoves[scissors] = rock;

int calc_score(int mine, int opponent) {
  int score = mine + 1;
  if (winningMoves[opponent] == mine) {
    score += 6;
  } else if (mine == opponent) {
    score += 3;
  } else {
    // no additional score
    // score += 0;
  }
  return score;
}

int main(int argc, char *argv[]) {
  std::string curline;
  std::ifstream inputfile;

  inputfile.open("input.txt");

  if (inputfile.is_open()) {
    int score = 0;
    while (std::getline(inputfile, curline)) {

      // parse line
      std::cout << score << std::endl;
    }
    inputfile.close();

  } else {
    std::cerr << "couldn't open file";
    return 1;
  }
  return 0;
}

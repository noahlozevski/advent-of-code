#include <fstream>   // for std::ifstream && can allow read and write
#include <iostream>  // for std::cout
#include <stdexcept> // for std::invalid_argument
#include <string>    // for std::string && getline();

// constants
const static int rock = 0;
const static int paper = 1;
const static int scissors = 2;

const static int winningMoves[] = {paper, scissors, rock};

int calc_score(int mine, int opponent) {
  int score = mine + 1;
  if (winningMoves[opponent] == mine) {
    score += 6;
  } else if (mine == opponent) {
    score += 3;
  } else {
    // no additional score
  }
  return score;
}

std::string move_to_string(int move) {
  switch (move) {
  case rock:
    return "rock";
  case paper:
    return "paper";
  case scissors:
    return "scissors";
  default:
    throw std::invalid_argument("move_to_string: invalid move");
  }
}

int main(int argc, char *argv[]) {
  std::string curline;
  std::ifstream inputfile;

  inputfile.open("input.txt");
  if (inputfile.is_open()) {
    int score = 0;
    while (std::getline(inputfile, curline)) {
      const int opponent = int(curline[0]) - int('A');
      const int mine = int(curline[2]) - int('X');
      const int new_score = calc_score(mine, opponent);

      std::cout << move_to_string(opponent) << " vs " << move_to_string(mine)
                << ": -> +" << new_score << std::endl;
      score += new_score;
    }

    std::cout << "Total score: " << score << std::endl;
  } else {
    std::cerr << "couldn't open file";
    return 1;
  }

  inputfile.close();
  return 0;
}

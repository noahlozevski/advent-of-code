#include <array>
#include <cctype>
#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <queue>
#include <string>        // for std::string && getline();
#include <unordered_map> // for std::unordered_map
#include <vector>

void execute(std::unordered_map<int, std::queue<char>> &crates,
             std::array<int, 3> moves) {

  // quantity / from / to
  int quantity = moves[0];
  int from = moves[1];
  int to = moves[2];

  std::cout << "Executing move: " << quantity << " " << from << " " << to
            << std::endl;

  for (int i = 0; i < quantity; i++) {
    char crate = crates.at(from).front();
    crates.at(from).pop();
    crates.at(to).push(crate);
  }
}

void print_crates_without_clearing(
    std::unordered_map<int, std::queue<char>> crates) {
  for (auto it = crates.begin(); it != crates.end(); it++) {
    std::cout << it->first << ": ";
    std::queue<char> queue = it->second;

    while (!queue.empty()) {
      std::cout << queue.front() << " ";
      queue.pop();
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  std::string line;

  std::unordered_map<int, std::queue<char>> crates;
  std::vector<std::array<int, 3>> moves;
  bool hasParsedCrates = false;

  while (std::getline(file, line)) {
    if (std::isdigit(line[1])) {
      hasParsedCrates = true;
      // we reached the number row, no more crates to parse
      continue;
    }

    if (!hasParsedCrates) {
      // parse the crates
      for (int i = 0; i < line.size(); i++) {
        const char chr = line[i];

        if (std::isalpha(chr)) {
          int column = (i + 3) / 4;
          std::cout << "Found crate " << chr << " : " << column << std::endl;

          if (crates.find(column) == crates.end()) {
            crates.insert(std::make_pair(column, std::queue<char>()));
          }
          crates.at(column).push(chr);
        }
      }
    } else {

      // parsing moves
      int moveIndex = 0;
      // quantity / from / to
      std::array<int, 3> move;
      for (int i = 0; i < line.size(); i++) {
        const char chr = line[i];
        if (std::isdigit(chr)) {
          move[moveIndex++] = chr - '0';
        }
      }
      moves.push_back(move);
    }
  }

  // print the crates
  std::cout << "Initial crate state:" << std::endl;
  print_crates_without_clearing(crates);

  // execute the moves
  for (int i = 0; i < moves.size(); i++) {
    auto move = moves[i];
    execute(crates, move);
    std::cout << "state after execution: " << std::endl;
    print_crates_without_clearing(crates);
  }

  return 0;
}

#include <cctype>   // for std::isdigit
#include <fstream>  // for std::ifstream
#include <iostream> // for std::cout
#include <stack>    // for std::stack
#include <string>   // for std::string, std::stoi
#include <vector>   // for std::vector

int main() {
  std::ifstream myFile("input.txt", std::ios::in);

  if (myFile.is_open()) {
    // store the current line
    std::string currLine;

    // store the lines before the crates
    std::vector<std::string> lineBuffers;
    // store the crates
    std::vector<std::stack<char>> crates;

    // flag to indicate that the crates have been parsed and accounted for
    bool cratesAccountedFor = false;

    // constants to indicate the position of the count, source, and destination
    // located within the file
    constexpr int countDest = 5;
    constexpr int sourceDest = 12;
    constexpr int destDest = 17;

    // store the number of columns and rows of crates
    int cratesColumnsCount;
    int cratesRowCount;

    while (std::getline(myFile, currLine)) {
      // if the crates have not been accounted for, then parse the crates
      if (!cratesAccountedFor) {
        if (currLine.length() == 0) {
          cratesAccountedFor = true;

          // calculate the number of columns and rows of crates
          cratesColumnsCount =
              (lineBuffers[lineBuffers.size() - 1]
                          [lineBuffers[lineBuffers.size() - 1].length() - 2]) -
              '0';
          cratesRowCount = lineBuffers.size() - 1;

          // initialize the size of the crates, for whatever reason without this
          // line the program crashes
          crates.resize(cratesColumnsCount);

          // intialize the crates
          for (int row = cratesRowCount - 1; row >= 0; --row) {
            for (int nextChar = 1, col = 0;
                 nextChar < lineBuffers[row].length(); nextChar += 4, col++) {
              char currentChar = lineBuffers[row][nextChar];
              if (currentChar == ' ') {
                // if the current char is a space, then skip it
                continue;
              }
              // otherwise, push the current char into the crates
              crates[col].push(currentChar);
            }
          }
        } else {
          // store the current line
          lineBuffers.push_back(currLine);
        }
      } else {
        // lambda to execute the command
        auto exe{[&crates](const int count, const int source,
                           const int destination) mutable {
          // now we need to retain the order when pushing multiple of a count
          // so we use a seperate stack
          std::stack<char> *crateStack = new std::stack<char>;

          // insert elements in our temporary stack
          for (int i = 0; i < count; i++) {
            crateStack->push(crates[source].top());
            crates[source].pop();
          }
          // insert our temporary stack elements to our destination stack until
          // the stack is empty
          while (!crateStack->empty()) {
            crates[destination].push(crateStack->top());
            crateStack->pop();
          }

          // delete the dummy crate stack
          delete crateStack;
        }};

        // parse the command
        int offset = 0;
        std::string count = currLine.substr(countDest, 1);
        if (std::isdigit(currLine[countDest + 1])) {
          ++offset;
          count += currLine[countDest + offset];
        }
        std::string source = currLine.substr(sourceDest + offset, 1);
        if (std::isdigit(currLine[sourceDest + offset + 1])) {
          ++offset;
          source += currLine[sourceDest + offset];
        }
        std::string destination = currLine.substr(destDest + offset, 1);
        if (std::isdigit(currLine[destDest + offset + 1])) {
          ++offset;
          destination += currLine[destDest + offset];
        }
        // execute the command
        exe(std::stoi(count), std::stoi(source) - 1,
            std::stoi(destination) - 1);
      }
    }
    // print the crates
    for (int i = 0; i < cratesColumnsCount; i++) {
      std::cout << crates[i].top();
    }
    std::cout << '\n';
  } else {
    std::cerr << "Unable to open file\n";
    return 1;
  }

  myFile.close();
  return 0;
}
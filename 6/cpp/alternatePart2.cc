#include <fstream>  // for std::ifstream
#include <iostream> // for std::cout
#include <string>   // for std::string
#include <vector>   // for std::vector

bool isUnique(std::vector<char> v) {
  std::size_t originalSize = v.size();
  // sort and remove duplicates within a copied vector
  std::sort(v.begin(), v.end());
  auto it = std::unique(v.begin(), v.end());
  v.erase(it, v.end());
  // if we have the same size after removing all duplicates than it has to be
  // unique.
  return (v.size() == originalSize);
}

void iterateAndReplace(std::vector<char> &v, const char element) {
  v.erase(v.begin());
  v.push_back(element);
}

int main() {
  std::ifstream myFile("input.txt", std::ios::in);

  if (myFile.is_open()) {
    std::string line;
    std::getline(myFile, line);

    std::vector<char> chars;
    constexpr short initalizerNumber = 14;

    // intialize our vector
    for (int i = 0; i < initalizerNumber; i++)
      chars.push_back(line[i]);

    // iterate over the rest of the characters
    for (int i = initalizerNumber; i < line.length(); i++) {
      iterateAndReplace(chars, line[i]);
      if (isUnique(chars)) {
        std::cout << "Found unique element: " << i + 1 << std::endl;
        break;
      }
    }

  } else {
    std::cerr << "Could not process file.\n";
    return 1;
  }

  myFile.close();
  return 0;
}
#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <queue>
#include <set>
#include <string> // for std::string && getline();

int count_unique(char list[], int length) {
  std::set<char> set;
  for (int i = 0; i < length; i++) {
    set.insert(list[i]);
  }
  return set.size();
}

int find_first_non_repeating_char(std::string line, int window_size) {
  char *window = new char[window_size]{};

  for (int i = 0; i < line.length(); i++) {
    window[i % window_size] = line[i];
    // log_window(window, window_size);

    if (i >= window_size && count_unique(window, window_size) == window_size) {
      std::cout << "Found non-repeating sequence" << std::endl;
      for (int j = 0; j < window_size; j++) {
        std::cout << window[j];
      }
      std::cout << std::endl;
      return i + 1;
    }
  }

  return -1;
}

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  std::string line;

  while (std::getline(file, line)) {
    std::cout << "line: " << line << std::endl;
    std::cout << "\033[1;31m" << find_first_non_repeating_char(line, 14)
              << "\033[0m\n";
  }

  return 0;
}

void log_window(char list[], int length) {
  for (int i = 0; i < length; i++) {
    std::cout << list[i];
  }
  std::cout << std::endl;
}

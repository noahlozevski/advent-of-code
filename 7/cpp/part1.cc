#include <charconv>
#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <queue>
#include <set>
#include <string> // for std::string && getline();
#include <string_view>
#include <unordered_map>

#include <string>
#include <vector>

std::vector<std::string_view> split(const std::string_view &str,
                                    char delimiter) {
  std::vector<std::string_view> tokens;
  auto start = str.begin();
  while (start != str.end()) {
    auto end = std::find(start, str.end(), delimiter);
    tokens.push_back(std::string_view(start, end - start));
    start = end + 1;
  }
  return tokens;
}

std::string get_parent_directory(std::string &path) {
  return path.substr(0, path.find('/'));
}

void update_parent_directories(
    std::string &current_path,
    std::unordered_map<std::string, int> &directory_size) {
  std::vector<std::string_view> tokens = split(current_path, '/');
  std::string parent_path = "";

  for (int i = 0; i < tokens.size() - 1; i++) {
    parent_path += tokens[i];
    directory_size[parent_path] += directory_size[current_path];
    parent_path += "/";
  }
}

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  std::string line;
  std::string current_path;
  std::unordered_map<std::string, int> directory_size;

  while (std::getline(file, line)) {
    std::cout << "line: " << line << std::endl;
    std::vector<std::string_view> tokens = split(line, ' ');

    if (line[0] == '$') {
      if (tokens[1] == "cd") {
        if (tokens[2] == "/") {
          current_path = "/";
        } else if (tokens[2] == "..") {
          current_path = get_parent_directory(current_path);
        } else {
          current_path += "/" + std::string(tokens[2].data(), tokens[2].size());
        }
      }
    } else {
      // must be a directory or file
      // parse a numbejr
      if (std::isdigit(tokens[1][0])) {
        int file_size;
        std::from_chars(tokens[1].data(), tokens[1].data() + tokens[1].size(),
                        file_size);
        std::cout << "file size: " << tokens[1] << std::endl;

        directory_size[current_path] += file_size;

        // update parent path sizes
        std::string tmp_parent = current_path;
        while (tmp_parent != "/" && tmp_parent.size() > 0) {
        }

      } else {
        // it is a directory
        std::cout << "directory: " << tokens[1] << std::endl;
        continue;
      }
    }
  }

  return 0;
}

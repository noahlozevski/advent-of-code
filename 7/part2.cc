#include <charconv>
#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <queue>
#include <set>
#include <sstream>
#include <string> // for std::string && getline();
#include <unordered_map>
#include <vector>

std::vector<std::string> split(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(str);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string get_parent_directory(std::string &path) {
  if (path == "/") {
    return path;
  }
  int i = 0;
  for (i = path.length() - 2; i >= 0; i--) {
    if (path[i] == '/') {
      break;
    }
  }
  return path.substr(0, i + 1);
}

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  std::string line;
  std::string current_path;
  std::unordered_map<std::string, int> directory_size;
  std::set<std::string> counted_files;

  while (std::getline(file, line)) {
    // std::cout << "line: " << line << std::endl;
    std::vector<std::string> tokens = split(line, ' ');
    // std::cout << "current path: " << current_path << std::endl;

    if (line[0] == '$') {
      std::cout << "command: " << tokens[1] << std::endl;
      // its a command
      if (tokens[1] == "cd") {
        std::string dir = tokens[2];
        if (dir == "/") {
          current_path = "/";
        } else if (dir == "..") {
          current_path = get_parent_directory(current_path);
        } else {
          current_path += dir + "/";
        }
      }
    } else {
      if (tokens[0] == "dir") {
        continue;
      } else {
        std::string digits = tokens[0];
        std::string file = tokens[1];

        int file_size;
        std::from_chars(digits.data(), digits.data() + digits.size(),
                        file_size);

        std::string file_path = current_path + file;
        std::cout << "file: " << file_path << " size: " << file_size
                  << std::endl;

        if (counted_files.find(file_path) != counted_files.end()) {
          std::cout << "file " << file_path << " already counted" << std::endl;
          continue;
        }
        counted_files.insert(file_path);

        if (directory_size.find(current_path) == directory_size.end()) {
          directory_size[current_path] = 0;
        }
        directory_size[current_path] += file_size;

        // update parent path sizes
        std::string tmp_parent = current_path;
        while (tmp_parent != "/") {
          tmp_parent = get_parent_directory(tmp_parent);
          directory_size[tmp_parent] += file_size;
        }
      }
    }
  }

  std::cout << "directory sizes: " << std::endl;

  // int total_size = 70000000;
  // offsetting the remaining size to make the optimization func solve at 0
  int remaining_size = 40000000 - directory_size["/"];
  std::cout << "remaining size after subtracting the root: " << remaining_size
            << std::endl;
  // smallest directory that makes remaining positive
  int to_delete = INT_MAX;
  for (auto &it : directory_size) {
    if (remaining_size + it.second > 0 && it.second < to_delete) {
      to_delete = it.second;
      std::cout << "update min directory size to delete: " << to_delete
                << std::endl;
    }
  }
  std::cout << "min value found: " << to_delete << std::endl;
  return 0;
}

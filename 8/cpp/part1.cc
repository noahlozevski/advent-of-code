#include <charconv>
#include <fstream>  // for std::ifstream && can allow read and write
#include <iostream> // for std::cout
#include <queue>
#include <set>
#include <sstream>
#include <string> // for std::string && getline();
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::vector<int>> map;

  // parse the map out
  while (std::getline(file, line)) {
    std::vector<int> row;
    std::cout << "Line: " << line << std::endl;
    for (int i = 0; i < line.length(); i++) {
      row.push_back(line[i] - '0');
    }
    map.push_back(row);
  }

  std::vector<std::vector<bool>> visible;

  // all outer edges are initially visible
  // int visible_trees = 2 * map.size() + 2 * map[0].size() - 4;
  int visible_trees = 0;
  // start with top edge, going downwards
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); j++) {
      std::cout << "i: " << i << " j: " << j << std::endl;
      bool is_edge =
          i == 0 || i >= map.size() - 1 || j == 0 || j >= map[0].size() - 1;
      if (is_edge) {
        std::cout << "Edge: " << map[i][j] << std::endl;
        visible_trees++;
        continue;
      }

      bool top = map[i][j] < map[i][j - 1];
      bool bottom = map[i][j] < map[i][j + 1];
      bool left = map[i][j] < map[i - 1][j];
      bool right = map[i][j] < map[i + 1][j];
      if (top && bottom && left && right) {
        visible_trees++;
        std::cout << "Visible: " << map[i][j] << std::endl;
      }
    }
  }
  std::cout << "Visible trees: " << visible_trees << std::endl;

  return 0;
}

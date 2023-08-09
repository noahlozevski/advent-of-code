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
  std::vector<std::vector<bool>> visible;

  // parse the map out
  while (std::getline(file, line)) {
    std::vector<int> row;
    std::vector<bool> visible_row;
    std::cout << "Line: " << line << std::endl;
    for (int i = 0; i < line.length(); i++) {
      row.push_back(line[i] - '0');
      visible_row.push_back(false);
    }
    map.push_back(row);
    visible.push_back(visible_row);
  }

  for (int row = 0; row < map.size(); row++) {
    // scanning left -> right
    for (int col = 0; col < map[0].size(); col++) {
      bool is_edge = row == 0 || row >= map.size() - 1 || col == 0 ||
                     col >= map[0].size() - 1;
      if (is_edge) {
        visible[row][col] = true;
        continue;
      }

      int current = map[row][col];
      int left = map[row][col - 1];
      if (current < left) {
        // no more visible in this direction
        break;
      } else if (current == left) {
        // same height, not visible
        continue;
      } else {
        visible[row][col] = true;
      }
    }

    // scanning right -> left
    for (int col = map[0].size() - 1; col >= 0; col--) {
      bool is_edge = row == 0 || row >= map.size() - 1 || col == 0 ||
                     col >= map[0].size() - 1;
      if (is_edge) {
        visible[row][col] = true;
        continue;
      }

      int current = map[row][col];
      int right = map[row][col + 1];
      if (current < right) {
        // no more visible in this direction
        break;
      } else if (current == right) {
        // same height, not visible
        continue;
      } else {
        visible[row][col] = true;
      }
    }
  }

  for (int col = 0; col < map[0].size(); col++) {
    // scanning top -> bottom
    for (int row = 0; row < map.size(); row++) {
      bool is_edge = row == 0 || row >= map.size() - 1 || col == 0 ||
                     col >= map[0].size() - 1;
      if (is_edge) {
        visible[row][col] = true;
        continue;
      }

      int current = map[row][col];
      int top = map[row - 1][col];
      if (current < top) {
        // no more visible in this direction
        break;
      } else if (current == top) {
        // same height, not visible
        continue;
      } else {
        visible[row][col] = true;
      }
    }

    // scanning bottom -> top
    for (int row = map.size() - 1; row >= 0; row--) {
      bool is_edge = row == 0 || row >= map.size() - 1 || col == 0 ||
                     col >= map[0].size() - 1;
      if (is_edge) {
        visible[row][col] = true;
        continue;
      }

      int current = map[row][col];
      int bottom = map[row + 1][col];
      if (current < bottom) {
        // no more visible in this direction
        break;
      } else if (current == bottom) {
        // same height, not visible
        continue;
      } else {
        visible[row][col] = true;
      }
    }
  }

  // count the visible trees
  std::cout << "Visible: " << std::endl;
  int visible_trees = 0;
  for (int row = 0; row < map.size(); row++) {
    for (int col = 0; col < map[0].size(); col++) {
      if (visible[row][col]) {
        std::cout << "1";
        visible_trees++;
      } else {
        std::cout << "0";
      }
    }

    std::cout << std::endl;
    // for (int col = 0; col < map[0].size(); col++) {
    //   std::cout << map[row][col];
    // }
    // std::cout << std::endl;
  }

  std::cout << "Visible trees: " << visible_trees << std::endl;
  return 0;
}

#include "graph.h"
#include <iostream>

using namespace std;

void Graph::readFromFile() {



}





// Function from cs 128 to get line:

// std::ifstream ifs{file_name};
//   for (std::string line; std::getline(ifs, line); line = "") {
//     dna_database.push_back(utilities::GetSubstrs(line, ','));
// }

// Function from cs 128 to get substr of a line:
//     std::vector<std::string> utilities::GetSubstrs(const std::string& str,
//                                                char delimiter) {
//   size_t last = 0;
//   std::vector<std::string> substrs;
//   for (size_t i = 0; i != str.length(); ++i) {
//     if (str.at(i) == delimiter) {
//       std::string substr = str.substr(last, i - last);
//       last = i + 1;
//       substrs.push_back(substr);
//     }
//   }
//   std::string substr = str.substr(last, str.length() - last);
//   substrs.push_back(substr);
//   return substrs;
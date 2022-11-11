#include "graph.h"


using namespace std;

Graph::Graph() {
    readFromFile();
}

string Graph::decodeHTTP(string title) {
    static map<string, string> decoded {
        {"%C3%81", "Á"},
        {"%C3%A1", "á"}, 
        {"%C3%85", "Å"},
        {"%C3%89", "É"},
        {"%C3%93", "Ó"},
        {"%E2%82%AC", "€"},
        {"%26", "&"},
        {"%28", "("},
        {"%29", ")"},
        {"%C3%BC", "ü"},
        {"%27", "'"},
        {"%2C", ","},
        {"%C3%A9", "é"},
        {"%C3%AD", "í"},
        {"%C5%99", "ř"},
        {"%C3%B3", "ó"},
        {"%C3%B6", "ö"},
        {"%C3%B8", "ø"},
        {"%C3%B4", "ô"},
        {"%C3%BA", "ú"},
        {"%C3%B1", "ñ"},
        {"%C3%A6", "æ"},
        {"%C3%A4", "ä"},
        {"%E2%80%93", "-"}, // –
        {"%C5%A1","š"},
        {"%C4%8D","č"},
        {"%C4%87", "ć"},
        {"%C5%82", "ł"},
        {"%C4%AB", "ī"},
        {"%2A", "*"},
        {"%C5%8D", "ō"},
        {"%C4%83", "ă"},
        {"%C3%B2", "ò"},
        {"%C3%A3", "ã"},
        {"%C3%A5", "å"},
        {"%21", "!"}
    };
    string toReturn = "";
    for (unsigned i = 0; i < title.length(); i++) {
        if (title.substr(i, 2) == "__") {
            toReturn += ": ";
            i++;
            continue;
        } else if (title.at(i) == '_') {
            toReturn += " ";
            continue;
        } else {
            string threeChar = title.substr(i, 3);
            string sixChar = title.substr(i, 6);
            string nineChar = title.substr(i, 9);
            for (auto entry : decoded) {
                if (threeChar == entry.first) {
                    toReturn += entry.second;
                    i += 2;
                    break;
                } else if (sixChar == entry.first) {
                    toReturn += entry.second;
                    i += 5;
                    break;
                } else if (nineChar == entry.first) {
                    toReturn += entry.second;
                    i += 8;
                    break;
                }
            }
        }
        toReturn += title.at(i);
    }
    return toReturn;
}

void Graph::readFromFile() {
    ifstream ifs("/workspaces/cs225/Final-Project/data/articles.tsv");
    for (string line; getline(ifs, line); line = "") {
        if (line.substr(0, 1) == "#") { // skip heading information
            continue;
        }
        nodeList_.push_back(Node(decodeHTTP(line)));
    }
    cout << (nodeList_[0].data) << endl;
}

void Graph::insertEdge(Node v1, Node v2, int weight) {
    
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
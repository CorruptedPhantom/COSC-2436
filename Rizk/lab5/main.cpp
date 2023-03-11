#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));
  vector<string> word;
  map<string, int> mapWord;
  string in = "";
  
  if (input.peek() != EOF) {
    while (getline(input, in)) {
      in.erase(remove(in.begin(), in.end(), '\n'), in.end());
      in.erase(remove(in.begin(), in.end(), '\r'), in.end());
      if (in.size() == 0) continue;
      string appendStr;
      for (auto l : in) {
        if (l == ' ' || l == '.' || l == ',' || l == '!' || l == '?')
        {
          if (!appendStr.empty()) word.push_back(appendStr);
          appendStr = "";
        } else if (l != '"')
          appendStr.push_back(tolower(l));
      }
    }
    for (auto x : word) {
      if (mapWord.find(x) == mapWord.end()) {
        mapWord.insert(pair<string, int>(x, 1));
      } else {
        int num = mapWord[x] + 1;
        mapWord.erase(x);
        mapWord.insert(pair<string, int>(x, num));
      }
    }
    for (auto count = mapWord.begin(); count != mapWord.end(); count++)
    {
      count == --mapWord.end()
        ? output << count->first << ": " << count->second
        : output << count->first << ": " << count->second << endl;
    }
  }
}
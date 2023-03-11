#include <iostream>
#include "BTree.h"
#include <fstream>
#include <string>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[])
{
  ArgumentManager am(argc, argv);
  string inFile = am.get("input");
  string comFile = am.get("command");
  string outFile = am.get("output");
  ifstream input(inFile);
  ifstream commandFile(comFile);
  ofstream output(outFile);

  string temp;
  int degree;
  commandFile >> temp;
  temp = temp.substr(temp.find('=') + 1, 1);
  if(isdigit(temp[0]))
  {
    degree = stoi(temp);
  }
  node::BTree B(degree);
  string word = "";
  int num;
  int amount = 0;
  while(!input.eof())
  {
    word = "";
    input >> temp;
    if(temp == " " || temp == "")
    {
      continue;
    }
    for(int x = 0; x < temp.length(); x++)
    {
      if(isdigit(temp[x]))
      {
        word = word + temp[x];
      }
    }
    num = stoi(word);
    B.insert(num);
  }
  int level;
  output << "Height=" << B.height(B.getRoot()) << " " << endl;
  while(!commandFile.eof())
  {
    word = "";
    getline(commandFile, temp);
    if(temp == " " || temp == "")
    {
      continue;
    }
    for(int x = 0; x < temp.length(); x++)
    {
      if(isdigit(temp[x]))
      {
        word = word + temp[x];
      }
    }
    level = stoi(word);
    B.print(B.getRoot(),level, output);
    output << endl;
  }
}
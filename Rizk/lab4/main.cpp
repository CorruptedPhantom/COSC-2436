#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

class queuePriority
{
  map<double, vector<string>> queue; //stores priority and task ("work")
  public:
    void push(double priority, string work) //the purpose of this function is to add string "work" to the queuePriority.
    {
        if (!queue[priority].empty()) //if the queue is not empty, i.e. there is another task already in there
        {
        queue[priority].push_back(work); //push the work into the priority vector
        }
        else
        {
        vector<string> workList;
        workList.push_back(work);
        queue[priority] = workList; //make a new vector to hold work, push that work into that vector make the new priority equal that work
        }
    }
    string pop()
    {
        if(!queue.begin()->second.empty())
        { //if queue not empty
            string work = queue.begin()->second[0]; //set work to the work in the value container vector
            queue.begin()->second.erase(queue.begin()->second.begin()); //erase the occurences
            if(queue.begin()->second.empty()) //if the queue is empty
                queue.erase(queue.begin()); //delete it from the map
            return work; // return the work at the end of the call
        }
        return "";
    }
};
int main(int argc, char *argv[])
{
  //ArgumentManager am(argc, argv);
  //ifstream inputFile(am.get("input"));
  //ofstream outputFile(am.get("output"));

  // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
  ifstream inputFile("input4.txt");
  ofstream outputFile("output4.txt");

  string in;
  int count = 0;
  queuePriority qp;
  while(getline(inputFile, in))
  {
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    int space = in.rfind(' ');
    string workTask = in.substr(0, space);
    double time = std::stod(in.substr(space + 1, in.length() - space));
    qp.push(time, workTask);
    count++;
  }
  for (int i = 0; i < count; i++)
  {
    outputFile << qp.pop() << endl;
  }
}
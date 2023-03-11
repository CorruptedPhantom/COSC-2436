#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <iomanip>
#include "ArgumentManager.h"
using namespace std;

int prec(char c) {
  if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return 0;
}

string getPostfix(string s) {
  stack<char> st;
  string postfix;
 
  for (int i=0; i<s.length(); i++) {
    if (isdigit(s.at(i)))
      postfix += s.at(i);
    else if (s.at(i) == '(')
      st.push('(');
    else if (s.at(i) == ')') {
      while (st.top() != '(') {
        postfix += st.top();
        st.pop();
      }
      st.pop();
    }
    else {
      while (!st.empty() && prec(s.at(i)) <= prec(st.top())) {
          postfix += st.top();
          st.pop();
      }
      st.push(s.at(i));
    }
  }
  while (!st.empty()) {
    postfix += st.top();
    st.pop();
  }
  return postfix;
}

int evaluatePostfix(string s) {
  stack<int> st;
  string answer;

  for (int i=0; i<s.length(); i++) {
    if (isdigit(s.at(i)))
    {
      string temp = "";
      temp += s.at(i);
      st.push(s.at(i) - '0');
    }
    else if (s.at(i) == 'x')
    {
      st.push(-1);
    }
    else {
      int val1 = st.top(); st.pop();
      int val2 = st.top(); st.pop();
      if (val1 > -1 && val2 > -1)
      {
        switch (s.at(i))
        {
          case '+': st.push(val2 + val1); break;
          case '-': st.push(val2 - val1); break;
          case '*': st.push(val2 * val1); break;
          case '/': st.push(val2 / val1); break;
        }
      }
      else if (val2 < 0 || val2 < 0)
            {
                if (val2 < 0)
                {
                    answer += "x";
                    (val2 > -1) ? (answer += to_string(val2)) : (answer += to_string(val2));
                    answer += s.at(i);
                }
                else if (val2 < 0)
                {
                    (val2 > -1) ? (answer += to_string(val2)) : (answer += to_string(val2));
                    answer += "x";
                    answer += s.at(i);
                }
            }
    }
  }
  return st.top();
}

int main(int argc, char *argv[])
{ //start of TA-provided code
  ArgumentManager am(argc, argv); 
  ifstream input(am.get("input"));
  ifstream command(am.get("command"));
  ofstream output(am.get("output"));
  vector<string> lines;
  string in = "";
  while (getline(input, in))
  {
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    if (in.size() == 0)
      continue;
    lines.push_back(in);
  }
  for (int x = 0; x < lines.size(); x++)
  {
    string line = lines.at(x).substr(0, lines.at(x).find("="));
    double rightSide = stoi(lines.at(x).substr(lines.at(x).find("=") + 1, (lines.at(x).find("=")) - (lines.at(x).length() - 1)));
    double answer = 0;
    string postFix = getPostfix(line);
    postFix = evaluatePostfix(postFix);
    if (postFix.find("*") != string::npos)
    {
      string temp = "";
      for (auto answer : postFix)
        if (isdigit(answer))
          temp += answer;
      double number = stoi(temp);
      answer = (double)rightSide / (double)number;
    }
    else if (postFix.find("/") != string::npos)
    {
      string temp = "";
      for (auto answer : postFix)
        if (isdigit(answer))
          temp += answer;
      double number = stoi(temp);
      if (isdigit(postFix.at(0)))
        answer = (double)number / (double)rightSide;
      else if (postFix.at(0) == 'x')
        answer = (double)rightSide * (double)number;
    }
    else if (postFix.find("+") != string::npos)
    {
      string temp = "";
      for (auto answer : postFix)
        if (isdigit(answer))
          temp += answer;
      double number = stoi(temp);
      answer = (double)rightSide - (double)number;
    }
      else if (postFix.find("-") != string::npos)
      {
        string temp = "";
        for (auto answer : postFix)
          if (isdigit(answer))
            temp += answer;
        double number = stoi(temp);
        if (isdigit(postFix.at(0)))
        {
          answer = (double)rightSide - (double)number;
          (answer == 0) ? (answer = 0) : (answer *= -1);
        }
          else if (postFix.at(0) == 'x')
            answer = (double)rightSide + (double)number;
      }
      output << std::setprecision(2) << std::fixed;
      output << answer;
  }
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node
{
    int data;
    struct node* next;
};

struct BSTnode
{
  string contents;
  BSTnode l;
  BSTnode r;
};

class linkedListQueue
{
  private:
    node* head;
    int size;
  public:
    linkedListQueue() { head = nullptr; size = 0; }
    ~linkedListQueue()
    {
      if(head!=nullptr)
      {
        while(head->next != nullptr)
        {
          node* temporary = head;
          head=head->next;
          delete head;
        }
        delete head;
      }
    }
    bool isEmpty() { return head==nullptr; }
    void enqueue(int t, string n)
    {
      node* temporary = new node;
      temporary->priority=t; temporary->name=n;
      temporary->next=nullptr;
      if(isEmpty()){ head=temporary; }             
      else
      {
        if(temporary->priority < head->priority) { temporary->next=head; head=temporary; }
        else
        {
          node* iterate = head;
          while(iterate->next != nullptr && (iterate->next)->priority <= temporary->priority) { iterate=iterate->next; }
          if(iterate->next == nullptr) { iterate->next = temporary; }
          else { temporary->next = iterate->next; iterate->next = temporary; }
        }
      }
      size++;
    }
    void dequeue()
    {
      if(isEmpty()) { return; }
      else
      {
        node* temporary = head;
        if(head->next==nullptr) { head=nullptr; }
        else { head=head->next; }
        delete temporary;
        size--;   
      }
    }
    string peek()
    {
      if(isEmpty()) { return ""; }
      else { return head->name; } 
    }
    int getSize() { return size; }
};

class BST
{
  private: //none
  public:
    BSTnode* root;
    BST() { root = nullptr; }
    bool empty() { return root == nullptr; }
    void add(string s)
    {
      BSTnode* n = new BSTnode;
      n->contents = s;
      n->l = nullptr;
      n->r = nullptr;
      if(root == nullptr) { root = n; }
      else { 
        BSTnode* iterate = root;
        bool added = false;
        while(!added) {
          if(s.size() > iterate->contents.size())
          {
            if(iterate->r == nullptr) { iterate->r = n; added = true; }
            else { iterate=iterate->r; }
          } else if (s.size() < iterate->contents.size())
          {
            if(iterate->l == nullptr) { iterate->l = n; added = true; }
            else { iterate=iterate->l; }
          } else {
            iterate->contents = s; added = true; 
          } 
        } 
      }
    }
    void post(BSTnode* current, ofstream &out)
    {
      if(current==nullptr) { return; }
      else {
        post(current->l, out); 
        post(current->r, out);
        out << current->contents << endl; 
      }
    }
    void pre(BSTnode* current, ofstream &out)
    {
      if(current==nullptr) { return; }
      else {
        out << current->contents << endl;
        pre(current->l, out); 
        pre(current->r, out);
      }
    }
    void in(BSTnode* current, ofstream &out)
    {
      if(current==nullptr) { return; }
      else
      {
        in(current->l, out); 
        out << current->contents << endl;
        in(current->r, out);
      }
    }
};

int main(int argc, char **argv)
{
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  linkedListQueue qp;
  BST binarySearchTree;
  queue<string> stringQueue;
  string temporary, order;

  while(getline(input, temporary)) {
    temporary.erase(remove(temporary.begin(), temporary.end(), '\n'), temporary.end());
    temporary.erase(remove(temporary.begin(), temporary.end(), '\r'), temporary.end());
    if(temporary.empty()) { continue; }
    if(temporary != "Preorder" && temporary != "Postorder" && temporary != "Inorder") {
      int x = stoi(temporary.substr(temporary.find("(")+1,temporary.find(")")-(1+temporary.find("("))));
      string y = temporary.substr(0,temporary.find("("));
      qp.enqueue(x,y);     
    }
  }
  order = temporary;
  ofstream output(am.get("output"));
  while(!qp.isEmpty())
  { 
    string s = qp.peek(); qp.dequeue();
    cout << s << endl;
    string cmd = s.substr(0,s.find(":"));
    cout << cmd << endl;
    if(cmd == "DECODE") {
      string toAdd = s.substr(s.find("["));
      toAdd = toAdd.substr(1,toAdd.size()-2);
      stringQueue.push(toAdd);
    }
    else if (cmd == "REPLACE") {
      if(stringQueue.empty()) { continue; }
      char one = s[9]; char two = s[11];
      string x = stringQueue.front(); stringQueue.pop();
      for(int i = 0; i < x.size(); i++) {
        if(x[i] == one) { x[i] = two; }
      }
      cout << x << endl;
      stringQueue.push(x);
    }
    else if (cmd == "REMOVE")
    {
      if(stringQueue.empty()) { continue; }
      char c = s[8];
      string x = stringQueue.front(); stringQueue.pop();
      x.erase(remove(x.begin(), x.end(), c),x.end());
      cout << x << endl;
      stringQueue.push(x);
    }
    else if (cmd == "SWAP")
    {
      if(stringQueue.empty()) { continue; }
      char one = s[6]; char two = s[8];
      vector<int> indexOne; vector<int> indexTwo;
      string x = stringQueue.front(); stringQueue.pop();
      for(int i = 0; i < x.size(); i++)
      {
        if(x[i] == one) { indexOne.push_back(i); }
        if(x[i] == two) { indexTwo.push_back(i); }
      }
      for(int i = 0; i < indexOne.size(); i++)
      {
        x[indexOne.at(i)] = two;  
      }
      for(int i = 0; i < indexTwo.size(); i++)
      {
        x[indexTwo.at(i)] = one; 
      }
      cout << x << endl;
      stringQueue.push(x);  
    }
    else if (cmd == "ADD")
    {
      if(stringQueue.empty()) { continue; }
      char addAfter = s[5]; char toAdd = s[7];
      string x = stringQueue.front(); stringQueue.pop();
      string result = "";
      for(int i = 0; i < x.size(); i++)
      {
        result += x[i];
        if(x[i] == addAfter) { result += toAdd; }
      }
      cout << result << endl;
      stringQueue.push(result);     
    }
    else if (cmd == "BST")
    { 
      if(stringQueue.empty()) { continue; }
      string x = stringQueue.front(); stringQueue.pop();
      binarySearchTree.add(x); 
    } 
  }
  if(!binarySearchTree.empty())
  {
    if(order == "Preorder") { binarySearchTree.pre(binarySearchTree.root, output); }
    else if (order == "Inorder") { binarySearchTree.in(binarySearchTree.root, output); }
    else if (order == "Postorder") { binarySearchTree.post(binarySearchTree.root, output); }
  }
}
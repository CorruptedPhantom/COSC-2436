using namespace std;
#include <iostream>
#include <fstream>
#include <cmath>

struct node
{
  int* keys; 
  int n; 
  bool isLeafNode;
  node** children;
  node(int degree)
  {
    keys = new int[degree - 1];
    children = new node* [degree];
    for(int x = 0; x < degree; x++)
      children[x] = nullptr;
    n = 0;
    isLeafNode = true;
  }

  node* insertAt(node* cu, node* temp, int value, int degree)
  {
    int index;
    if(isLeafNode == true)
    {
      index = degree;
      while(!keys[index - 1])
      {
        index--;
      }
      while(keys[index - 1] > value && index != 0)
      {
        keys[index] = keys[index - 1];
        index--;
      }
      keys[index] = value;
      n = n + 1;
    } else {
      index = 0;
      while(index < n && value > keys[index])
      {
        index++;
      }
      children[index]->insertAt(this, temp, value, degree);
    }
      if(n == degree)
      {
        if(this == temp)
        {
          node* splt = new node(degree);
          splt->children[0] = this;
          splt->isLeafNode = false;
          splt->split(this, degree);
          return splt;
        }
        else
        {
          cu->split(this, degree);
        }
      }
    return temp;
  }

  void split(node* s, int degree)
  {
      node* R = new node(degree);
      float val = ceil(float(degree) / 2);
      int WC = val;
      int next = (degree - 1) / 2;
      int indexR = 0;
      int carry = s->keys[next];
      int indexC = 0;
      int kc = s->n;
      for(int x = next + 1; x < kc; x++)
      {
        R->keys[indexR] = s->keys[x];
        indexR++;
        s->n = s->n - 1;
        R->n = R->n + 1;
      }
      if(s->isLeafNode == false)
      {
        for(int x = WC; x <= degree; x++)
        {
          R->children[indexC] = s->children[x];
          indexC++;
        }
        R->isLeafNode = s->isLeafNode;
      }
      int num = degree - 1;
      while(children[num] != s)
      {
        children[num + 1] = children[num];
        num--;
      }
      children[num + 1] = R;
      int x = degree - 1;
      while(!keys[x - 1] && x != 0)
      {
        x--;
      }
      while(keys[x - 1] > carry && x != 0)
      {
        keys[x] = keys[x - 1];
        x--;
      }
      keys[x] = carry;
      n = n + 1;
      s->n = s->n - 1;
  }

  class BTree
  {
    private:
      node *root;
      int degree;
    public:
      BTree(int deg)
      {
        root = nullptr;  
        degree = deg; 
      }
      node* getRoot()
      { 
        return root;
      }
      int height(node* cu)
      {
        while(cu != nullptr)
        {
          return height(cu->children[0]) + 1;
        }
        return 0;
      }
      bool dupCheck(node* cu, int val)
      {
        if(cu == nullptr)
        {
          return false;
        }
        for(int x = 0; x < cu->n; x++)
        {
          if(cu->keys[x] == val)
          {
            return true;
          }
        }
        for(int x = 0; x < cu->n + 1; x++)
        {
          if(dupCheck(cu->children[x], val) == true)
          {
            return true;
          }
        }
        return false;
      }
      void insert(int val)
      {
        if(dupCheck(root, val) == true)
        {
          return;
        }
        if(root == nullptr)
        {
          root = new node(degree);
          root->isLeafNode = true;
          root->keys[0] = val;
          root->n = 1;
        }
        else
        {
          root = root->insertAt(root, root, val, degree);
        }   
      }
      bool isLeaf(node* temp)
      {
        for(int x = 0; x < degree; x++)
        {
          if(temp->children[x] != nullptr)
          {
            return false;
          }
        }
        return true;
      }
      void print(node* cu, int level, ofstream& output)
      {
        if(cu == nullptr)
        {
          output << "EMPTY";
          return;
        }
        if(level > height(root))
        {
          output << "EMPTY";
          return;
        }
        if(level == 1)
        {
          if(cu == nullptr)
          {
            output << "EMPTY";
            return;
          }
          for(int x = 0; x < cu->n; x++)
          {
            output << cu->keys[x] << " ";
          }
        } else {
          for(int i = 0; i < cu->n + 1; i++)
          {
            print(cu->children[i], level - 1, output);
          }
        }
      }
  };
};
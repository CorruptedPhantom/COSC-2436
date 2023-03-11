#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node
{
  int value;
  node *l;
  node *r;
  int size;
};

class AVLTree {
 private:
  node *top;
  int getBalance(node *);
  int size(node *);
  node *newNode(int);
  node *leftRotate(node *);
  node *rightRotate(node *);
  node *insertHelper(node *, int);
  node *balanceTree(node *);
  void printLevel(node *top, ostream &o, int level, bool);

 public:
  AVLTree() { top = nullptr; };
  ~AVLTree();
  node *add(node *node, int value);
  node *remove(node *top, int value);
  node *getMin(node *) const;
  node *getTop() const { return top; };
  void print(node *, std::ostream &);
};

AVLTree::~AVLTree()
{
  while (top != nullptr)
  {
    top = remove(top, top->value);
  }
  delete top;
}

int AVLTree::size(node *n)
{
  if (n == nullptr) return 0;
  return n->size;
}

node *AVLTree::newNode(int value)
{
  node *n = new node;
  n->value = value;
  n->l = nullptr;
  n->r = nullptr;
  n->size = 1;
  return n;
}

int AVLTree::getBalance(node *n)
{
  if (n == nullptr) return 0;
  return size(n->l) - size(n->r);
}

node *AVLTree::getMin(node *n) const
{
  node *current = n;
  while (current->l != nullptr) current = current->l;
  return current;
}

node *AVLTree::leftRotate(node *x)
{
  node *y = x->r;
  node *T2 = y->l;
  y->l = x;
  x->r = T2;
  x->size = max(size(x->l), size(x->r)) + 1;
  y->size = max(size(y->l), size(y->r)) + 1;
  return y;
}

node *AVLTree::rightRotate(node *y)
{
  node *x = y->l;
  node *T2 = x->r;
  x->r = y;
  y->l = T2;
  y->size = max(size(y->l), size(y->r)) + 1;
  x->size = max(size(x->l), size(x->r)) + 1;
  return x;
}

node *AVLTree::balanceTree(node *n) { return n; }

node *AVLTree::add(node *node, int value)
{
  top = insertHelper(node, value);
  return top;
}

node *AVLTree::insertHelper(node *node, int value)
{
  if (node == nullptr) return newNode(value);
  if (value < node->value)
    node->l = add(node->l, value);
  else if (value > node->value)
    node->r = add(node->r, value);
  else
    return node;
  node->size = max(size(node->l), size(node->r)) + 1;
  int BF = getBalance(node);
  if (BF > 1)
  {
    if (value < node->l->value)
    {
      return rightRotate(node);
    } else if (value > node->l->value)
    {
      node->l = leftRotate(node->l);
      return rightRotate(node);
    }
  }
  if (BF < -1)
  {
    if (value > node->r->value)
    {
      return leftRotate(node);
    } else if (value < node->r->value)
    {
      node->r = rightRotate(node->r);
      return leftRotate(node);
    }
  }
  return node;
}

node *AVLTree::remove(node *top, int value)
{
  if (top == nullptr) return top;
  if (value < top->value)
    top->l = remove(top->l, value);
  else if (value > top->value)
    top->r = remove(top->r, value);
  else {
    if ((top->l == nullptr) || (top->r == nullptr))
    {
      node *temp = top->l ? top->l : top->r;
      if (temp == nullptr)
      {
        temp = top;
        top = nullptr;
      } else
        *top = *temp;
      delete temp;
    } else {
      node *temp = getMin(top->r);
      top->value = temp->value;
      top->r = remove(top->r, temp->value);
    }
  }

  if (top == nullptr) return top;

  top->size = max(size(top->l), size(top->r)) + 1;
  int BF = getBalance(top);
  if (BF > 1)
  {
    if (getBalance(top->l) >= 0)
    {
      return rightRotate(top);
    } else {
      top->l = leftRotate(top->l);
      return rightRotate(top);
    }
  }
  if (BF < -1) {
    if (getBalance(top->r) <= 0)
    {
      return leftRotate(top);
    } else {
      top->r = rightRotate(top->r);
      return leftRotate(top);
    }
  }
  return top;
}

void AVLTree::printLevel(node *top, std::ostream &o, int level, bool firstEntry)
{
  if (top == nullptr) return;
  if (level == 1)
    firstEntry ? o << top->value : o << " " << top->value;
  else if (level > 1)
  {
    printLevel(top->l, o, level - 1, false);
    printLevel(top->r, o, level - 1, false);
  }
}

void AVLTree::print(node *top, std::ostream &o)
{
  int h = size(top);
  for (int i = 1; i <= h; i++)
  {
    i == 1 ? printLevel(top, o, i, true) : printLevel(top, o, i, false);
  }
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  AVLTree tree;
  int num;
  input >> num;
  num = 0;
  while (input.peek() != EOF) {
    input >> num;
    tree.add(tree.getTop(), num);
  }
  tree.print(tree.getTop(), output);
}
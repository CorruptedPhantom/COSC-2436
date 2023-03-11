#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

template <typename T> struct node //node template initializer
{
  T data;
  node<T> *next;
};

template <typename T> class linkedList //linkedList template initializer
{
  private: //private variables
    node<T> *head;
    int length;
  public: //public variables
    linkedList(); //constructor
   ~linkedList(); //destructor
    void addFront(T value); //function for adding a node to the front
    void addEnd(T value); //function for adding a node to the end
    void removeFront(); //function for removing a node from the front
    void removeEnd(); //function for removing a node from the end
    void print(ofstream &output); //function for outputting linkedList to output.txt
};

template <typename T> linkedList<T>::linkedList() //constructor for linkedList
{
  head = nullptr; //initializing the head variable
  length = 0; //initializing length variable
}
template <typename T> linkedList<T>::~linkedList() //destructor for linkedList
{
  node<T> *cur = head;
  while (cur != nullptr) //while there is still data in the linked list
  {
    node<T> *temp = cur;
    cur = cur->next;
    delete temp; //delete the data
  }
}
template <typename T> void linkedList<T>::addFront(T value) //function for adding a node to the front
{
  node<T> *temp = new node<T>(); //create a new node
  temp->data = value; //assign the new data to the new node
  temp->next = head; //make it the head of the list
  head = temp; //set head = to temp (the new node)
  length++; //increase length by 1 to reflect the changes made to the linkedList
}
template <typename T> void linkedList<T>::addEnd(T value) //function for adding a node to the end
{
  node<T> *temp = new node<T>(); //create a new node
  temp->data = value; //assign the new data to the new value
  temp->next = nullptr; //make it the last node in the list

  node<T> *cur = head;
  if (cur == nullptr) { //if it is the only value in the list
    head = temp; //set the new Node as the head of the list
  } else {
    while (cur->next != nullptr) //otherwise
    {
      cur = cur->next; //make a new node at the end
    }
    cur->next = temp; //set the new node as the linkedList's newly created node
  }
  length++; //increase length by 1 to reflect the changes made to the linkedList
}
template <typename T> void linkedList<T>::removeFront() //function for removing a node at the front
{
  node<T> *temp = new node<T>();
  node<T> *cur = head;
  if(cur == nullptr){return;} //return if it is already null (no data)
  temp = head;
  head = head->next;
  length--; //decrease length by 1 to reflect the changes made to the linkedList
}
template <typename T> void linkedList<T>::removeEnd() //function for removing a node at the end
{
  node<T> *cur = head;
  node<T> *prev = nullptr;
  if (cur == nullptr){return;} //return if it is already null (no data)
  else if (cur->next == nullptr) { //if next node is null (no data)
    head = nullptr; //set current node to null (the node we wish to removel)
  }
  else //otherwise
  {
    while (cur->next != nullptr) //while there is data after the current node
    {
      prev = cur; //set current node as previous
      cur = cur->next; //move on to next node
    }
    prev->next = nullptr; //once while loop is done, set current node to null (no data)
    delete cur; //delete the current node
  }
  length--;
}
template <typename T> void linkedList<T>::print(ofstream &output) //function for printing out linkedList
{
  node<T> *cur = head;
  while (cur != nullptr)
  {
    output << cur->data;
    if (cur->next != nullptr)
      output << " ";
    cur = cur->next;
  }
}

int main(int argc, char *argv[]) { //start of TA-provided code
  ArgumentManager am(argc, argv); 
  ifstream input(am.get("input"));
  ifstream command(am.get("command"));
  ofstream output(am.get("output"));
  
  vector <string> inputVector; //holds the input
  string in = "";
  while (getline(input, in))
  {
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    inputVector.push_back(in);
  } //end of TA-provided code
//read the first line, depending on what it is initialize vector "theList" to contain the data and prepare the linkedList
  if (inputVector[0] == "string"){ //if the first line is string
    linkedList<string> theList; //initialize the vector as a string vector
    if (inputVector[1] == "head"){ //if the second line is head
      theList.addFront(inputVector[2]); //add the third line to the front of the "theList" vector
        for (int x = 3; x < inputVector.size();x++) //for the rest of the vector
        {
          if(inputVector[x] == "remove head") //if the current line says remove head
          {
            theList.removeFront(); //remove the very first node
          }
          else if(inputVector[x] == "remove tail") //if the current line says remove tail
          {
            theList.removeEnd(); //remove the very last node
          }
          else //otherwise
          {
            theList.addFront(inputVector[x]); //add the data to the very first node
          }
      }
    }
    else if (inputVector[1] == "tail"){ //if the second line is tail
      theList.addEnd(inputVector[2]); //add the third line to the end of the "theList" vector
        for (int x = 3; x < inputVector.size();x++) //for the rest of the vector
        {
          if(inputVector[x] == "remove head") //if the current line says remove head
          {
            theList.removeFront(); //remove the very first node
          }
          else if(inputVector[x] == "remove tail") //if the current line says remove tail
          {
            theList.removeEnd(); //remove the very last node
          }
          else //otherwise
          {
            theList.addEnd(inputVector[x]); //add the data to the very last node
          }
      }
    }
    theList.print(output); //output the list
  }
  
  if (inputVector[0] == "int"){ //if the first line is int
    linkedList<int> theList; //initialize the vector as an int vector
    if (inputVector[1] == "head"){ //if the second line is head
      theList.addFront(stoi(inputVector[2])); //add the third line to the front of the vector
      for (int x = 3; x < inputVector.size();x++) //for the rest of the vector
      {
        if(inputVector[x] == "remove head") //if the line is remove head
        {
          theList.removeFront(); //remove the first node in the linked list
        }
        else if(inputVector[x] == "remove tail") //if the line is remove tail
        {
          theList.removeEnd(); //remove the last node in the linked list
        }
        else{
          theList.addFront(stoi(inputVector[x])); //add the data to the very first node
        }
      }
    }
    else if (inputVector[1] == "tail") //if the second line is tail
    {
      theList.addEnd(stoi(inputVector[2])); //add the third line to the end of the linked list
        for (int x = 3; x < inputVector.size();x++) //for the rest of the vector
        {
        if(inputVector[x] == "remove head") //if the line is remove head
        {
          theList.removeFront(); //remove the very first node
        }
        else if(inputVector[x] == "remove tail") //if the line is remove
        {
          theList.removeEnd(); //remove the very last node
        }
        else //otherwise
        {
          theList.addEnd(stoi(inputVector[x])); //add the line to the very end
        }
      }
    } 
    theList.print(output); //output the list
  }

  if (inputVector[0] == "char") //if the first line is char
  {
    linkedList<char> theList; //initialize the vector as a char vector
    if (inputVector[1] == "head") //if the second line is head
    {
      theList.addFront(inputVector[2][0]); //add at the beginning (the vector is 2-dimensional, in which the first dimension holds the line and the second holds the char)
      for (int x = 3; x < inputVector.size();x++) //for the rest of the vector
      {
        if(inputVector[x] == "remove head") //if the line is remove head
        {
          theList.removeFront(); //remove the very first node
        }
        else if(inputVector[x] == "remove tail") //if the line is remove tail
        {
          theList.removeEnd(); //remove the very last node
        }
        else //otherwise
        {
          theList.addFront(inputVector[x][0]); //add at the end
        }
      }
    }
    else if (inputVector[1] == "tail") //if the second line is tail
    {
      theList.addEnd(inputVector[2][0]); //add at the end (the vector is 2-dimensional, in which the first dimension holds the line and the second holds the char)
      for (int x = 3; x < inputVector.size();x++) //for the rest of the vector
      {
        if(inputVector[x] == "remove head") //if the line is remove head
        {
          theList.removeFront(); //remove the very first node
        }
        else if(inputVector[x] == "remove tail") //if the line is remove tail
        {
          theList.removeEnd(); //remove the very last node
        }
        else //otherwise
        {
          theList.addEnd(inputVector[x][0]); //add the node to the very end
        }
      }
    } 
    theList.print(output); //output the linked list
  }
  return 0; //return 0 as a failsafe
}
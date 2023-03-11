#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

template <typename T>
struct node //initialize structure
{
    T data;
    node<T> *next;
};

template <typename T>
class linkedList //initialize class
{
private:
    node<T> *head;
    int size;
public:
    linkedList(); //initialize constructor
    ~linkedList(); //initialize destructor
    bool isEmpty() { return head == nullptr; } //check if linkedList is empty
    int getSize() { return size; } //return the size of the linkedList
    node<T> getHead() const { return head; } //returns head of the linkedList
    void addFront(T value); //add value to the front of the linkedList
    void append(T value); //add value to the end of the linkedList
    void removeFront(); //remove the first node
    void removeEnd(); //remove the last node
    void removeIndex(int position); //remove node at specified index
    void addIndex(T value, int position); //add node at specified index
    node<T> *returnIndex(int position);  //return index of specified value
    int search(string toSearch); //search a specific value
    void swap(node<T> *n1, node<T> *n2); //swap two values
    void sort(string type); //sort the linkedlist based on the type
    void output(std::ostream &out); //output the entire linked list
};

template <typename T>
linkedList<T>::linkedList() //constructor
{
    head = nullptr;
    size = 0;
}

template <typename T>
linkedList<T>::~linkedList() //destructor
{
    node<T> *current = head; //set current node as the head
    while (current != nullptr) //while current node exists
    {
        node<T> *temporary = current; //set temporary node as current
        current = current->next; //move on to next node
        delete temporary; //delete previous node (temporary)
    }
}

template <typename T>
void linkedList<T>::addFront(T value) //add to the front of the linkedList
{

    node<T> *temporary = new node<T>(); //create a new node temporary
    temporary->data = value; //move data inside temporary
    temporary->next = head; //make the next node after temporary the head
    head = temporary; //set head to temporary
    size++; //increase size by 1
}

template <typename T>
void linkedList<T>::append(T value) //add to the end of the linkedList
{

    node<T> *temporary = new node<T>(); //initialize temporary as new node
    temporary->data = value; //move data inside temporary
    temporary->next = nullptr; //make next node after temporary the head
    node<T> *current = head; //set current node as temporary
    if (current == nullptr) //if current doesnt exist
    {
        head = temporary; //set head to temporary
    }
    else
    {
        while (current->next != nullptr) //while the next node exists
        {
            current = current->next; //move on to next node
        }
        current->next = temporary; //set previous node as the temporary node
    }
    size++; //add 1 to size
}

template <typename T>
void linkedList<T>::removeFront() //remove a node from the front
{
    if (head == nullptr) //if head doesnt exist
        return; //return
    else
    {
        delete head; //delete the head node
        head = head->next; //set head to new 1st node
        size--; //remove 1 from size
    }
}

template <typename T>
void linkedList<T>::removeEnd() //remove node from the end
{
    node<T> *current = head; //set current node to head
    node<T> *previous = nullptr; //set previous node to null (no data)
    if (current == nullptr) //if current node has no data
        return; //return
    else if (current->next == nullptr) //if next node node doesnt exist
    {
        head = nullptr; //set head to null (no data)
    }
    else
    {
        while (current->next != nullptr) //while next node exists
        {
            previous = current; //set previous node as current
            current = current->next; //move on to next
        }
        previous->next = nullptr; //set next node after previous (current) as no data
        delete current; //delete current node
    }
    size--; //remove 1 from size
}

template <typename T>
void linkedList<T>::removeIndex(int position) //remove value from a certain index
{
    int currentIndex = 0; //initialize currentIndex
    node<T> *current = head; //set current node as head
    node<T> *previous = nullptr; //set previous node to null (no data)
    node<T> *next = head->next; //initialize head ndoe
    if (position == 0) //if the position = 0
    {
        removeFront(); //remove the head node
    }
    else
    {
        while (currentIndex < position) //while currentIndex is less than position
        {
            previous = current; //set previous node as current
            next = next->next; //set next as next node
            current = current->next; //move on to next node
            currentIndex++; //increase currentIndex
        }

        if (currentIndex == position) //if currentIndex is = to position
        {
            previous->next = next; //set the next node after previous = next
            current->next = nullptr; //set the next node after current as null (no data)
            delete current; //delete
        }
        size--; //remove 1 from size
    }
}

template <typename T>
void linkedList<T>::addIndex(T value, int position) //add value at certain inde
{
    node<T> *temporary = new node<T>(); //initialize temproary node
    temporary->data = value; //add data 
    temporary->next = nullptr; //set next node after temporary to null
    node<T> *current = head; //set current node as head
    node<T> *previous = nullptr; //set previous node as null (no data)

    if (position == 0) //if the position = 0
    {
        head = temporary; //set head as temporary node
        temporary->next = current; //set next node after temporary as current
    }
    else if (position > size) //else if position > size
        return; //return
    else
    {
        for (int i = 0; i < position; i++)
        {
            previous = current; //set previous node as current
            current = current->next; //move on to next node
        }
        previous->next = temporary; //set next node after previous as temporary
        temporary->next = current; //set next node after temporary = to current
    }
    size++; //increase size by 1
}

template <typename T>
int linkedList<T>::search(string toSearch) //search a certain string
{
    node<T> *current = head; //initialize current node as head
    int index = 0; //initialize index
    while (current != nullptr) //while current exists
    {
        if (current->data.find(toSearch) != string::npos) //checking if current is found in the linkedList
            return index; //return index
        current = current->next; //move on to next node
        index++; //add 1 to index
    }
    return -1; //if all else fails, return -1 (exit)
}

template <typename T>
node<T> *linkedList<T>::returnIndex(int position) //return index
{
    node<T> *current = head; //set current node as head
    while (position > 0) //while position > 0
    {
        current = current->next; //move on to next node
        position--; //subtract 1 from position
    }
    return current; //return current node
}

template <typename T>
void linkedList<T>::sort(string type) //sort
{
    if (type == "id") //if type == id
    {
        int i, j, n = getSize(); //initialize variables i/j/n
        for (i = 0; i < n; i++)
            for (j = 0; j < n - i - 1; j++)
                if (stoi(returnIndex(j)->data.substr(returnIndex(j)->data.find(":") + 1, 4)) > stoi(returnIndex(j + 1)->data.substr(returnIndex(j + 1)->data.find(":") + 1, 4))) //
                    swap(returnIndex(j), returnIndex(j + 1)); //swap
    }

    else if (type == "username") //if type == id
    {
        int i, j, n = getSize(); //initialize i/j/n
        int startIndex1, startIndex2, endIndex1, endIndex2, smallestLength; //initialize startIndex1/2, endIndex1/2, smallestLength
        string string1, string2; //initialize string1/string2
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                startIndex1 = returnIndex(j)->data.find("username:") + 9; //
                endIndex1 = returnIndex(j)->data.find(";", startIndex1); //
                string1 = returnIndex(j)->data.substr(startIndex1, endIndex1 - startIndex1); //
                startIndex2 = returnIndex(j + 1)->data.find("username") + 9; //
                endIndex2 = returnIndex(j + 1)->data.find(";", startIndex2); //
                string2 = returnIndex(j + 1)->data.substr(startIndex2, endIndex2 - startIndex2); //
                if (string1.compare(string2) > 0) //
                {
                    swap(returnIndex(j), returnIndex(j + 1)); //
                }

                else if (string1.compare(string2) == 0) //
                {
                    startIndex1 = returnIndex(j)->data.find("score:") + 6; //
                    endIndex1 = returnIndex(j)->data.find(";", startIndex1); //
                    string1 = returnIndex(j)->data.substr(startIndex1, endIndex1 - startIndex1); //
                    startIndex2 = returnIndex(j + 1)->data.find("score:") + 6; //
                    endIndex2 = returnIndex(j + 1)->data.find(";", startIndex2); //
                    string2 = returnIndex(j + 1)->data.substr(startIndex2, endIndex2 - startIndex2); //
                    int score1 = stoi(string1), score2 = stoi(string2); //
                    if (score1 < score2) //if score1 < score2
                        swap(returnIndex(j), returnIndex(j + 1)); //swap
                }
            }
        }
    }
    else if (type == "grade") //if type == grade
    {
        int i, j, n = getSize(); //initialize 
        int startIndex1, startIndex2, endIndex1, endIndex2, smallestLength; //initialize
        string string1, string2; //initialize
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                startIndex1 = returnIndex(j)->data.find("grade:") + 5; //
                endIndex1 = returnIndex(j)->data.find(";", startIndex1); //
                string1 = returnIndex(j)->data.substr(startIndex1, endIndex1 - startIndex1); //
                startIndex2 = returnIndex(j + 1)->data.find("grade:") + 5; //
                endIndex2 = returnIndex(j + 1)->data.find(";", startIndex2); //
                string2 = returnIndex(j + 1)->data.substr(startIndex2, endIndex2 - startIndex2); //
                if (string1 > string2) //if string1 > string2
                    swap(returnIndex(j), returnIndex(j + 1)); //swap
            }
        }
    }

    else if (type == "score") //if type == score
    {
        int i, j, n = getSize(); //initialize
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                int startIndex1 = returnIndex(j)->data.find("score:") + 6, endIndex1 = returnIndex(j)->data.find(";", startIndex1); //
                string string1 = returnIndex(j)->data.substr(startIndex1, endIndex1 - startIndex1); //
                int startIndex2 = returnIndex(j + 1)->data.find("score:") + 6, endIndex2 = returnIndex(j + 1)->data.find(";", startIndex2); //
                string string2 = returnIndex(j + 1)->data.substr(startIndex2, endIndex2 - startIndex2); //
                int score1 = stoi(string1), score2 = stoi(string2); //
                if (score1 < score2) //if score1 < score2
                    swap(returnIndex(j), returnIndex(j + 1)); //swap
            }
        }
    }
}

template <typename T>
void linkedList<T>::swap(node<T> *n1, node<T> *n2) //swap
{

    int index1 = search(n1->data), index2 = search(n2->data); //initialize
    T tempVar1 = returnIndex(index1)->data; //initialize
    addIndex(returnIndex(index2)->data, index1); //add node
    removeIndex(index1 + 1); //remove node
    addIndex(tempVar1, index2); //add node
    removeIndex(index2 + 1); //remove node
}

template <typename T>
void linkedList<T>::output(ostream &out) //ouput
{
    node<T> *current = head; //set current node as head
    while (current != nullptr) //while current exists
    {
        (current->next == nullptr) ? (out << current->data) : (out << current->data << endl); //ouput node
        current = current->next; //move to next node
    }
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ifstream cmd(am.get("command"));
    ofstream out(am.get("output"));
    
    linkedList<string> credentials;
    string in;

    while (getline(input, in))
    {
        in.erase(remove(in.begin(), in.end(), '\n'), in.end());
        in.erase(remove(in.begin(), in.end(), '\r'), in.end());
        in.erase(remove(in.begin(), in.end(), ' '), in.end());
        if (in.find("id:") != string::npos)
        {
            if (in.find("username:", in.find("id:") + 3) != string::npos)
            {
                if (in.find("score:", in.find("username:") + 8) != string::npos)
                {
                    if (in.find("grade:", in.find("score:") + 5) != string::npos)
                    {
                        cout << in << " Passes." << endl;
                        bool usernamesMatch = false, idsMatch = false;
                        if (credentials.getSize() == 0)
                        {
                            cout << in << " Added (size 0)" << endl;
                            credentials.append(in);
                        }
                        else if (credentials.getSize() > 0)
                        {
                            for (int x = 0; x < credentials.getSize(); x++)
                            {

                                int startIndex1 = in.find("username:") + 9, startIndex2 = credentials.returnIndex(x)->data.find("username:") + 9;
                                int endIndex1 = in.find(";", startIndex1), endIndex2 = credentials.returnIndex(x)->data.find(";", startIndex2);
                                string str1 = in.substr(startIndex1, endIndex1 - startIndex1), str2 = credentials.returnIndex(x)->data.substr(startIndex2, endIndex2 - startIndex2);
                                if (str1.compare(str2) == 0)
                                    usernamesMatch = true;

                                startIndex1 = in.find("ids:") + 4, startIndex2 = credentials.returnIndex(x)->data.find("ids:") + 4;
                                endIndex1 = in.find(";", startIndex1), endIndex2 = credentials.returnIndex(x)->data.find(";", startIndex2);
                                str1 = in.substr(startIndex1, endIndex1 - startIndex1), str2 = credentials.returnIndex(x)->data.substr(startIndex2, endIndex2 - startIndex2);
                                if (str1.compare(str2) == 0 && !usernamesMatch)
                                {
                                    idsMatch = true;
                                    cout << in << " Added (ID Match)" << endl;
                                    credentials.removeIndex(x);
                                    credentials.addIndex(in, x);
                                }
                            }
                            if (!usernamesMatch && !idsMatch && credentials.search(in) < 0)
                            {
                                credentials.append(in);
                                cout << in << " Added (No User/ID Match)" << endl;
                            }
                        }
                    }
                }
            }
        }
        else if (in == "")
        {
            credentials.append(in);
        }
    }
    if (cmd.peek() != EOF)
    {
        string sortType;
        string in;
        while (getline(cmd, in))
        {
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            if (in.find("Add") != string::npos)
            {
                int index = stoi(in.substr(in.find("(") + 1, in.find(")") - in.find("(") - 1));
                string toAdd = in.substr(in.find("["), (in.find("]") - in.find("[") + 1));
                if (toAdd.find("id:") != string::npos && toAdd.find("username:") != string::npos && toAdd.find("score:") != string::npos && toAdd.find("grade:") != string::npos)
                {
                    if (index <= credentials.getSize())
                    {
                        cout << "index:" << index << " toAdd: " << toAdd << endl;

                        for (int x = 0; x < credentials.getSize(); x++)
                        {
                            if (toAdd.substr(toAdd.find(":") + 1, 4).compare(credentials.returnIndex(x)->data.substr(credentials.returnIndex(x)->data.find(":") + 1, 4)) == 0)
                            {
                                cout << "Added " << toAdd << endl;
                                credentials.removeIndex(x);
                                credentials.addIndex(toAdd, x);
                            }
                        }

                        cout << "Passed the id check" << endl;
                        bool usernamesMatch = false, idsMatch = false;
                        if (credentials.getSize() == 0 && index <= credentials.getSize())
                        {
                            cout << "Added (NO VALUES)" << toAdd << endl;
                            credentials.addFront(toAdd);
                        }

                        else if (credentials.getSize() > 0 && index <= credentials.getSize())
                        {

                            for (int x = 0; x < credentials.getSize(); x++)
                            {
                                idsMatch = false;
                                int startIndex1 = toAdd.find("username:") + 9, startIndex2 = credentials.returnIndex(x)->data.find("username:") + 9;
                                int endIndex1 = toAdd.find(";", startIndex1), endIndex2 = credentials.returnIndex(x)->data.find(";", startIndex2);
                                string str1 = toAdd.substr(startIndex1, endIndex1 - startIndex1), str2 = credentials.returnIndex(x)->data.substr(startIndex2, endIndex2 - startIndex2);
                                if (str1.compare(str2) == 0)
                                    usernamesMatch = true;

                                startIndex1 = toAdd.find("ids:") + 4, startIndex2 = credentials.returnIndex(x)->data.find("ids:") + 4;
                                endIndex1 = toAdd.find(";", startIndex1), endIndex2 = credentials.returnIndex(x)->data.find(";", startIndex2);
                                str1 = toAdd.substr(startIndex1, endIndex1 - startIndex1), str2 = credentials.returnIndex(x)->data.substr(startIndex2, endIndex2 - startIndex2);
                                if (str1.compare(str2) == 0)
                                    idsMatch = true;

                                if (idsMatch && !usernamesMatch)
                                {
                                    cout << toAdd << "Added (ID MATCH)" << endl;
                                    credentials.removeIndex(x);
                                    credentials.addIndex(toAdd, x);
                                }
                            }

                            if (!usernamesMatch && !idsMatch && credentials.search(toAdd) < 0)
                            {
                                cout << toAdd << "Added (NO USER/ ID MATCH)" << endl;
                                credentials.addIndex(toAdd, index);
                            }
                        }
                    }
                }
            }
            else if (in.find("Remove") != string::npos)
            {
                string toFind = in.substr(in.find("(") + 1, in.find(")") - in.find("(") - 1);
                cout << "\n"
                     << toFind << " String to Delete" << endl;
                while (credentials.search(toFind) > -1)
                {
                    cout << "Removing " << credentials.returnIndex(credentials.search(toFind))->data << endl;
                    credentials.removeIndex(credentials.search(toFind));
                }
            }
            else if (in.find("Sort") != string::npos)
            {
                credentials.sort(in.substr(in.find("(") + 1, in.find(")") - in.find("(") - 1));
                sortType = in.substr(in.find("(") + 1, in.find(")") - in.find("(") - 1);
            }
        }
        credentials.output(out);
    }
    return 0;
}
#include <vector>
#include <fstream>
#include <iostream>
#include "ArgumentManager.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

bool isSolved(vector<vector<char>> &matrix, size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
            if (matrix[i][j] == 'B')
                return false;

    return true;
}

void moveUp(vector<vector<char>> &matrix, size_t row, size_t col)
{
    Stack s;
    int counter = 0;
    char temp;

    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            if (matrix[i][j] != 'O' && matrix[i][j] != 'X')
            {
                if (!s.isEmpty() && s.peek() == 'B')
                {
                    temp = s.pop();
                    s.push('X');
                }
                else
                    s.push(matrix[i][j]);
            }
            else if (matrix[i][j] == 'X')
            {
                while (s.getSize() < counter)
                    s.push('O');
                s.push('X');
            }
            counter++;
        }

        while (s.getSize() < counter)
            s.push('O');

        for (int i = row - 1; i >= 0; i--)
            matrix[i][j] = s.pop();

        counter = 0;
    }
}

void moveDown(vector<vector<char>> &matrix, size_t row, size_t col)
{
  Stack s;
  int counter = 0;
  char temp;

  for (int j = 0; j < col; j++)
    {
        for (int i = row - 1; i >= 0; i--)
        {
            if (matrix[i][j] != 'O' && matrix[i][j] != 'X')
            {
                if (!s.isEmpty() && s.peek() == 'B')
                {
                    temp = s.pop();
                    s.push('X');
                }
                else
                    s.push(matrix[i][j]);
            }
            else if (matrix[i][j] == 'X')
            {
                while (s.getSize() < counter)
                    s.push('O');
                s.push('X');
            }
            counter++;
        }

        while (s.getSize() < counter)
            s.push('O');

        for (int i = 0; i < row; i++)
            matrix[i][j] = s.pop();

        counter = 0;
    }
}

void moveLeft(vector<vector<char>> &matrix, size_t row, size_t col)
{
  Stack s;
  int counter = 0;
  char temp;

  for (int j = 0; j < row; j++)
    {
        for (int i = 0; i < col; i++)
        {
            if (matrix[j][i] != 'O' && matrix[j][i] != 'X')
            {
                if (!s.isEmpty() && s.peek() == 'B')
                {
                    temp = s.pop();
                    s.push('X');
                }
                else
                    s.push(matrix[j][i]);
            }
            else if (matrix[j][i] == 'X')
            {
                while (s.getSize() < counter)
                    s.push('O');
                s.push('X');
            }
            counter++;
        }

        while (s.getSize() < counter)
            s.push('O');

        for (int i = col - 1; i >= 0; i--)
            matrix[j][i] = s.pop();

        counter = 0;
    }
}

void moveRight(vector<vector<char>> &matrix, size_t row, size_t col)
{
  Stack s;
  int counter = 0;
  char temp;

  for (int j = 0; j < row; j++)
    {
        for (int i = col - 1; i >= 0; i--)
        {
            if (matrix[j][i] != 'O' && matrix[j][i] != 'X')
            {
                if (!s.isEmpty() && s.peek() == 'B')
                {
                    temp = s.pop();
                    s.push('X');
                }
                else
                    s.push(matrix[j][i]);
            }
            else if (matrix[j][i] == 'X')
            {
                while (s.getSize() < counter)
                    s.push('O');
                s.push('X');
            }
            counter++;
        }

        while (s.getSize() < counter)
            s.push('O');

        for (int i = 0; i < col; i++)
            matrix[j][i] = s.pop();

        counter = 0;
    }
}

void addPath(Queue &q, Pair p, int move, size_t row, size_t col)
{
    Pair temp;
    temp.matrix = p.matrix;
    temp.moves = p.moves;

    switch (move)
    {
    case 1:
        moveUp(temp.matrix, row, col);
        if (temp.matrix != p.matrix)
        {
            temp.moves += "1";
            q.enqueue(temp);
        }
        break;

    case 2:
        moveRight(temp.matrix, row, col);
        if (temp.matrix != p.matrix)
        {
            temp.moves += "2";
            q.enqueue(temp);
        }
        break;

    case 3:
        moveDown(temp.matrix, row, col);
        if (temp.matrix != p.matrix)
        {
            temp.moves += "3";
            q.enqueue(temp);
        }
        break;

    case 4:
        moveLeft(temp.matrix, row, col);
        if (temp.matrix != p.matrix)
        {
            temp.moves += "4";
            q.enqueue(temp);
        }
        break;
    }
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    size_t row;
    size_t col;
    input >> row;
    input >> col;
    vector<vector<char>> matrix;

    for (int i = 0; i < row; i++)
    {
        vector<char> temp;
        for (int j = 0; j < col; j++)
        {
            char c;
            input >> c;
            temp.push_back(c);
        }
        matrix.push_back(temp);
    }

    Pair temp;
    temp.matrix = matrix;
    temp.moves = "";

    Queue q;
    q.enqueue(temp);

    while (!q.isEmpty())
    {
        temp = q.dequeue();
        if (isSolved(temp.matrix, row, col))
        {
            if (temp.moves == "") {
                cout << 0;
                output << 0;
            }
            else {
                cout << 0;
                output << temp.moves;
            }
            break;
        }
        else
        {
            addPath(q, temp, 1, row, col);
            addPath(q, temp, 2, row, col);
            addPath(q, temp, 3, row, col);
            addPath(q, temp, 4, row, col);
        }
    }

    return 0;
}
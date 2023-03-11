#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char *argv[])
{
    // *** You need to open files using argumentmanager when submit your assignment ***
    //ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ifstream command(am.get("command"));
    // ofstream out(am.get("output"));

    // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
    ifstream input("input2.txt");
    ifstream command("command2.txt");
    ofstream out("output2.txt");

    string in = "";
    int num = 0;
    vector<string> lines;
    vector<string> vectorID;
    vector<string> keyValues;
    vector<string> replacements;
    vector<string> cmds;
    vector<string> postCmd;

    if (input.peek() != EOF)
    {
        while (getline(input, in))
        {
            // Clean up blank spaces, \n and \r, and skip blank lines
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in.size() == 0)
                continue;

            // continue to process the input below
            // Ensuring the entry is valid, if valid add to lines vector
            int num = 0;
            if (in.find(";id:") != string::npos) // If ;id: is present
            {
                if (isalpha(in[0]))
                {
                    for (auto entry : in)
                    {
                        if (!isalpha(entry) && !isdigit(entry) && entry != ';' && entry != ':' && entry != '#')
                        {
                            num++;
                        }
                    }
                    if (num == 0)
                    {
                        lines.push_back(in);
                    }
                }
            }
        }

        // Cutting up the lines and putting ids into their own vectors
        for (auto line : lines)
        {
            string id = line.substr(line.find(";id:") + 4, line.length() - 1);
            vectorID.push_back(id);
            string lineChar = line.substr(0, line.find("id:"));
            keyValues.push_back(lineChar);
        }
        // Decoding the ids and characters and putting them into a vector
        for (int x = 0; x < vectorID.size(); x++)
        {
            string replacement = "";
            for (int y = 0; y < vectorID.at(x).length(); y++)
            {
                char selectedChar = vectorID.at(x).at(y);
                if (isdigit(selectedChar))
                {
                    replacement += selectedChar;
                }
                else if (isalpha(selectedChar))
                {
                    if (keyValues.at(x).find(selectedChar) != string::npos)
                    {
                        int startValue = keyValues.at(x).find(selectedChar) + 2;
                        int endValue = keyValues.at(x).find(';', startValue);
                        replacement += keyValues.at(x).substr(startValue, endValue - startValue);
                    }
                }
                else if (selectedChar == '#')
                    replacement += "#";
            }

            // Replacing the # with the index of the character
            vector<int> hashtag;
            int lastIndex = 0;
            while (replacement.find('#', lastIndex) != string::npos)
            {
                lastIndex = replacement.find('#', lastIndex);
                hashtag.push_back(lastIndex++);
            }
            while (!hashtag.empty())
            {
                replacement.insert(hashtag.back(), to_string(hashtag.back()));
                hashtag.pop_back();
            }
            while (replacement.find('#') != string::npos)
            {
                replacement.erase(replacement.find('#'), 1);
            }
            replacements.push_back(replacement);
        }

        // Handling command cases
        string cmd = "";
        num = 0;

        while (getline(command, cmd))
        {
            // Clean up blank spaces, \n and \r, and skip blank lines
            cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
            cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
            cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());
            if (cmd.size() == 0)
                continue;

            // continue to process the command below
            cmds.push_back(cmd);
        }

        // Finding the valid indexes within replacements and putting them into correctIndex
        // Taking the lines from each cmd and puttings the cmdFirst and cmdLast into their own indexes
        vector<string> commandFirst, commandLast;
        vector<int> correctIndex;
        bool cmdFirst = false, cmdLast = false;

        for (auto line : cmds)
        {
            if (line.find("cmdFirst:") != string::npos)
            {
                cmdFirst = true;
                commandFirst.push_back(line.substr(line.find(':') + 1));
            }

            else if (line.find("cmdLast:") != string::npos)
            {
                cmdLast = true;
                commandLast.push_back(line.substr(line.find(':') + 1));
            }
        }

        // Depending on if the command has only cmdFirst, cmdLast, or both
        // Look for the cmdFirst and cmdLast in replacements and put their indexes into correctIndex
        if (cmdFirst && cmdLast)
        {
            for (int x = 0; x < replacements.size(); x++)
            {
                for (int y = 0; y < commandFirst.size(); y++)
                {
                    if (commandFirst.at(y) == replacements.at(x).substr(0, 4))
                    {
                        for (int z = 0; z < commandLast.size(); z++)
                        {
                            if (commandLast.at(z) == replacements.at(x).substr(replacements.at(x).size() - 4))
                            {
                                correctIndex.push_back(x);
                            }
                        }
                    }
                }
            }
        }

        else if (cmdFirst && !cmdLast)
        {
            for (int x = 0; x < cmds.size(); x++)
            {
                for (int y = 0; y < replacements.size(); y++)
                {
                    if ((replacements.at(y).substr(0, 4)) == (cmds.at(x).substr(cmds.at(x).find(':') + 1)))
                    {
                        correctIndex.push_back(y);
                    }
                }
            }
        }

        else if (!cmdFirst && cmdLast)
        {
            for (int x = 0; x < cmds.size(); x++)
            {
                for (int y = 0; y < replacements.size(); y++)
                {
                    if ((replacements.at(y).substr(replacements.at(y).size() - 4)) == (cmds.at(x).substr(cmds.at(x).find(':') + 1)))
                    {
                        correctIndex.push_back(y);
                    }
                }
            }
        }

        else if (!cmdFirst && !cmdLast)
        {
            for (int x = 0; x < replacements.size(); x++)
            {
                postCmd.push_back(replacements.at(x));
            }
        }

        // Putting the indexes of correctIndex from replacements into postCmd vector
        sort(correctIndex.begin(), correctIndex.end());
        for (int x = 0; x < correctIndex.size(); x++)
        {
            postCmd.push_back(replacements.at(correctIndex.at(x)));
        }
        // Outputting to argumentmanager
        for (auto line : postCmd)
        {
            out << line << "\n";
        }
    }
}

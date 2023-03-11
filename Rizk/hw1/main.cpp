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
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ifstream command(am.get("command"));
    ofstream out(am.get("output"));

    // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
    //ifstream input("input2.txt");
    //ifstream command("command2.txt");
    //ofstream out("output2.txt");

    string in = "";
    int num = 0;
    vector<string> lines,vectorID,keyValues,replacements,cmds,postCmd;

    if (input.peek() != EOF)
    {
        while (getline(input, in)) //Start of TA-provided code
        {
            // Clean up blank spaces, \n and \r, and skip blank lines
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in.size() == 0)
                continue; //End of TA provided code

            int num = 0; //generic counter variable
            if (in.find(";id:") != string::npos) //if the id exists
            {
                if (isalpha(in[0])) //is the first digit alpha?
                {
                    for (auto entry : in) //enhanced for loop going through each line in the string
                    {
                        if (!isalpha(entry) && !isdigit(entry) && entry != ';' && entry != ':' && entry != '#') //if the next index is not a letter or number or ;/:/#
                            num++; //increase the count
                    }

                    if (num == 0) //if the counter = 0
                        lines.push_back(in); //add the text to the lines vector
                }
            }
        }
        for (auto line : lines) //enhanced for loop going through each index in vector lines
        {
            string id = line.substr(line.find(";id:") + 4, line.length() - 1); //separate id from array
            vectorID.push_back(id); //put IDs into their own vector.

            string keyValue = line.substr(0, line.find("id:")); //separate keyValue from array
            keyValues.push_back(keyValue); //put keyValues into their own array
        }
        for (int x = 0; x < vectorID.size(); x++) //replacing the letters in ID with numbers
        {
            string replacement = ""; //this will hold the edited string from vectorID
            for (int y = 0; y < vectorID.at(x).length(); y++) //going 1by1 through the loop
            {
                char currentLetter = vectorID.at(x).at(y); //the letter we are going to replace
                if (isdigit(currentLetter)) //if its a digit we don't need to change it in any way
                {
                    replacement += currentLetter; //instead of editing it, we will add to the new array
                }

                else if (isalpha(currentLetter)) //check if its a letter instead
                {
                    if (keyValues.at(x).find(currentLetter) != string::npos) //if the letter exists in both ID and keyValue
                    {
                        int startValue = keyValues.at(x).find(currentLetter) + 2; //finding the first digit associated with the letter
                        int endValue = keyValues.at(x).find(';', startValue); //finding the last digit associated with the letter
                        replacement += keyValues.at(x).substr(startValue, endValue - startValue); //add all of the values to replacement
                    }
                }
                else if (currentLetter == '#')
                    replacement += "#"; //keep hashtag as is for now, next step is to replace them
            }
            vector<int> hashtag; //replacing hashtags
            int lastIndex = 0;
            while (replacement.find('#', lastIndex) != string::npos) //finding hashtags if they exist
            {
                lastIndex = replacement.find('#', lastIndex); //find where # is
                hashtag.push_back(lastIndex++); //replace with index
            }
            while (!hashtag.empty()) //if there are no hashtags
            {
                replacement.insert(hashtag.back(), to_string(hashtag.back()));
                hashtag.pop_back();
            }
            while (replacement.find('#') != string::npos) //make sure to remove the hashtags from the replacement string
                replacement.erase(replacement.find('#'), 1);

            replacements.push_back(replacement); //add the replacement string to the replacements vector
        }
        //dealing with commands
        string cmd = "";
        num = 0;
        while (getline(command, cmd)) //Start of TA provided code
        {
            // Clean up blank spaces, \n and \r, and skip blank lines
            cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
            cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
            cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());
            if (cmd.size() == 0)
                continue;

            // continue to process the command below (End of TA provided code)
            cmds.push_back(cmd); //add cmd to the cmds vector
        }
        vector<string> cmdFirst, cmdLast; //cmdFirst holds the first4: digits, cmdLast hold the last4: digits
        vector<int> validIndex;
        bool firstSeen = false, lastSeen = false; //check to see if first4: and last4: appear
        for (auto line : cmds) //going through the cmds vector
        {
            if (line.find("first4:") != string::npos) //if first4: shows up in the code
            {
                firstSeen = true; //set firstSeen to true as first4: was found
                cmdFirst.push_back(line.substr(line.find(':') + 1)); //add the first4: digits to the cmdFirst vector
            }

            else if (line.find("last4:") != string::npos) //if last4: shows up in the code
            {
                lastSeen = true; //set lastSeen to true as last4: was found
                cmdLast.push_back(line.substr(line.find(':') + 1)); //add the last4: digits to the cmdFirst vector
            }
        }
        if (firstSeen && lastSeen) //if both firstSeen and lastSeen are true (i.e. both show up in the code)
        {
            for (int x = 0; x < replacements.size(); x++)
                for (int y = 0; y < cmdFirst.size(); y++)
                    if (cmdFirst.at(y) == replacements.at(x).substr(0, 4))
                        for (int z = 0; z < cmdLast.size(); z++)
                            if (cmdLast.at(z) == replacements.at(x).substr(replacements.at(x).size() - 4))
                                validIndex.push_back(x);
        }
        else if (firstSeen && !lastSeen) //if only firstSeen is true (i.e. first4: shows up but not last4:)
        {
            for (int x = 0; x < cmds.size(); x++)
                for (int y = 0; y < replacements.size(); y++)
                    if ((replacements.at(y).substr(0, 4)) == (cmds.at(x).substr(cmds.at(x).find(':') + 1)))
                        validIndex.push_back(y);
        }
        else if (!firstSeen && lastSeen) //if only lastSeen is true (i.e. last4: shows up but not first4:)
        {
            for (int x = 0; x < cmds.size(); x++)
                for (int y = 0; y < replacements.size(); y++)
                    if ((replacements.at(y).substr(replacements.at(y).size() - 4)) == (cmds.at(x).substr(cmds.at(x).find(':') + 1)))
                        validIndex.push_back(y);
        }
        else if (!firstSeen && !lastSeen) //if neither are true (i.e. neither first4: nor last4: show up)
        {
            for (int x = 0; x < replacements.size(); x++)
                postCmd.push_back(replacements.at(x));
        }

        sort(validIndex.begin(), validIndex.end());
        for (int x = 0; x < validIndex.size(); x++)
            postCmd.push_back(replacements.at(validIndex.at(x)));
        
        for (int x = 0; x < postCmd.size(); x++)
            (x == postCmd.size() - 1) ? (out << postCmd.at(x)) : (out << postCmd.at(x) << endl);
    }
}
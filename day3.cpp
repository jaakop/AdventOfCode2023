#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string getNumber(string line, int start = 0) {
    string number = "";
    
    for(int i = start; i < line.length(); i++) {
        if(line[i] >= '0' && line[i] <= '9') {
            number += line[i];
        }
        else {
            break;
        }
    }
    return number;
}

bool isCharSymbold(char c) {
    return c != '.' && !(c >= '0' && c <= '9');
}
 
int main()
{
    vector<string> lines;
    string line;
    ifstream myFile ("input3.txt");

    int sum = 0;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            lines.push_back(line);
        }
        myFile.close();
    }

    for(int i = 0; i < lines.size(); i++) 
    {
        string currentLine = lines[i]; 

        for(int j = 0; j < currentLine.length(); j++) {
            bool hasSymbol = false;
            string number = getNumber(currentLine, j);
        
            if(number == "") {
                continue;
            }

            if(j != 0 && isCharSymbold(currentLine[j-1])) 
                hasSymbol = true;
            if(j+number.length() != currentLine.length()-1 && isCharSymbold(currentLine[j+number.length()])) 
                hasSymbol = true;

            if(i != 0) {
                string previousLine = lines[i-1];

                for(int k = j-1; k < j+number.length()+1; k++) {
                    if(k < 0 || k > previousLine.length() - 1)
                        continue;
                    
                    if(isCharSymbold(previousLine[k]))
                        hasSymbol = true;
                }
            }
            if(i != lines.size() - 1) {
                string nextLineLine = lines[i+1];
                
                for(int k = j-1; k < j+(int)number.length()+1; k++) {
                    if(k < 0 || k > nextLineLine.length() - 1)
                        continue;
                    
                    if(isCharSymbold(nextLineLine[k]))
                        hasSymbol = true;
                }
            }


            if(hasSymbol)
                sum += stoi(number);

            j += number.length();
        }
    }

    cout << sum;
    return 0;
}
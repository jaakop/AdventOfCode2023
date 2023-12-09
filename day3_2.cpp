#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

int getNumber(string line, int index = 0) {
    string number = "";

    int i = index;

    while (i >= 0 && isNumber(line[i])) {
        number = line[i] + number;
        i--;
    }
    
    i = index + (isNumber(line[index]) ? 1 : 0);
    while (i < line.length() && isNumber(line[i])) {
        number += line[i];
        i++;
    }

    return number == "" ? 0 : stoi(number);
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
            if(currentLine[j] != '*')
                continue;

            int gearSum = 1;
            int numberOfParts = 0;


            if(j != 0) {
                int num = getNumber(currentLine, j-1);
                if(num != 0) {
                    gearSum *= num;
                    numberOfParts++;
                }
            }

            if(j != currentLine.length()-1) {
                int num = getNumber(currentLine, j+1);
                if(num != 0) {
                    gearSum *= num;
                    numberOfParts++;
                }
            } 
                

            if(i != 0) {
                string previousLine = lines[i-1];

                bool numberFound = false;

                for(int k = j-1; k <= j+1; k++) {
                    if(k < 0 || k > previousLine.length() - 1)
                        continue;

                    if(!numberFound) {
                        int num = getNumber(previousLine, k);
                        if(num != 0) {
                            gearSum *= num;
                            numberOfParts++;
                            numberFound = true;
                            continue;
                        }
                    }
                    numberFound = isNumber(previousLine[k]);
                }
            }

            if(i != lines.size() - 1) {
                string nextLineLine = lines[i+1];

                bool numberFound = false;
                
                for(int k = j-1; k <= j+1; k++) {
                    if(k < 0 || k > nextLineLine.length() - 1)
                        continue;

                    if(!numberFound) {
                        int num = getNumber(nextLineLine, k);
                        if(num != 0) {
                            gearSum *= num;
                            numberOfParts++;
                            numberFound = true;
                            continue;
                        }
                    }

                    numberFound = isNumber(nextLineLine[k]);
                }
            }
            
            if(numberOfParts == 2) {
                sum += gearSum;
            }
        }
    }

    cout << sum;
    return 0;
}
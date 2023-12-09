#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int checkForStringNumber(string line, int pos) {
    string numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    
    for(int j = 0; j < 9; j++) { 
        int numPos = 0;
        bool numberFound = false;
        
        for(int i = pos; i < line.length() && i-pos < numbers[j].length(); i++) {
            
            if(line[i] != numbers[j][numPos]) {
                numberFound = false;
                break;
            }
            numPos++;
            if(numPos == numbers[j].length()) {
                numberFound=true;
            }
        }

        if(numberFound) {
            return j + 1;
        }
    }

    return 0;
}

int main()
{
    string line;
    ifstream myFile ("input1.txt");

    int sum = 0;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            string number = "";

            for(int i = 0; i < line.length(); i++) {
                if(line[i] >= '0' && line[i] <= '9') {
                    number += line[i];
                    break;
                }
                int num = checkForStringNumber(line, i);
                
                if(num != 0) {
                    number += to_string(num);
                    break;
                }
            }

            for(int i = line.length() - 1; i >= 0; i--) {
                if(line[i] >= '0' && line[i] <= '9') {
                    number += line[i];
                    break;
                }

                int num = checkForStringNumber(line, i);
                
                if(num != 0) {
                    number += to_string(num);
                    break;
                }
            }
            if(number != "") {
                sum += stoi(number);
            }
        }
        myFile.close();
    }
    cout << sum;
    return 0;
}
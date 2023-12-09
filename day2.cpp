#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> findStringIndex(string s, string find) {
    vector<int> indexList;
    
    for(int i = 0; i < s.length(); i++) {
        bool found = false;
        for(int j = 0; j < find.length() && i+j < s.length(); j++) {
            if(s[i+j] != find[j]) {
                break;
            }
            found = true;
        }
        if(found) {
            indexList.push_back(i);
        }
    }

    return indexList;
}

int getNumberFromString(int i, string line) {
    string number = "";
    int j = i-2;
    while(line[j] != ' ' && j >= 0) {
        number = line[j] + number;
        j--;
    }

    if(number != "") {
        return stoi(number);
    }
    return 0;
}

int main()
{
    string line;
    ifstream myFile ("input2.txt");

    int sum = 0;

    string colors[] = {"red", "green", "blue"};
    int bag[] = {12, 13, 14};

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            bool validGame = true;

            vector<int> reds = findStringIndex(line, "red");
            vector<int> greens = findStringIndex(line, "green");
            vector<int> blues = findStringIndex(line, "blue");

            for(int i : reds) {
                if(getNumberFromString(i, line) > bag[0]){
                    validGame = false;
                }
            }
            for(int i : greens) {
                if(getNumberFromString(i, line) > bag[1]){
                    validGame = false;
                }
            }
            for(int i : blues) {
                if(getNumberFromString(i, line) > bag[2]){
                    validGame = false;
                }
            }

            if(validGame) {
                sum += getNumberFromString(findStringIndex(line, ":")[0]+2, line);
            }
        }
        myFile.close();
    }

    cout << sum;
    return 0;
}
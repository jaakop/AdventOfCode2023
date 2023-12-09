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

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

int pow(int base, int power) {
    if(power <= 1) {
        if(power <= 0)
            return 0;
        return base;
    }
    return base * pow(base, power - 1);
}

vector<int> getNumbers(string line, int index) {
    vector<int> numbers;

    string number = "";

    for(int i = index; i < line.length(); i++) {
        if(isNumber(line[i])) {
            number += line[i];
            continue;
        }

        if(number.length() > 0 && number != " ") {
            numbers.push_back(stoi(number));
            number = "";
        }

        if(line[i] == '|') {
            break;
        }
    }
    
    if(number != "")
        numbers.push_back(stoi(number));

    return numbers;
}

int main()
{
    string line;
    ifstream myFile ("input4.txt");

    int sum = 0;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {

            vector<int> winningNumbers = getNumbers(line, findStringIndex(line, ":")[0]+1);
            vector<int> numbers = getNumbers(line, findStringIndex(line, "|")[0]+1);

            int foundNumbers = 0;

            for(int number : numbers) {
                for(int winning : winningNumbers) {
                    if(winning == number) {
                        foundNumbers++;
                        break;
                    }
                }
            }

            if(foundNumbers == 1) {
                sum += 1;    
            } 
            else {
                sum += pow(2, foundNumbers-1);
            }
        }
        myFile.close();
    }
    cout << sum;
    return 0;
}
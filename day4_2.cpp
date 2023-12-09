#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

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
    int cardNumber = 1;

    map<int, int> cardAmounts;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {

            if(!cardAmounts.count(cardNumber)) {
                cardAmounts.insert(make_pair(cardNumber, 1));
            }
            else {
                cardAmounts[cardNumber] += 1;
            }

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

            for(int i = 1; i <= foundNumbers; i++) {
                int card = cardNumber + i;
                
                if(!cardAmounts.count(card)) {
                    cardAmounts.insert(make_pair(card, 1 * cardAmounts[cardNumber]));
                }
                else {
                    cardAmounts[card] += 1 * cardAmounts[cardNumber];
                }
            }
            cardNumber++;
        }
        myFile.close();
    }

    for(auto card : cardAmounts) {
        sum += card.second;
    }

    cout << sum;
    return 0;
}
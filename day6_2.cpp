#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

vector<double> getNunbers(string line) {
    vector<double> numbers;
    string number = "";
    for(int i = 0; i < line.length(); i++) {
        if(!isNumber(line[i])) {
            continue;
        }

        number += line[i];
    }
    
    if(number != "") {
        numbers.push_back(stod(number));
    }

    return numbers;
}

int main()
{
    string line;
    ifstream myFile ("input6.txt");

    int sum = 1;
    int lineNum = 0;

    vector<double> times;
    vector<double> distances;  

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            string number = "";

            auto numbers = getNunbers(line);
            if(lineNum == 0) {
                times = numbers;
            }
            else {
                distances = numbers;
            }
            lineNum++;
        }
        myFile.close();
    }

    for(int i = 0; i<times.size(); i++) {
        auto root = sqrt((times[i]*times[i]) + 4*(-distances[i]-1));

        auto max = floor((-times[i]-root)/(-2));
        auto min = ceil((-times[i]+root)/(-2));
        cout << max << " " << min << endl;
        sum *= max-min+1;
    }
    
    cout << sum;
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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
            }

            for(int i = line.length() - 1; i >= 0; i--) {
                if(line[i] >= '0' && line[i] <= '9') {
                    number += line[i];
                    break;
                }
            }

            sum += stoi(number);
        }
        myFile.close();
    }
    cout << sum;
    return 0;
}
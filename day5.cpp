#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

vector<unsigned long> getNunbers(string line) {
    vector<unsigned long> numbers;
    string number = "";
    for(int i = 0; i < line.length(); i++) {
        if(!isNumber(line[i])) {
            if(line[i] == ' ' && number != "") {
                numbers.push_back(stoul(number));
                number = "";
            }
            continue;
        }

        number += line[i];
    }
    
    if(number != "") {
        numbers.push_back(stoi(number));
    }

    return numbers;
}

unsigned long processMap(unsigned long value, vector<vector<unsigned long>> map)
{
    unsigned long newValue = -1;
    for (auto mapping : map)
    {
        if (mapping[1] > value
        || !(mapping[1] <= value && value <= mapping[1] + mapping[2] - 1))
        {
            continue;
        }

        newValue = mapping[0] + value - mapping[1];
    }

    if (newValue < 0)
    {
        newValue = value;
    }

    return newValue;
}

vector<unsigned long> processValues(vector<unsigned long> values, vector<vector<unsigned long>> map) {
    vector<unsigned long> newValues;
    for(unsigned long value : values) {
        newValues.push_back(processMap(value, map));
    }
    return newValues;
}

int main()
{
    string line;
    ifstream myFile ("input5.txt");

    unsigned long sum = -1;

    vector<unsigned long> seeds;
    vector<vector<unsigned long>> seedSoilMap;
    vector<vector<unsigned long>> soilFertMap;
    vector<vector<unsigned long>> fertWaterMap;
    vector<vector<unsigned long>> waterLightMap;
    vector<vector<unsigned long>> lightTempMap;
    vector<vector<unsigned long>> tempHumidMap;
    vector<vector<unsigned long>> humidLocMap;
    unsigned long map = 0;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            if(line == ""){
                map++;
                continue;
            }

            if(map == 0) {
                seeds = getNunbers(line);
                continue;
            }

            vector<unsigned long> mapNumbers = getNunbers(line);
            if(mapNumbers.size() == 0) {
                continue;
            }

            switch (map)
            {
            case 1:
                seedSoilMap.push_back(mapNumbers);
                break;
            case 2:
                soilFertMap.push_back(mapNumbers);
                break;
            case 3:
                fertWaterMap.push_back(mapNumbers);
                break;
            case 4:
                waterLightMap.push_back(mapNumbers);
                break;
            case 5:
                lightTempMap.push_back(mapNumbers);
                break;
            case 6:
                tempHumidMap.push_back(mapNumbers);
                break;
            case 7:
                humidLocMap.push_back(mapNumbers);
                break;

            default:
                break;
            }
        }
        myFile.close();
    }
    auto values = processValues(
        processValues( 
            processValues(
                processValues(
                    processValues(
                        processValues(
                            processValues(seeds, seedSoilMap)
                            ,soilFertMap)
                        ,fertWaterMap)
                    ,waterLightMap)
                ,lightTempMap)
            ,tempHumidMap)
        ,humidLocMap);

    for(unsigned long value : values) {
        if(value < sum || sum == -1) {
            sum = value;
        }
    }

    cout << sum;
    return 0;
}
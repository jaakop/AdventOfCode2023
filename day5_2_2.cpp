#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

vector<double> getNunbers(string line) {
    vector<double> numbers;
    string number = "";
    for(int i = 0; i < line.length(); i++) {
        if(!isNumber(line[i])) {
            if(line[i] == ' ' && number != "") {
                numbers.push_back(stod(number));
                number = "";
            }
            continue;
        }

        number += line[i];
    }
    
    if(number != "") {
        numbers.push_back(stod(number));
    }

    return numbers;
}

vector<double> processSeedRanges(vector<double> seeds, vector<vector<double>> map) {
    vector<double> newSeeds;

    while(seeds.size() > 0) {
        // Get seed range from the end of the array
        // See: https://www.youtube.com/watch?v=NmxHw_bHhGM
        double seedsE = seeds[seeds.size()-1];
        seeds.pop_back();
        double seedsS = seeds[seeds.size()-1];
        seeds.pop_back();

        bool found = false;
        for(auto numbers : map) {            
            // Get range partion start
            auto os = std::max(seedsS, numbers[1]);
            // Get range partion end
            auto oe = std::min(seedsE, numbers[1] + numbers[2]);

            // Make sure that the start is before end
            if(os < oe) {
                found = true;
                // Add new range start from map starting point (numbers [0]) 
                newSeeds.push_back(os - numbers[1] + numbers[0]);
                // Add new range edn from map starting point (numbers [0])
                newSeeds.push_back(oe - numbers[1] + numbers[0]);

                // Check if seeds range is only partionally overlapping, if so push new seed range to the og seeds array for processing
                //If seed range start is smaller that range start, we have to add new range from seed start to range start
                if(os > seedsS) {
                    seeds.push_back(seedsS);
                    seeds.push_back(os);
                }
                //If seed range end is smaller that range end, we have to add new range from seed end to range end
                if(oe > seedsE) {
                    seeds.push_back(seedsE);
                    seeds.push_back(oe);
                }
                break;
            }
        }
        // No map range matched this range, add the numbers back as is
        if(!found) {
            newSeeds.push_back(seedsS);
            newSeeds.push_back(seedsE);
        }
    }
    
    return newSeeds;
}

int main()
{
    string line;
    ifstream myFile ("input5.txt");

    double sum = -1;
    
    vector<double> seeds;
    vector<vector<double>> seedSoilMap;
    vector<vector<double>> soilFertMap;
    vector<vector<double>> fertWaterMap;
    vector<vector<double>> waterLightMap;
    vector<vector<double>> lightTempMap;
    vector<vector<double>> tempHumidMap;
    vector<vector<double>> humidLocMap;
    vector<vector<double>> seedLocMap;
    int map = 0;

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

            vector<double> mapNumbers = getNunbers(line);
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

    for(int i = 0; i < seeds.size(); i+=2) {
        seeds[i+1] = seeds[i]+seeds[i+1];
    } 

    seeds = processSeedRanges(seeds, seedSoilMap);
    seeds = processSeedRanges(seeds, soilFertMap);
    seeds = processSeedRanges(seeds, fertWaterMap);
    seeds = processSeedRanges(seeds, waterLightMap);
    seeds = processSeedRanges(seeds, lightTempMap);
    seeds = processSeedRanges(seeds, tempHumidMap);
    seeds = processSeedRanges(seeds, humidLocMap);
    
    for(int i = 0; i < seeds.size(); i+=2) {
        if(seeds[i] < sum || sum == -1) 
            sum = seeds[i];
    }
    
    cout << to_string(sum);
    return 0;
}
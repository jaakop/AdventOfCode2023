#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// First version derived from 1st part couldn't calculate first map with 1st pair (350 million numbers) in 20min
// This binary tree calculates the whole thing in 9 min

struct Node {
    unsigned long Key;
    vector<unsigned long> Value;
    Node* Left;
    Node* Right;

    Node(vector<unsigned long> value) {
        Key = value[1];
        Value = value;
        Left = NULL;
        Right = NULL;
    }
};

Node* Find( Node* node, unsigned long value )
{
    if( node == NULL )
        return NULL;
    if( node->Key <= value && (node->Key <= value && value <= node->Key + node->Value[2] - 1) )
        return node;
    if( node->Key > value )
        return Find( node->Left, value );
    else
        return Find( node->Right, value );
};


void Insert( Node*& node, vector<unsigned long> value )
{
    if( node == NULL ) {
        node = new Node( value );
        return;
    }
    if( node->Key > value[1] )
        Insert( node->Left, value );
    else
        Insert( node->Right, value );
};



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

unsigned long processMap(unsigned long value, Node* tree)
{
    auto branch = Find(tree, value);

    if(branch != NULL) {
        return branch->Value[0] + value - branch->Value[1];
    }

    return value;
}

vector<unsigned long> processValues(vector<unsigned long> values, Node* tree) {
    for(unsigned long i = 0; i < values.size(); i++) {
        values[i] = processMap(values[i], tree);
    }

    cout << "Map finished" << endl;
    return values;
}

int main()
{
    string line;
    ifstream myFile ("input5.txt");

    unsigned long sum = ULONG_MAX;

    vector<unsigned long> seeds;

    Node* seedSoilTree = NULL;
    Node* soilFertTree = NULL;
    Node* fertWaterTree = NULL;
    Node* waterLightTree = NULL;
    Node* lightTempTree = NULL;
    Node* tempHumidTree = NULL;;
    Node* humidLocTree = NULL;

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
                Insert(seedSoilTree, mapNumbers);
                break;
            case 2:
                Insert(soilFertTree, mapNumbers);
                break;
            case 3:
                Insert(fertWaterTree, mapNumbers);
                break;
            case 4:
                Insert(waterLightTree, mapNumbers);
                break;
            case 5:
                Insert(lightTempTree, mapNumbers);
                break;
            case 6:
                Insert(tempHumidTree, mapNumbers);
                break;
            case 7:
                Insert(humidLocTree, mapNumbers);
                break;

            default:
                break;
            }
        }
        myFile.close();
    }

    for (int i = 0; i < seeds.size(); i += 2)
    {
        vector<unsigned long> newSeeds;
        for (unsigned long j = seeds[i]; j < seeds[i] + seeds[i + 1]; j++)
        {
            newSeeds.push_back(j);
        }

        cout << "Now calculating next patch of seeds from " << newSeeds[0] << " to " << newSeeds.back() << endl;

        auto values = processValues(
            processValues(
                processValues(
                    processValues(
                        processValues(
                            processValues(
                                processValues(newSeeds, seedSoilTree), soilFertTree),
                            fertWaterTree),
                        waterLightTree),
                    lightTempTree),
                tempHumidTree),
            humidLocTree);

        for (unsigned long value : values)
        {
            if (value < sum)
            {
                sum = value;
            }
        }
        cout << "Patch of seeds calculated, new smallest sum: " + to_string(sum) << endl;
    }

    cout << sum;
    return 0;
}
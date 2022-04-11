#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> split(string text);

string stringFromFile(string filePath);

string removePunctuation(string text);

unordered_map<string, double> sumMaps(vector<unordered_map<string, double>> maps);
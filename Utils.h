#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> split(string text);

string readFile(string filePath);

string getCleanedWord(string text);
void cleanWord(string& text);

unordered_map<string, double> sumMaps(vector<unordered_map<string, double>> maps);

unordered_map<string, double> tokenize(string content, int& numWords);

void relativize(unordered_map<string, double>& map, double dividend);

void insertFeature(vector<pair<string, double>>& features, pair<string, double> targetFeature, int targetIndex);

void autoInsertFeature(vector<pair<string, double>>& features, pair<string, double> targetFeature);

vector<pair<string, double>> getEmptyFeatureVector(int length);

double cosine_distance(vector<double> vector_a, vector<double> vector_b);
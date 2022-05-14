#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace FastDelta{
    typedef unordered_map<string, double> feature_map;
    typedef pair<string, double> feature;
    typedef vector<feature> feature_vec;

    vector<string> split(string text);

    string readFile(string filePath);

    string getCleanedWord(string text);
    void cleanWord(string& text);

    feature_map sumMaps(vector<feature_map> maps);

    feature_map tokenize(string content, int& numWords);

    void relativize(feature_map& map, double dividend);

    void insertFeature(feature_vec& features, feature targetFeature, int targetIndex);

    void autoInsertFeature(feature_vec& features, feature targetFeature);

    vector<feature> getEmptyFeatureVector(int length);

    double findCosDist(vector<double> vector_a, vector<double> vector_b);
}
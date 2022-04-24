#pragma once

#include <filesystem>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <math.h>

#include "Utils.h"
#include "Text.h"

using namespace std;

class Corpus{
    public:
        unordered_map <string, Text> writings;
        unordered_map <string, double> overallFrequencies; /*This should
        represent the sum of all frequences for every text in writing*/

        Corpus(string folderPath, int numFeatures);
        Corpus(vector<Text> texts, int numFeatures);

        vector<unordered_map<string, double>> getFrequenciesVec();
        void appendTexts(vector<Text>);
        vector<pair<string, double>> getMostFrequentFeatures(int numFeatures);
        vector<string> trimFeatures(int numFeatures);

        double getFeatureMean(string feature);
        double getFeatureStdev(string feature);
        double getFeatureStdev(string feature, string authorName);
        vector<double> getZScores(string authorName);

        void printOverallFeatures();
    
    private:
        vector<string> features;
};
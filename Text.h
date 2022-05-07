#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "Utils.h"

using namespace std;

class Text{
    public:
        string authorName;
        unordered_map <string, double> wordFrequencies;
        Text(string name, string text);
        Text();
        void trimFeatures(unordered_set<string> topFeatures);
        void printFrequencies();
        double getFrequency(string token);
    private:
        int wordsWritten;
};
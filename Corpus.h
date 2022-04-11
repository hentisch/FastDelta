#pragma once

#include <vector>
#include <unordered_map>
#include "Utils.h"

#include "Text.h"


using namespace std;

class Corpus{
    public:
        unordered_map <string, Text> writings;
        unordered_map <string, double> overall_frequencies; /*This should
        represent the sum of all frequences for every text in writing*/
        Corpus(vector<Text> texts);
        vector<unordered_map<string, double>> getFrequenciesVec();
};
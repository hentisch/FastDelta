#include "Text.h"

Text::Text(){}

Text::Text(string name, string text){
    /*Constructs a text object, immediately
    tokenizing the text string and storing
    the result in the wordFrequenceis map.*/
    this->authorName = name;

    int totalWords;
    unordered_map<string, double> features = tokenize(text, totalWords);

    this->wordsWritten = totalWords;
    relativize(features, totalWords);
    this->wordFrequencies = features;
}

void Text::trimFeatures(unordered_set<string> topFeatures){
    /* This function will remove every feature from the text object's wordFrequencies
    map unless it is part of the passed topFeatures vector*/

    auto isInfrequentFeature = [&](pair<string, double> feature){
        return topFeatures.find(feature.first) == topFeatures.end(); 
        //return true;
    };

    erase_if(this->wordFrequencies, isInfrequentFeature);
}

void Text::printFrequencies(){
    /*Prints the tokenized word 
    frequencies of a text*/
    for(auto i: wordFrequencies)
    {
        cout << i.first << "    " << i.second << endl;
    }
}
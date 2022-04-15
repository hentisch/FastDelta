#include "Text.h"

Text::Text(){}

Text::Text(string name, string text){
    /*Constructs a text object, with the 
    word frequencies attribute storing the 
    relitive word frequiences for the text 
    given as a paramater*/
    this->authorName = name;

    int totalWords;
    unordered_map<string, double> features = tokenize(text, totalWords);

    this->wordsWritten = totalWords;
    relativize(features, totalWords);
    this->wordFrequencies = features;
}

void Text::printFrequencies(){
    /*Prints the tokenized word 
    frequencies of a text*/
    for(auto i: wordFrequencies)
    {
        cout << i.first << "    " << i.second << endl;
    }
}
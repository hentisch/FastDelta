#include "Text.h"

Text::Text(string name, string text){
    /*Constructs a text object, with the 
    word frequencies attribute storing the 
    relitive word frequiences for the text 
    given as a paramater*/
    vector<string> words = split(text);
    for(int i = 0; i < words.size(); i++){
        if(wordFrequencies.find(words[i]) == wordFrequencies.end()){
            wordFrequencies[words[i]] = 1.0 / words.size();
        }
        else{
            wordFrequencies[words[i]] += 1.0 / words.size();
        }
    }
}

void Text::printFrequencies(){
    /*Prints the tokenized word 
    frequencies of a text*/
    for(auto i: wordFrequencies)
    {
        cout << i.first << "    " << i.second << endl;
    }
}
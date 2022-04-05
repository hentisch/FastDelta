#include "Text.h"

Text::Text(string name, string text){
    text = removePunctuation(text);
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
    for(auto i: wordFrequencies)
    {
        cout << i.first << "    " << i.second << endl;
    }
}
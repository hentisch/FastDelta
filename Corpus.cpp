#include "Corpus.h"

Corpus::Corpus(vector<Text> texts){
    /*Constructs Corpus object. 
    "Writings" represents a hashmap of writings,
    based on the array of texts passed. Overall frequencies 
    represents the word frequencies for the entire corpus*/
    for(Text t: texts){
        writings[t.authorName] = t;
    } 
    overall_frequencies = sumMaps(this->getFrequenciesVec());
}

vector<unordered_map<string, double>> Corpus::getFrequenciesVec(){
    /*This method returns a vector of dictionaries, with each 
    dictonary representing the word frequencies for a text in the corpus */
    vector<unordered_map<string, double>> frequencies;
    for(auto text: this->writings){
        frequencies.push_back(text.second.wordFrequencies);
    }
    return frequencies;
}


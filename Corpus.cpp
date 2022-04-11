#include "Corpus.h"

Corpus::Corpus(string folderPath){
    /*This function will construct a corpus from a set of text files in a certain folder. These should be in the format
    TextName_AuthorName.txt with both names in camel case. Note that if there are two texts with the same author, 
    they will be combined into one "text" */
    unordered_map<string, string> authorContent;

    for(auto &file: filesystem::directory_iterator(folderPath)) //Lists all files 
    {
        string path = file.path();
        
        string splitName = path.substr(path.find_last_of("/")+1, (path.find(".") - path.find_last_of("/")) - 1);
        string authorName = splitName.substr(splitName.find("_")+1);
        string content = stringFromFile(file.path());

        if(authorContent.find(authorName) == authorContent.end())
            authorContent[authorName] = content;
        else
            authorContent[authorName] += " " + content; 
    }

    vector<Text> texts;

    for(pair writing: authorContent){
        texts.push_back(Text(writing.first, writing.second));
    }

    this->appendTexts(texts);
}

Corpus::Corpus(vector<Text> texts){
    /*Constructs Corpus object*/
    this->appendTexts(texts);
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

void Corpus::appendTexts(vector<Text> texts){
    /*This should append each text object
    to the corpus object. Additionally, the 
    overall frequencies map should be updated.*/
    for(Text t: texts){
        writings[t.authorName] = t;
    } 
    overall_frequencies = sumMaps(this->getFrequenciesVec());
}

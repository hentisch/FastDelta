#include "Corpus.h"

Corpus::Corpus(string folderPath, int numFeatures){
    /*This function will construct a corpus from a set of text files in a certain folder. These should be in the format
    TextName_AuthorName.txt with both names in camel case. Note that if there are two texts with the same author, 
    they will be combined into one "text". The total number of features represented in the corpus will be restricted
    based on the numFeatures paramater.*/
    unordered_map<string, string> authorContent;

    for(auto &file: filesystem::directory_iterator(folderPath)) //Lists all files 
    {
        string path = file.path();
        
        string splitName = path.substr(path.find_last_of("/")+1, (path.find(".") - path.find_last_of("/")) - 1);
        string authorName = splitName.substr(splitName.find("_")+1);
        string content = readFile(file.path());

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

    this -> features = this->trimFeatures(numFeatures);
}

Corpus::Corpus(vector<Text> texts, int numFeatures){
    /*Constructs Corpus object from an array of Text objects. 
    The total number of features reprsented in the corpus
    will be restricted by the numFeatures paramater.*/
    this->appendTexts(texts);

    this -> features = this->trimFeatures(numFeatures);
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
    overallFrequencies = sumMaps(this->getFrequenciesVec());
}

vector<pair<string, double>> Corpus::getMostFrequentFeatures(int numFeatures){
    /* This method will return the numFeatures most frequent features amongst the 
    entire corpus */
    vector<pair<string, double>> features = getEmptyFeatureVector(numFeatures);
    for(pair feature: this->overallFrequencies){
        autoInsertFeature(features, feature);
    }
    return features;
}

vector<string> Corpus::trimFeatures(int numFeatures){
    /*this method should remove all features in the corpus, except for the
    numFeatures most frequent features. A string vector will be returned,
    reperesenting the strings still present in the Corpus maps. Note that
    this feature trimming also applies to the Corpus objects consituent
    text objects*/

    vector<pair<string, double>> topFeaturesVec = this->getMostFrequentFeatures(numFeatures);

    unordered_set<string> topFeaturesSet; /*As we are going to go through every feature in each of our
    frequency maps, it is usefull to be able to check if a word is in this list in o(1) time*/

    for(pair feature: topFeaturesVec){
        topFeaturesSet.insert(feature.first);
    }

    auto isInfrequentFeature = [&](pair<string, double> feature){
        return topFeaturesSet.find(feature.first) == topFeaturesSet.end(); 
    };
    
    erase_if(this->overallFrequencies, isInfrequentFeature);

    for(auto& text: this->writings){
        text.second.trimFeatures(topFeaturesSet);
    }

    vector<string> topFeatures;
    for(string feature: topFeaturesSet){
        topFeatures.push_back(feature);
    }

    return topFeatures;
}

double Corpus::getFeatureMean(string feature){
    /*This method should return the mean frequency for a given feature across all texts in your corpus */
    if(overallFrequencies.find(feature) == overallFrequencies.end())
       throw std::invalid_argument("\"" +  feature + "\"" + " could not be found in the overall set of frequencies");
    return this->overallFrequencies[feature] / this->writings.size();
}

void Corpus::printOverallFeatures(){
    /* This method will print out the overallFrequencies 
    map, for the purpose of debugging*/
    for(pair i: overallFrequencies){
        cout << i.first << " " << i.second << "\n";
    }
}


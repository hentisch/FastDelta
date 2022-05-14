#include "Corpus.h"

using namespace FastDelta;

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

vector<feature_map> Corpus::getFrequenciesVec(){
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

feature_vec Corpus::getMostFrequentFeatures(int numFeatures){
    /* This method will return the numFeatures most frequent features amongst the 
    entire corpus */
    feature_vec features = getEmptyFeatureVector(numFeatures);
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

    feature_vec topFeaturesVec = this->getMostFrequentFeatures(numFeatures);

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
    /*This returns the mean frequency for a given feature across all texts in your corpus */
    if(overallFrequencies.find(feature) == overallFrequencies.end())
       throw std::invalid_argument("\"" +  feature + "\"" + " could not be found in the overall set of frequencies");
    return this->overallFrequencies[feature] / this->writings.size();
}

double Corpus::getFeatureStdev(string feature){
    /* This method returns the standard deviation of a feature amongst the corpus*/
    if(overallFrequencies.find(feature) == overallFrequencies.end())
        throw std::invalid_argument("\"" + feature + "\"" + " could not be found in the overall set of frequencies");
    
    double mean = this->getFeatureMean(feature);

    double sum = 0;

    for(pair text: writings){
        sum += pow(text.second.wordFrequencies[feature] - mean, 2);
    }

    return sqrt(sum/writings.size());
}

vector<double> Corpus::getZScores(string authorName){
    /* This method returns a vector of z-scores for the given text, with each score
    in the z-score vector representeing the word represented at the same index in the
    passed features array. */
    vector<double> zScores;

    for(string feature: this->features){

        double textFrequency = this->writings[authorName].getFrequency(feature);

        zScores.push_back((textFrequency - this->getFeatureMean(feature)) / this->getFeatureStdev(feature));
    }
    
    return zScores;
}

vector<pair<string, double>> Corpus::rankBySimilarity(string authorName){ 
    /*This function should rate all texts in the Corpus, except one, by their similarity to the text
    refrenced by the name passed to the method */
    vector<double> unknownZScores = this->getZScores(authorName);
    vector<pair<string, double>> rankings;

    for(pair text: writings){
        if(text.first != authorName){
            vector<double> zScores = this->getZScores(text.first);
            double distance = findCosDist(unknownZScores, zScores);
            if(rankings.size() <= 0)
                rankings.push_back(pair<string, double>(text.first, distance));
            else{
                bool atEnd = true;
                for(int i = 0; i < rankings.size(); i++){
                    if(distance < rankings[i].second){
                        rankings.insert(rankings.begin() + i, pair<string, double>(text.first, distance));
                        atEnd = false;
                        break;
                    }
                }
                if(atEnd)
                    rankings.push_back(pair<string, double>(text.first, distance));
            }
        }
    }

    return rankings;
}

void Corpus::printOverallFeatures(){
    /* This method will print out the overallFrequencies 
    map, for the purpose of debugging*/
    for(pair i: overallFrequencies){
        cout << i.first << " " << i.second << "\n";
    }
}
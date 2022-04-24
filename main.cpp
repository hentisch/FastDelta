#include <iostream>
#include <vector>
#include <string>
#include "Utils.h"
#include "Text.h"
#include "Corpus.h"

using namespace std;

int main(){
    Corpus dataset("/home/henry/Desktop/GitRepos/CStylo/Dataset", 50);

    vector<double> scores = dataset.getZScores("Unknown");

    for(double feature: scores){
        cout << feature << " ";
    }
    cout << "\n";

    cout << scores.size() << "\n";

    return 0;
}
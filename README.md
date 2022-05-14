# FastDelta
The 'FastDelta' C++ library is, as the name may apply, built to allow for the quick use of Delta methods of authorship attributation, specifically the cosine delta measure. Certain well established libraries, such as [Stylo](https://github.com/computationalstylistics/stylo), are likely to be more accurate for research and smaller tasks of identification. However, this library is much, much faster than Stylo on account of being written in C++. As such, this library allows for the use of these methods on a larger scale than was feasable before.

## Installation
To install 'FastDelta':
  1. Clone this git repository
  2. In the cloned git reposity, move all of the files in the `lib` directory into your main project directory
  3. When compiling your project using this library, make sure to also compile the 'Corpus.cpp', 'Text.cpp', and 'Utils.cpp'. Note that this project uses C++20 features. With g++, you can enable these by using the -std=c++2a flag

## Usage
This library is primarily intended to be used for it's 'Corpus' class. To use the class, simply '#include <"Corpus.h">' at the top of your file. Keep in mind that the 'Corpus' Class belongs to the 'FastDelta' namespace. You can use the Corpus constructor to create a Corpus from a folder of text files. These text files should be organized in the format 'BookName_Author.txt'. In the corpus, different texts with the same author will be merged into one frequency vector. In addition to the folder path, the second paramater of this constructor will dictate how many of the top features should be considered for comparison. Generally, 50 is a good value to use. 

Once you have constructed your 'corpus', you can do your stylometric analysis through the rankBySimilarity method. Pass it the name of an author in your corpus, and it will return a vector of string double paris. In each pair, the string represents the name of an author, and the double represents the distance between the passed author, and the pairs author. The vector is sorted by stylometric similarity, meaning that the first pair in the vector will represent the author who's writing style is closest to the author considered.

## Contributing
If you would like to contribute to this library, feel free to leave a pull request.

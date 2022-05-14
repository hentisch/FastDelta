# FastDelta
The 'FastDelta' C++ library is, as the name may apply, built to allow for the quick use of Delta methods of authorship attributation. Certain well established libraries, such as [Stylo](https://github.com/computationalstylistics/stylo), are likely to be more accurate for research and smaller tasks of identification. However, this library is much, much faster than Stylo on account of being written in C++. As such, this library allows for the use of these methods on a larger scale than was feasable before.

## Installation
To install 'FastDelta':
  1. Clone this git repository
  2. In the cloned git reposity, move all of the files in the `lib` directory into your main project directory
  3. When compiling your project using this library, make sure to also compile the 'Corpus.cpp', 'Text.cpp', and 'Utils.cpp'. Note that this project uses C++20 features. With g++, you can enable these by using the -std=c++2a flag

## Usage
Full documentation for this library is avalible [here](www.google.com).

## Contributing
If you would like to contribute to this library, feel free to leave a pull request.

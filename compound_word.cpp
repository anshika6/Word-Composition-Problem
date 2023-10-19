#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool isCompoundWord(const string& word, const unordered_set<string>& wordSet) {
    if (word.empty()) { //not a compound word
        return false;
    }

    int len = word.length();

    for (int i = 1; i < len; ++i) {
        string prefix = word.substr(0, i);
        string suffix = word.substr(i);

        if (wordSet.count(prefix) && wordSet.count(suffix)) {
            return true;
        }
    }

    return false;
}

int main() {
    ifstream inputFile1("Input_01.txt");
    ifstream inputFile2("Input_02.txt");

    if (!inputFile1.is_open() || !inputFile2.is_open()) {
        cerr << "Error opening input files.\n";
        return 1;
    }

    vector<string> wordList;
    string word;
    unordered_set<string> wordSet;

    // Read words from Input_01.txt and Input_02.txt and insert them into the set
    while (inputFile1 >> word) {
        wordList.push_back(word);
        wordSet.insert(word);
    }

    while (inputFile2 >> word) {
        wordList.push_back(word);
        wordSet.insert(word);
    }

    inputFile1.close();
    inputFile2.close();

    // Measure time taken to process input files
    auto start = high_resolution_clock::now();

    string longestCompoundWord;
    string secondLongestCompoundWord;

    // Iterate through the words to find longest and second longest compound words
    for (const string& word : wordList) {
        if (isCompoundWord(word, wordSet)) {
            if (word.length() > longestCompoundWord.length())
                longestCompoundWord = word;
            else if (word.length() > secondLongestCompoundWord.length())
                secondLongestCompoundWord = word;
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Longest Compounded Word : " << longestCompoundWord << endl;
    cout << "Second Longest Compounded Word : " << secondLongestCompoundWord << endl;
    cout << "Time taken to process input files : " << duration.count() << " milliseconds\n";

    return 0;
}

// output
/*Longest Compounded Word  :  electroencephalographically     
Second Longest Compounded Word  :  immunoelectrophoretically
Time taken to process input files: 233 milliseconds  */


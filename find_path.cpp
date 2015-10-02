#include <iostream>
#include "AnagramSet.hpp"
#include "Dictionary.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
const int maxWords = 300000;
const int TABLE_SIZE = 9298187;

string words[maxWords], reversedWords[maxWords];

// read file into wordList. Return number of words read in
int readInWords(string wordList[],  int maxSize, string fileName) ;

// count the number of words in wordList that are in d
void countHits (string wordList[], int length,  Dictionary & d);

// write the dictionary to a file
void toFile(const Dictionary & d, const string & fileName) ;

// find palindromic words (bob) and palindrom pairs (live evil)
void findPalindromes(Dictionary & d, int numWords);

// count anagrams
void countAnagrams( Dictionary & d, int minimum, string wordList[], int length);

// remove words from dictionary
void removalTest( Dictionary & d, int numWords, int howMany) ;

// insert words to dictionary
void insertionTest( Dictionary & d, int numWords);

// find words whose letters match a given string
void unScramble(Dictionary & d);

bool in_dictionary(const string &s, Dictionary& dict)
{
    if (dict.contains(s))
        return true;
    return false;
}

void print_list(const vector<string> word)
{
    int size = word.size();
    for (int i = 0; i < size; i++) {
         if (i)
            cout << "\n |\n";
        cout << word[i];
    }
    cout << endl;
}


int main()
{
    string file_name = "words.txt", user_in;
    ofstream fout("hashed-sorted_words.txt");
    ifstream fin(file_name.c_str());
    if (fin.fail()) {
        cout << file_name << " doesn't exist.\n" << flush;
        return -1;
    }
    int numWords = readInWords(words, maxWords,"words.txt");
    cout << "Read in " << numWords << " words " << endl;
    Dictionary dict(words, numWords, TABLE_SIZE);
	toFile(dict, "full.txt");
    
    vector<string> word_1;
    string word_2, tmp;
    do {
        word_1.erase(word_1.begin(), word_1.end());
        cout << "Enter two word seperate by space or q to quit: " << flush;
        getline (cin, user_in);
        if (user_in == "q")
            break;
        stringstream sstrm(user_in);
        sstrm >> tmp >> word_2;
        word_1.push_back(tmp);
        bool in_dict = false, found_path = false;
        
        for (unsigned int i = 0; !found_path && i < word_1.size(); i++) {
            if (word_1[i] == word_2)
                found_path = true;
            in_dict = false;
            for (int j = 0; !in_dict && tmp[j]; j++) {
                tmp = word_1[i];
                if (tmp[j] != word_2[j])
                    tmp[j] = word_2[j];
                else
                    continue;
                if (in_dictionary(tmp, dict)) {
                    word_1.push_back(tmp);
                    in_dict = true;
                }
            }
        }
        print_list(word_1);
    } while (user_in != "q");
    return 0;
}

int readInWords(string wordList[],  int maxSize, string fileName) {
    int i = 0;
	ifstream infile;
	infile.open(fileName.c_str());
	if (!infile) cout <<"Failed to open file" << endl;
    while (infile && i < maxSize) {
        string s;
        infile >> s;
        if (infile) {
            wordList[i] = s;
            i++;
        }
    }
    return i; 
}

string reverse(const string & s) {
	string t;
	for (int i = s.length()-1; i >= 0; i--)
		t.push_back(s[i]);
	return t;
}

void toFile(const Dictionary & d, const string & fileName) {
	ofstream out;
	out.open(fileName.c_str());
	out << d << endl;
	out.close();
}

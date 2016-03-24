/*
 * Your Dictionary stores a map of key-value pairs where the
 * key is a suitably stored bag of letters (e.g. a LetterBag object 
 * or a sorted string) and the value a set of words containing exactly 
 * those letters. The key--value pairs are represented by the AnagramSet
 * class, which you also need to implement.
 * You must use a hash table with chaining as the underlying data 
 * structure.  Write everything from scratch.
 * 
 * Your run times should meet or beat the times shown. For example, 
 * on a typical laptop, a size 100000 hash table should give elapsed 
 * time under 0.25 seconds for each countAnagrams() call.  Your times 
 * will increase with smaller hash table sizes as illustrated by the 
 * sample runs. I'm looking primarily at efficiency for grading this 
 * assignment. That means the fastest time for the least amount of 
 * memory.  To achieve that you need a good hash function. The hash 
 * function takes a key and returns a number in the range [0, size-1]. 
 * The Dictionary constructor takes size as a parameter so you can 
 * create Dictionaries with different underlying hash table sizes.
 * Notice that we overload the stream insertion operator for both 
 * AnagramSet and Dictionary.  
 * 
 * For AnagramSet, you should output both the key and the set of 
 * associated words ( e.g. aet: { eat,  tea } ) . 
 * I output the Dictionary in a slightly odd format to manifest its 
 * underlying structure in the hash table. That means you will see 
 * more than one AnagramSet per line (exclosed in braces) whenever a 
 * collision occurred (i.e. both AnagramSets mapped to the same hash 
 * index).  You don't need to duplicate this output format.
 * 
 * I'm not providing header files for Dictionary or Anagram. You should 
 * be able to deduce constructor and function prototypes from the calls 
 * in tester.cpp. Also, you will want to have more functions in 
 * AnagramSet and Dictionary than are used in the tester, depending on 
 * how you implement the hash table. You may want to make a separate 
 * class to store the hash table itself, rather than put it in 
 * Dictionary; that's up to you.
 */
 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

#include "AnagramSet.hpp"
#include "Dictionary.hpp"

using namespace std;
const int maxWords = 200000;
string words[maxWords], reversedWords[maxWords];

int tfine; // used for timer

void resetTimer() ;  // reset the timer
int getTime();  // get elapsed time

// read file into wordList. Return number of words read in
int readInWords(string wordList[],  int maxSize, string fileName) ;

// return the reverse of s
string reverse(const string & s);

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

int main() {

	int  tableSize;
	cout << "What is the hash table size? ";
	cin >> tableSize;
	resetTimer();
	
	cout << "Starting" << endl;
	int numWords = readInWords(words, maxWords,"words.txt");
	
	cout << "Read in " << numWords << " words " << endl;
	cout << "Done reading words, elapsed time = " << getTime() << endl << endl;
	
	resetTimer();
	Dictionary d(words, numWords, tableSize );
	cout << "Done creating dictionary, elapsed time = " << getTime() << endl;
	countHits(words,numWords,d);

	resetTimer();
	toFile(d, "full.txt");
	cout << "Done writing to file, elapsed time = " << getTime() << endl;
	
	findPalindromes(d,numWords);

	for (int i = 2; i <= 13; i++)
		countAnagrams(d,i,words,numWords);
	
	removalTest(d, numWords, numWords-30);
	removalTest(d, numWords, numWords);

	insertionTest(d, numWords);
	insertionTest(d, numWords);

	unScramble(d);
	cout << "Bye!" << endl;
	return 0;
}


void resetTimer() {
	tfine = clock();
}

int getTime() {
	return clock() - tfine;
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
    return i;  // the number of words read in
}

void countHits (string wordList[], int length,  Dictionary & d) {
	resetTimer();	 
	int count = 0;
	for (int i = 0; i < length; i++) 
		if (d.contains(wordList[i]) )
			count++;
	cout << "Hit count = " << count
		 << ",  elapsed time = " << getTime() << endl << endl;
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

void countAnagrams( Dictionary & d, int howMany, string wordList[], int length) {
	// There's a faster way of counting if we know d contains the same words
	// as wordList, but for the sake of testing we'll ignore that fact.
	resetTimer();
	int sum = 0;
	for (int i = 0; i < length; i++)  {
		AnagramSet * a = d.getSet(wordList[i]);
		if (a != NULL && a->getSize() == howMany)   
			sum++;
	}
	cout	<< "Found " << setw(5) << sum 
			<< " words with  " << setw(3) << howMany << " anagramatic forms. Elapsed time = " 
			<< getTime() << endl;
}

void findPalindromes(Dictionary & d, int numWords) {
	Dictionary pal(2000);
	cout << "Creating reversed word list...";
	for (int i = 0; i < numWords; i++) 
		reversedWords[i] = reverse(words[i]);
	cout << endl << "Counting palindromes.";
	countHits(reversedWords, numWords, d);
	cout <<  "Creating palindrome dictionary...";
	for (int i = 0; i < numWords; i++)  {
		if (d.contains(reversedWords[i])) {
			pal.insert(words[i]);
			pal.insert(reversedWords[i]);
		}
	}
	cout << "done.  " << endl;
	toFile(pal, "palindromes.txt");

	cout << endl << endl;
}

void removalTest( Dictionary & d, int numWords, int howMany) {
	resetTimer();
	for (int i = 0, j = 0; j < howMany; i  = ( i + 22079) % numWords, j++) 
		d.remove(words[i]);
	cout << endl << "Done removing " << howMany << ", elapsed time = " << getTime() << endl << endl;
	cout <<"Current dictionary = " << endl <<  d;
	countHits(words,numWords,d);


}


void insertionTest( Dictionary & d, int numWords) {
	resetTimer();
	for (int i = numWords-1; i >= 0; i--)
		d.insert(words[i]);
	cout << "Done inserting, elapsed time = " << getTime() << endl;
	countHits(words,numWords,d);

}


void unScramble(Dictionary & d) {
	string s;
	do {
		cout << "Enter an anagram or q to quit: ";
		cin >> s;
		if (s != "q") {
			AnagramSet * a = d.getSet(s);
			if (a == NULL)
				cout << "Not found " << endl;
			else
				cout << "Found it: " << *a << endl;
		}
	} while (s != "q");
}

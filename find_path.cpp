#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct Word_Bag {
    string word;
    long long 
bool in_dictionary(const string &s)
{
    return -1;
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
    
    string file_name = "words.txt";
    ifstream fin.open(file_name.str());
    
    if (fin.fail()) {
        cout << file_name << " doesn't exist.\n";
        return -1;
    }
    vector<string> word_1;
    string word_2, tmp, user_in;
    cout << "Enter two word seperate by space: " << flush;
    getline (cin, user_in);
    stringstream sstrm(user_in);
    sstrm >> tmp >> word_2;
    word_1.push_back(tmp);
    //cout << "You entered " << word_1[0] << ' ' << word_2 << endl;
    bool in_dict = false, found_path = false;
    for (int i = 0; !found_path && i < word_1.size(); i++) {
        if (word_1[i] == word_2)
            found_path = true;
        in_dict = false;
        for (int j = 0; !in_dict && tmp[j]; j++) {
            tmp = word_1[i];
            if (tmp[j] != word_2[j])
                tmp[j] = word_2[j];
            else
                continue;
            if (in_dictionary(tmp)) {
                word_1.push_back(tmp);
                in_dict = true;
            }
        }
    }
    print_list(word_1);
    return 0;
}
    
        

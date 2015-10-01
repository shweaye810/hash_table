#include <iostream>
#include <fstream>
#include <string>

#include "../Shwe_Lib/shwe_lib.cpp"
using namespace std;

const int WORD_SIZE = 298187;
const long long P = 953148474371;

long long Universal_hash(string& s);

struct Hash_Table {
    string str = "";
    Hash_Table *next = nullptr;
};

void read_words(ifstream& fin, Hash_Table *dict)
{
    string tmp;
    long long h;
    int i = 0;
    while (getline(fin, tmp))
    {
        set_lower(tmp);
        h = Universal_hash(tmp);
        if (dict[h].str != "") {
            Hash_Table *tmp_table = new Hash_Table(tmp);
            dict->next = tmp_table;
        }
        dict[h] = tmp;
    }    
}

long long Universal_hash(string& s)
{
    unsigned long long h = 0;
    int size = s.size();
    for (int i = 0; i < size; i++)
    {
        h = ((h * 3810463) + s[i]*4789) % WORD_SIZE;
    }
    return h;
}

void print_words(ofstream& fout, string *dict)
{
    for (int i = 0; i < WORD_SIZE; i++) {
        fout << i << ' ' << dict[i] << endl;
    }
}

int main()
{
    string file_name = "words.txt";
    ofstream fout("hashed-sorted_words.txt");
    ifstream fin(file_name.c_str());
    if (fin.fail()) {
        cout << file_name << " doesn't exist.\n" << flush;
        return -1;
    }
    Hash_Table *dict = new Hash_Table[WORD_SIZE];
    read_words(fin, dict);
    print_words(fout, dict);

    fin.close();
    fout.close();
    return 0;
}

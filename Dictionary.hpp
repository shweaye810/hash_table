#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <fstream>
#include <iostream>
#include <istream>
#include <string>

using namespace std;

class Dictionary : public AnagramSet
{
private:
    AnagramSet **h_table;
    int tbl_size;
public:
    int numWords;
    friend ofstream & operator<<(ofstream &out, const Dictionary &d);
    friend ostream & operator<<(ostream &out, Dictionary &d);
    Dictionary(int size);
    Dictionary(const string words[], int n_words, int tbl_size);
    void fil_tbl(string & key, const string &word);
    bool contains(const string & word);
    void traverse();
    void insert(const string & word);
    void remove(const string & word);
    AnagramSet *getSet(const string & word);
};
/*
ostream &operator<<(ostream &out, Dictionary &d)
{
    int cnt,k_cnt;
    for (int i = 0; i < d.tbl_size; i++) {
        AnagramSet *tmp = d.h_table[i];
        if (tmp != nullptr) {
            Node *ptr;
            out << "{ ";
            k_cnt = 0;
            while (tmp != nullptr && tmp->getSize()) {
                k_cnt++;
                if (k_cnt > 1)
                    out << ", ";
                ptr = tmp->get_ptr();
                out << tmp->get_key() << ": { ";
                cnt = 0;
                while (ptr != nullptr) {
                    cnt++;
                    if (cnt > 1)
                        out << ", ";
                    out << ptr->get_string();
                    ptr = ptr->get_next_node();
                }
                out << " }";
                tmp = tmp->get_next_key();
            }
            out << " }\n";
        }
    }
    out << endl;
    return out;
}
*/
ofstream &operator<<(ofstream &out, const Dictionary &d)
{
    int cnt,k_cnt;
    for (int i = 0; i < d.tbl_size; i++) {
        AnagramSet *tmp = d.h_table[i];
        if (tmp != nullptr) {
            Node *ptr;
            out << "{ ";
            k_cnt = 0;
            while (tmp != nullptr && tmp->getSize()) {
                k_cnt++;
                if (k_cnt > 1)
                    out << ", ";
                ptr = tmp->get_ptr();
                out << tmp->get_key() << ": { ";
                cnt = 0;
                while (ptr != nullptr) {
                    cnt++;
                    if (cnt > 1)
                        out << ", ";
                    out << ptr->get_string();
                    ptr = ptr->get_next_node();
                }
                out << " }";
                tmp = tmp->get_next_key();
            }
            out << " }\n";
        }
    }
    out << endl;
    return out;
}

Dictionary::Dictionary(int size)
{
    tbl_size = size;
    h_table = new AnagramSet*[tbl_size];
    for (int i = 0; i < tbl_size; i++)
    {
        h_table[i] = nullptr;
    }

}

int partition(string &a, int first, int last)
{
    int x = a[first]; int low = first, high = last;
    bool highTurn = true;

    while (low < high)
    {
        if (highTurn) {
            if (a[high] < x) {
                a[low++] = a[high];
                highTurn = !highTurn;
            }
            else    high--;
        }
        else {
            if (a[low] > x) {
                a[high--] = a[low];
                highTurn = !highTurn;
            }
            else    low++;
        }
    }
    a[low] = x;
    return low;
}

void quick_sort(string &ary, int start, int end) {
    if (start >= end) return;

    int mid = partition(ary, start, end);

    quick_sort(ary, start, mid - 1);
    quick_sort(ary, mid + 1, end);
}


void sort(string &ary, int len)
{
    quick_sort(ary, 0, len - 1);
}
long long hash_value(const string &str, int tbl_size)
{
    int length = str.length();
    unsigned long long h = 0;
    for (int i = 0; i < length; i++)
    {
        h = ((h * 3810463) + str[i]*4789) % tbl_size;
    }
    return h;
}

void Dictionary::fil_tbl(string &key, const string &word)
{
    unsigned h = hash_value(key, tbl_size);
    if (h_table[h] == nullptr) {
        h_table[h] = new AnagramSet(key, word);
    } else {
        AnagramSet *tmp = h_table[h];
        while (tmp->get_next_key() != nullptr) {
            if (tmp->get_key() == key) {
                break;
            }
            tmp = tmp->get_next_key();
        }
        if (tmp->get_key() == key)
            tmp->add_word(word);
        else
            tmp->set_next_key(new AnagramSet(key, word));
    }
}

Dictionary::Dictionary(const string words[], int n_words, int table_size)
{
    tbl_size = table_size;
    numWords = n_words;
    h_table = new AnagramSet*[tbl_size];
    for (int i = 0; i < tbl_size; i++) {
        h_table[i] = nullptr;
    }
    for (int i = 0; i < numWords; i++) {
        insert(words[i]);
    }
}

bool Dictionary::contains(const string & word)
{
    bool chk = false;
    string tmp_ky = word;
    sort(tmp_ky, int(word.length()));
    unsigned int h = hash_value(tmp_ky, tbl_size);
    if (h_table[h] == nullptr)
        return false;
    AnagramSet *tmp = h_table[h];
    while (tmp != nullptr && tmp->get_key() != tmp_ky)
        tmp = tmp->get_next_key();
    if (tmp == nullptr)
        return false;
    string key_data = tmp->get_key();
    if (key_data == tmp_ky) {
        chk = tmp->check_node(word);
    }
    return chk;
}
/*
AnagramSet *Dictionary::getSet(const string & word)
{
    bool chk = false;
    string tmp_ky = word;
    for (unsigned int i = 0; i < tmp_ky.length(); i++)
        tmp_ky[i] = tolower(tmp_ky[i]);
    sort(tmp_ky, int(word.length()));
    unsigned int h = hash_value(tmp_ky, tbl_size);
    if (h_table[h] == nullptr)
        return false;
    AnagramSet *tmp = h_table[h];
    while (tmp != nullptr && tmp->get_key() != tmp_ky)
        tmp = tmp->get_next_key();
    if (tmp == nullptr)
        return false;
    else if (tmp->get_key() == tmp_ky)
        return tmp;
}
*/
void Dictionary::traverse()
{
    ofstream fout;
    fout.open("traverse.txt");
    int cnt,k_cnt;
    for (int i = 0; i < tbl_size; i++) {
        AnagramSet *tmp = h_table[i];
        Node *ptr = nullptr;
        fout << "{ ";
        k_cnt = 0;
        while (tmp != nullptr) {
            k_cnt++;
            if (k_cnt > 1)
                fout << ", ";
            ptr = tmp->get_ptr();
            fout << tmp->get_key() << ": { ";
            cnt = 0;
            while (ptr != nullptr) {
                cnt++;
                if (cnt > 1)
                    fout << ", ";
                fout << ptr->get_string();
                ptr = ptr->get_next_node();
            }
            fout << " }";
            tmp = tmp->get_next_key();
        }
        fout << " }\n";
    }
}
void Dictionary::insert(const string & word)
{
    string key = word;
    sort(key, int(key.length()));
    fil_tbl(key, word);
}

void Dictionary::remove(const string & word)
{
    string key = word;
    sort(key, int(key.length()));
    unsigned h = hash_value(key, tbl_size);
    AnagramSet *tmp = h_table[h];
    if (tmp == nullptr)
        return;
    while (tmp->get_next_key() != nullptr) {
        if (tmp->get_key() == key) {
            break;
        }
        tmp = tmp->get_next_key();
    }
    if (tmp->get_key() == key)
        tmp->rm_word(word);
    if (tmp->get_ptr() == nullptr) {
        if (tmp->get_next_key()) {
            AnagramSet * key_to_del = tmp->get_next_key();
            tmp->set_key(key_to_del->get_key());
            tmp->set_ptr(key_to_del->get_ptr());
            tmp->set_size(key_to_del->getSize());
            tmp->set_next_key(key_to_del->get_next_key());
            key_to_del->set_next_key(nullptr);
            key_to_del->set_size(0);
            delete key_to_del;
            key_to_del = nullptr;
        } else {
            tmp = nullptr;
            delete tmp;
            tmp = nullptr;
        }
    }
    /*
    if (tmp->get_ptr() == nullptr && h_table[h]->get_next_key() != nullptr) {
        AnagramSet *key_to_del = h_table[h]->get_next_key();
        if (tmp != key_to_del) {
            tmp->set_key(key_to_del->get_key());
            tmp->set_ptr(key_to_del->get_ptr());
            tmp->set_size(key_to_del->getSize());
            h_table[h]->set_next_key(key_to_del->get_next_key());
            key_to_del->set_next_key(nullptr);
            key_to_del->set_size(0);
            delete key_to_del;
            key_to_del = nullptr;
        } else if (key_to_del != nullptr && key_to_del->get_next_key() == nullptr &&
            key_to_del->get_ptr() == nullptr){
            key_to_del->set_size(0);
            delete key_to_del;
            key_to_del = nullptr;
        }
        */
        if (h_table[h]->get_next_key() == nullptr)
            h_table[h] = nullptr;
}

#endif // DICTIONARY_H

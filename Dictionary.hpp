#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <fstream>
#include <iostream>
#include <istream>

using namespace std;

class Dictionary : public AnagramSet
{
private:
	AnagramSet **h_table;
	int tbl_size;
	void quickSort(string & s, int len);
	void quickSort1(string & s, int start, int end);
	int partition(string & s, int first, int last);
public:
	friend ofstream & operator<<(ofstream &out, const Dictionary &d);
	friend ostream & operator<<(ostream &out, Dictionary &d);
	Dictionary(int size);
	Dictionary(string words[], int n_words, int tbl_size);
	void fil_tbl(string &key, const string &word);
	bool contains(const string & word);
	void traverse();
	void insert(const string & word);
	void remove(const string & word);
	int numWords;
	AnagramSet *getSet(string word);
};

ostream &operator<<(ostream &out, Dictionary &d)
{
	int cnt, k_cnt;

	for (int i = 0; i < d.tbl_size; i++)
	{
		AnagramSet *tmp = d.h_table[i];

		if (tmp != nullptr) {
			Node *ptr;
			out << "{ ";
			k_cnt = 0;

			while (tmp != nullptr && tmp->getSize())
			{
				k_cnt++;
				if (k_cnt > 1)
					out << ", ";
				ptr = tmp->get_ptr();
				out << tmp->get_key() << ": { ";
				cnt = 0;

				while (ptr != nullptr)
				{
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

	return out;
}

ofstream &operator<<(ofstream &out, const Dictionary &d)
{
	int cnt, k_cnt;

	for (int i = 0; i < d.tbl_size; i++)
	{
		AnagramSet *tmp = d.h_table[i];
		if (tmp != nullptr)
		{
			Node *ptr;
			out << "{ ";
			k_cnt = 0;

			while (tmp != nullptr && tmp->getSize())
			{
				k_cnt++;
				if (k_cnt > 1)
					out << ", ";
				ptr = tmp->get_ptr();
				out << tmp->get_key() << ": { ";
				cnt = 0;

				while (ptr != nullptr)
				{
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

int Dictionary::partition(string & s, int first, int last)
{
	char x = s[first]; int low = first, high = last;
	bool highTurn = true;

	while (low < high)
	{
		if (highTurn) {
			if (s[high] < x)
			{
				s[low++] = s[high];
				highTurn = !highTurn;
			}
			else
				high--;
		}
		else
		{
			if (s[low] > x)
			{
				s[high--] = s[low];
				highTurn = !highTurn;
			}
			else	low++;
		}
	}

	s[low] = x;

	return low;
}

// helper function for quicksort
void Dictionary::quickSort1(string & s, int start, int end)
{
	if (start >= end) return;

	int mid = partition(s, start, end);

	quickSort1(s, start, mid - 1);
	quickSort1(s, mid + 1, end);

}

// quicksort
void Dictionary::quickSort(string & s, int len)
{
	quickSort1(s, 0, len - 1);
}

unsigned int hash_value(string &str, int tbl_size)
{
	int length = str.length();
	unsigned int v = 0;
	int a = 29;

	for (int i = 0; i < length; i++)
	{
		v *= a;
		v += str[i];
		v %= tbl_size;
	}

	return v;
}

void Dictionary::fil_tbl(string &key, const string &word)
{
	unsigned h = hash_value(key, tbl_size);
	if (h_table[h] == nullptr)
	{
		h_table[h] = new AnagramSet(key, word);
	}
	else
	{
		AnagramSet *tmp = h_table[h];

		while (tmp->get_next_key() != nullptr)
		{
			if (tmp->get_key() == key)
			{
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

Dictionary::Dictionary(string words[], int n_words, int table_size)
{
	tbl_size = table_size;

	h_table = new AnagramSet*[tbl_size];
	for (int i = 0; i < tbl_size; i++)
	{
		h_table[i] = nullptr;
	}

	for (int i = 0; i < n_words; i++)
	{
		insert(words[i]);
	}

	numWords = n_words;
}

bool Dictionary::contains(const string & word)
{
	bool chk = false;
	string tmp_ky = word;
	quickSort(tmp_ky, tmp_ky.length());
	unsigned int h = hash_value(tmp_ky, tbl_size);

	if (h_table[h] == nullptr)
		return false;

	AnagramSet *tmp = h_table[h];

	while (tmp != nullptr && tmp->get_key() != tmp_ky)
		tmp = tmp->get_next_key();

	if (tmp == nullptr)
		return false;

	string key_data = tmp->get_key();

	if (key_data == tmp_ky)
	{
		chk = tmp->check_node(word);
	}
	return chk;
}

AnagramSet *Dictionary::getSet(string word)
{
	bool chk = false;
	string tmp_ky = word;

	for (int i = 0; i < word.length(); i++)
	{
		tmp_ky[i] = tolower(tmp_ky[i]);
	}

	quickSort(tmp_ky, tmp_ky.length());
	unsigned int h = hash_value(tmp_ky, tbl_size);
	if (h_table[h] == nullptr)
		return nullptr;
	AnagramSet *tmp = h_table[h];
	while (tmp != nullptr && tmp->get_key() != tmp_ky)
		tmp = tmp->get_next_key();
	if (tmp == nullptr)
		return nullptr;
	else if (tmp->get_key() == tmp_ky)
		return tmp;
}

void Dictionary::traverse()
{
	ofstream fout;
	fout.open("traverse.txt");
	int cnt, k_cnt;
	for (int i = 0; i < tbl_size; i++)
	{
		AnagramSet *tmp = h_table[i];
		Node *ptr = nullptr;
		fout << "{ ";
		k_cnt = 0;
		while (tmp != nullptr)
		{
			k_cnt++;
			if (k_cnt > 1)
				fout << ", ";
			ptr = tmp->get_ptr();
			fout << tmp->get_key() << ": { ";
			cnt = 0;
			while (ptr != nullptr)
			{
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
	quickSort(key, key.length());
	fil_tbl(key, word);
}

void Dictionary::remove(const string & word)
{
	string key = word;
	quickSort(key, key.length());
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
		}
		else {
			tmp = nullptr;
			delete tmp;
			tmp = nullptr;
		}
	}
	if (h_table[h]->get_next_key() == nullptr)
		h_table[h] = nullptr;
}

#endif // DICTIONARY_H

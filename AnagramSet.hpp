#ifndef AnagramSet_H
#define AnagramSet_H

#include "Node.hpp"
#include <string>
using namespace std;

class AnagramSet
{
private:
	string key;
protected:
	AnagramSet *nxt_ky;
	Node *ptr;
	int size;
public:
	friend ostream &operator<<(ostream &out, const AnagramSet &a);
    AnagramSet();
    AnagramSet(string &key, const string &word);
    string &get_key();
    void add_word(const string &word);
    void set_next_key(AnagramSet *nxt);

	void rm_word(const string &word);

    void set_key(string &key);
	void set_ptr(Node *ptr);
	void set_size(int size);
    AnagramSet *get_next_key();
    Node *get_ptr();
    bool check_node(const string &word);
	int getSize();
};

ostream & operator<<(ostream &out, const AnagramSet &a)
{
	int cnt;
	Node *ptr;
	AnagramSet tmp = a;
	ptr = tmp.get_ptr();
	out << tmp.get_key() << ": { ";
	cnt = 0;
	while (ptr != nullptr) {
		cnt++;
		if (cnt > 1)
			out << ", ";
		out << ptr->get_string();
		ptr = ptr->get_next_node();
	}
	out << " }";

	return out;
}

AnagramSet::AnagramSet()
{
    ptr = nullptr;
    nxt_ky = nullptr;
	size = 0;
}

AnagramSet::AnagramSet(string &key, const string &word)
{
    this->key = key;
    this->nxt_ky = nullptr;
    this->ptr = new Node(word);
	size = 1;
}

string &AnagramSet::get_key()
{
    return key;
}

void AnagramSet::add_word(const string &word)
{
	Node *tmp = ptr;
	while (tmp != nullptr && tmp->get_next_node() != nullptr) {
		if (tmp->get_string() == word)
			return;
		tmp = tmp->get_next_node();
	}
	if (tmp->get_string() != word)
		tmp->set_node(new Node(word));
	/*
	Node *nde = new Node(word);
	ptr->set_node(nde);
	nde->set_node(tmp);
	*/
	size++;
}
void AnagramSet::rm_word(const string &word)
{
	Node *entry_ptr = ptr;
	Node *node_to_del = ptr;
	while (entry_ptr != nullptr) {
		if (word == entry_ptr->get_string())
			break;
		entry_ptr = entry_ptr->get_next_node();
	}
	if (entry_ptr != nullptr) {
		entry_ptr->set_string(ptr->get_string());
		ptr = ptr->get_next_node();

		node_to_del->set_node(nullptr);
		delete node_to_del;
		node_to_del = nullptr;
	}
	size--;
}


void AnagramSet::set_next_key(AnagramSet *nxt)
{
    this->nxt_ky = nxt;
}
void AnagramSet::set_key(string &key)
{
    this->key = key;
}
void AnagramSet::set_ptr(Node *ptr)
{
	this->ptr = ptr;
}
void AnagramSet::set_size(int size)
{
	this->size = size;
}
AnagramSet * AnagramSet::get_next_key()
{
    return this->nxt_ky;
}
Node * AnagramSet::get_ptr()
{
    return this->ptr;
}
bool AnagramSet::check_node(const string &word)
{
    Node *tmp = this->ptr;
    while (tmp != nullptr && tmp->get_string() != word)
        tmp = tmp->get_next_node();
    if (tmp == nullptr)
        return false;
    return true;
}

int AnagramSet::getSize()
{
	return size;
}

#endif // AnagramSet_H

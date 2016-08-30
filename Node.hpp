#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;
class Node
{
private:
protected:
        string str;
        Node *next;
public:
        Node(const string &word);
        void set_node(Node *ptr);
        void set_string(const string &s);
        void del_node();
        Node *get_next_node();
        string &get_string();
};

Node::Node(const string &word)
{
        str = word;
        next = nullptr;
}

void Node::set_node(Node *ptr)
{
        this->next = ptr;
}
void Node::set_string(const string &s)
{
        str = s;
}
string & Node::get_string()
{
        return str;
}
Node * Node::get_next_node()
{
        return this->next;
}


#endif // NODE_H

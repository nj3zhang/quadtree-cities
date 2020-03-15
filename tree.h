/*
 * Nicole Zhang
 * nj3zhang
 */
#ifndef tree_h
#define tree_h
#include "data.h"
#include <iostream>
#include <string.h>
using namespace std;

class Node {
public:
    Node * NE;
    Node * NW;
    Node * SE;
    Node * SW;
    Node * parent;
    XY key;
    city_info data;
    Node () {
        NE = nullptr;
        NW = nullptr;
        SE = nullptr;
        SW = nullptr;
        parent = nullptr;
    };
};

class QuadTree {
public:
    Node * t_head{nullptr};
    int tsize{0};
    ~QuadTree();
    string insert (city_info data);
    Node * searchKey (Node *subTree, XY key);
    string search (XY key);
    void qmax (string attr, Node *current, int &max);
    void qmin (string attr, Node *current, int &min);
    void qtotal(string attr, Node *current, long int &total);
    void print (Node* current, string &message);
    void clear (Node* current);
    string size ();
};
#endif


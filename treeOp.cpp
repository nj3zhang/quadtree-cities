/*
 * Nicole Zhang
 * nj3zhang
 */

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "tree.h"
#include "data.h"

using namespace std;
double getAttribute (Node *current, string attr);

/*
 Destructor
 Calls clear to remove all nodes in the tree
 */
QuadTree::~QuadTree(){
    if (t_head != nullptr) {
        clear(t_head);
        t_head = nullptr;
        tsize = 0;
    }
}

/*
 Insert to the tree at a leaf node
 Calls searchKey to find the node to insert to
 Depending on the value of the key, insert to the node in specific direction
 return failure if there is a duplicate key
 */
string QuadTree :: insert(city_info data) {
    Node * newNode = new Node;
    Node * current = nullptr;
    newNode->key.x = data.x;
    newNode->key.y = data.y;
    newNode->data = data;
    // empty tree
    if (t_head == nullptr){
        t_head = newNode;
    } else {
        current = searchKey(t_head, newNode->key);
        if (newNode -> key.x >= current->key.x && newNode ->key.y > current->key.y){
            //NE
            current -> NE = newNode;
        } else if (newNode -> key.x < current->key.x && newNode ->key.y >= current->key.y){
            //NW
            current -> NW = newNode;
        } else if (newNode -> key.x <= current->key.x && newNode ->key.y < current->key.y) {
            //SW
            current -> SW = newNode;
        } else if (newNode -> key.x > current->key.x && newNode ->key.y <= current->key.y) {
            //SE
            current -> SE = newNode;
        } else {
            //Duplicate
            delete newNode;
            newNode = nullptr;
            return "failure";
        }
        newNode->parent = current;
    }
    tsize += 1;
    return "success";
}
/*
 Recursively search the tree for node to insert key to
 Returns a pointer to the node we want to insert to
 */
Node* QuadTree::searchKey(Node* subTree, XY key) {
    if (subTree == nullptr) {
        return nullptr;
    }
    Node *prev = nullptr;
    Node *temp = subTree;
    prev = temp;
        if (key.x >= temp->key.x && key.y > temp->key.y){
            //NE
            temp = temp->NE;
        } else if (key.x < temp->key.x && key.y >= temp->key.y){
            //NW
            temp = temp->NW;
        } else if (key.x <= temp->key.x && key.y < temp->key.y) {
            //SW
            temp = temp->SW;
        } else if (key.x > temp->key.x && key.y <= temp->key.y) {
            //SE
            temp = temp->SE;
        } else {
            return temp;
        }
    if(temp != nullptr){
        prev = searchKey(temp, key);
    }
    return prev;
}

/*
 Calls searchKey with the root node as a parameter
 If it returns nullptr, then the node is not found
 else return a message with the found city name
 */
string QuadTree::search(XY key) {
    Node *current = searchKey(t_head, key);
    if (current == nullptr){
        return "not found";
    }
    if (current -> key.x == key.x && current -> key.y == key.y){
        return "found " + current->data.name;
    }
    return "not found";
}

/*
 Traverse recurisvely through subtree starting at a specified node (current)
 Compare the values of the specified attribute
 Updates the min variable accordingly
 */
void QuadTree::qmin(string attr, Node *current, int &min){
    if (current != nullptr){
        qmin(attr, current->NE, min);
        double value = getAttribute(current, attr);
        if(value < min) {
            min = value;
        }
        qmin(attr, current->NW, min);
        qmin(attr, current->SW, min);
        qmin(attr, current->SE, min);
    }

}

/*
Traverse recurisvely through subtree starting at a specified node (current)
Compare the values of the specified attribute
Updates the max variable accordingly
*/
void QuadTree::qmax(string attr, Node *current, int &max){
    if (current != nullptr){
        qmax(attr, current->NE, max);
        int value = getAttribute(current, attr);
        if(value > max) {
            max = value;
        }
        qmax(attr, current->NW, max);
        qmax(attr, current->SW, max);
        qmax(attr, current->SE, max);
    }
}

/*
Traverse recurisvely through subtree starting at a specified node (current)
Adds all the values of the specified attribute
Updates the total variable accordingly
*/
void QuadTree::qtotal(string attr, Node *current, long int &total){
    if (current != nullptr){
        qtotal(attr, current->NE, total);
        int value = getAttribute(current, attr);
        total += value;
        qtotal(attr, current->NW, total);
        qtotal(attr, current->SW, total);
        qtotal(attr, current->SE, total);
    }
}

/*
 Returns the size of the tree (number of nodes)
 */
string QuadTree::size () {
    return "tree size " + to_string(tsize);
}

/*
 In order traversal of the subtree starting at a specified node (recursive)
 Concatenate city name to the message that is passed in by reference
 */
void QuadTree::print(Node* current, string &message) {
    if (current != nullptr){
        print(current->NE, message);

        print(current->NW, message);
        message += current->data.name;
        message += " ";
        print(current->SW, message);
        print(current->SE, message);
    }
     
}

/*
 Post order traversal of the entire tree and removes each node
 Results in an empty tree
 */
void QuadTree::clear (Node *current){
    if (current != nullptr){
        clear(current->NE);
        clear(current->NW);
        clear(current->SW);
        clear(current->SE);
        
        current -> NE = nullptr;
        current -> NW = nullptr;
        current -> SE = nullptr;
        current -> SW = nullptr;
        current -> parent = nullptr;
        delete current;
        current = nullptr;
    }
}

/*
 Helper function to retrieve the value of an attribute specified by a string
 */
double getAttribute (Node *current, string attr){
    double attrValue {0};
    if (attr == "p"){
        attrValue = current->data.population;
    } else if (attr == "r"){
        attrValue = current->data.costLL;
    } else if (attr == "s"){
        attrValue = current->data.salary;
    }
    return attrValue;
}


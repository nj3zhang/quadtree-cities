/*
 * Nicole Zhang
 * nj3zhang
 */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include "tree.h"
#include "data.h"
#include "treeOp.cpp"
using namespace std;
void parseCityInfo (XY &key, city_info &info, string values);
void parseXY (XY &key, string values, int &index);
void parseAttr (string &direction, string &attribute, string values, int index);
// double getAttribute (Node *current, string attr);
bool isNodeValid (Node* current, string d);
string setOutputPrecision (double output);
Node *getDirectionSubtree (Node* searchNode, string direction);

int main() {
    string line {};
    QuadTree Tree;

    while (getline(cin, line) && !cin.eof()){
    string command {""};
    string values {};
    string message {""};
    string direction {""};
    string attribute {""};
    int index;
    XY key;
    city_info info;
    int lineLength = line.length();

    int i = 0;
        while (i < lineLength && line[i] != ' ' ){
            command += line[i];
            i++;
        }
        i += 1;
        // ignore whitespace after command
        while (line[i] == ' '){
            i += 1;
        }
        while (i < lineLength) {
            values += line[i];
            i++;
        }
        if (command == "i") {
            parseCityInfo(key, info, values);
            message = Tree.insert(info);
        } else if (command == "s"){
            parseXY(key, values, index);
            message = Tree.search(key);
        } else if (command[0] == 'q') {
            parseXY(key, values, index);
            parseAttr(direction, attribute, values, index);
            if (command == "q_min"){
                //Searches for the node specified by the given key
                //returns a pointer to the node
                Node *searchNode = Tree.searchKey(Tree.t_head, key);
                bool validNode = isNodeValid(searchNode, direction);
                message = validNode? "min " : "failure";
                if (searchNode != nullptr && validNode) {
                    searchNode = getDirectionSubtree(searchNode, direction);
                    int min = getAttribute(searchNode, attribute);
                    Tree.qmin(attribute, searchNode, min);
                    message += setOutputPrecision(min);
                }
            }
            if (command == "q_max"){
                           //Searches for the node specified by the given key
                           //returns a pointer to the node
                           Node *searchNode = Tree.searchKey(Tree.t_head, key);
                           bool validNode = isNodeValid(searchNode, direction);
                           message = validNode? "max " : "failure";
                           if (searchNode != nullptr && validNode) {
                               searchNode = getDirectionSubtree(searchNode, direction);
                               int max = getAttribute(searchNode, attribute);
                               Tree.qmax(attribute, searchNode, max);
                               message += setOutputPrecision(max);
                           }
                       }
            if (command == "q_total") {
                Node *searchNode = Tree.searchKey(Tree.t_head, key);
                bool validNode = isNodeValid(searchNode, direction);
                message = validNode? "total " : "failure";
                if (searchNode != nullptr && validNode) {
                    searchNode = getDirectionSubtree(searchNode, direction);
                    long int total {0};
                    Tree.qtotal(attribute, searchNode, total);
                    message += setOutputPrecision(total);
                }
            }
        } else if (command == "print") {
            Tree.print(Tree.t_head, message);
        } else if (command == "size"){
            message = Tree.size();
        } else if (command == "clear") {
            Tree.clear(Tree.t_head);
            Tree.t_head = nullptr;
            Tree.tsize = 0;

            message = "success";
        }

        if (message != ""){
            cout << message << endl;
        }
    }
    return 0;
}
/*
 Returns a pointer to a node in the direction specified
 */
Node *getDirectionSubtree (Node* searchNode, string direction) {
        if (direction == "NW") {
            searchNode = searchNode->NW;
        } else if (direction == "NE") {
            searchNode = searchNode->NE;
        } else if (direction == "SW") {
            searchNode = searchNode->SW;
        } else if (direction == "SE") {
            searchNode = searchNode->SE;
        }
    return searchNode;
}

// Sets the output precision to have no decimal points
string setOutputPrecision (double output){
    std::ostringstream outputString;
    outputString << fixed;
    outputString << setprecision(0);
    outputString << output;
    return outputString.str();
}
/*
Verify the node is non-empty and is not a leaf node in the specified direction
returns false if the node is empty or the direction is empty
*/
bool isNodeValid (Node* current, string d){
    if (current == nullptr){
        return false;
    }
    if (d == "NE"){
        return current->NE != nullptr;
    } else if (d == "NW") {
        return current->NW != nullptr;
    } else if (d == "SE") {
        return current->SE != nullptr;
    } else if (d == "SW"){
        return current->SW != nullptr;
    }
    return true;
}

/*
 Parse out the attribute and direction specified in the input string
 */
void parseAttr (string &direction, string &attribute, string values, int index){
    int j = index + 1;
    int stringLength = values.length();
    while(values[j] != ';'){
        direction += values[j];
        j++;
    }
    j += 1;
    while (j < stringLength && values[j] != ';'){
        attribute += values[j];
        j++;
    }
}

/*
 From the input string, parse out the x and y coordinates
 store it as the XY struct
 */
void parseXY (XY &key, string values, int &index) {
    int j = 0;
        int stringLength = values.length();
        string x {""};
        string y {""};
        while(values[j] != ';'){
            x += values[j];
            j++;
        }
        j += 1;
        while (j < stringLength && values[j] != ';'){
            y += values[j];
            j++;
        }
        key.x = stod(x);
        key.y = stod(y);
    index = j;
}

/*
 Given a string of values containing the city info
 parse it into inividual parameters that is stored in the city_info class
 */
void parseCityInfo (XY &key, city_info &info, string values){
    int valuesLength = values.length();
    string value {""};
    int i = 0;
    // Name
    while(i < valuesLength && values[i]!=';' && values[i] != ' ') {
        value += values[i];
        i++;
    }
    info.name = value;
    i += 1;
    value = "";
    // X coordinate
    while(i < valuesLength && values[i]!=';' && values[i] != ' ') {
        value += values[i];
        i++;
    }
    info.x = stod(value);
    key.x = stod(value);
    i+=1;
    value = "";
    // Y coordinate
    while(i < valuesLength && values[i]!=';' && values[i] != ' ') {
        value += values[i];
        i++;
    }
    info.y = stod(value);
    key.y = stod(value);
    i+=1;
    value = "";
    // Population
    while(i < valuesLength && values[i]!=';' && values[i] != ' ') {
        value += values[i];
        i++;
    }
    info.population = stod(value);
    i+=1;
    value = "";
    // Cost of living
    while(i < valuesLength && values[i]!=';' && values[i] != ' ') {
         value += values[i];
         i++;
     }
    info.costLL = stod(value);
    i+=1;
    value = "";
    // Average salary
    while(i < valuesLength && values[i]!=';' && values[i] != ' ') {
        value += values[i];
        i++;
    }
    info.salary = stod(value);
}


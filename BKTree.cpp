/*******************************************************************************
 Spell Checker using BK-Tree
 
 This program is an implementation of a spell checker for English text. The
 spell checker incorporates a database of known words, which is built from a
 simple word list. The Burkhard-Keller Tree (BK-Tree for short) organizes the
 word list for efficient searching.
 
 BK-Tree implementation is based of the description in this article:
 http://blog.notdot.net/2007/4/Damn-Cool-Algorithms-Part-1-BK-Trees
 
 OTHER RESOURCES:
 https://en.wikipedia.org/wiki/Levenshtein_distance
 http://people.cs.vt.edu/shaffer/Book/C++3elatest.pdf (pg. 215 Sec. 6.3.2)
 https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s13
*******************************************************************************/

#include "BKTree.h"

using std::cout;
using std::endl;
using std::string;
using std::basic_string;
using std::vector;

BKTree::BKTree() { root = NULL; }
BKTree::~BKTree() { delete root; }

Node* BKTree::createNode(string w, size_t d){
    Node* node = new Node();

    node->word = w;
    node->distance = d;
    node->leftChild = NULL;
    node-rightSibling = NULL;

    return node;
}

void BKTree::add(string w){
    if ( root == NULL ){
        root = createNode(w, -1);
        return;
    }

    Node* curNode = root;
    Node* child;
    Node* newChild;
    size_t dist;

    while(1){
        dist = levenshteinDistance(curNode->word, w);
        if(!dist)
            return;
        child = curNode->leftChild;
        while(child){
            if(child->distance == dist){
                curNode = child;
                break;
            }
            child = child->rightChild;
        }

        if(!child){
            newChild = createNode(w, dist);
            newChild->leftChild = newChild;
            newChild->rightSibling = curNode->leftChild;
            break;
        }
    }
}

void BKTree::search(string w, int t){
    vector<string> suggestions;
    bool wordFound = false;

    recursiveSearch(root, suggestions, w, t, wordFound);
    printSuggestions(suggestions, wordFound);
}

void BKTree::recursiveSearch(Node* curNode, vector<string>& suggestions, string w, size_t t, bool& wordFound){
    size_t curDist = levenshteinDistance(curNode->word, w);
    size_t minDist = curDist - t;
    size_t maxDist = curDist + t;

    if(!curDist){
        wordFound = true;
        return;
    }

    if(curDist <= t){
        suggestions.push_back(curNode->word);
    }

    Node* child = curNode->leftChild;
    if(!child){
        return;
    }

    while(child){
        if(inRange(child->distance, minDist, maxDist))
            recursiveSearch(child, suggestions, w, t, wordFound);
        child = child->rightSibling;
    }
}
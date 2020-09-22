#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

using namespace std;

#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TRIENode{
    struct TRIENode *children[ALPHABET_SIZE];
    bool isWordEnd;
};

struct TRIENode *getNode(void){
    struct TRIENode *pNode = new TRIENode;
    pNode->isWordEnd = false;

    for(int i = 0; i < ALPHABET_SIZE; i++){
        pNode->children[i] = NULL;
    }
    return pNode;
}

void insert(struct TRIENode *root, const string key){
    struct TRIENode *cur = root;
    for(int level = 0; level < key.length(); level++){
        int index = CHAR_TO_INDEX(key[level]);

        if(!cur->children[index]){
            cur->children[index] = getNode();
        }
    }
    cur->isWordEnd = true;
}

bool search(struct TRIENode *root, const string key){
    int length = key.length();
    struct TRIENode *cur = root;

    for(int level = 0; level <length; level++){
        int index = CHAR_TO_INDEX(key[level]);
        if(!cur->children[index]){
            return false;
        }
        cur = cur->children[index];
    }

    return (cur!=NULL && cur->isWordEnd);
}

bool isLastNode(struct TRIENode* root){
    for(int i=0; i<ALPHABET_SIZE; i++){
        if(root->children[i]){
            return 0;
        }
        return 1;
    }
    return 0;
}

void suggestionsRec(struct TRIENode* root, string curPrefix){
    if(root->isWordEnd){
        cout<<curPrefix<<endl;
    }
    if(isLastNode(root)){
        return;
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(root->children[i]){
            curPrefix.push_back(97 + i);
            suggestionsRec(root->children[i], curPrefix);
        }
    }
}

int printAutoSuggestions(TRIENode* root, const string query){
    struct TRIENode* cur = root;

    int level;
    int n = query.length();

    for(level = 0; level < n; level++){
        int index = CHAR_TO_INDEX(query[level]);
        if(!cur->children[index]){
            return 0;
        }

        cur = cur->children[index];
    }

    bool isWord = (cur->isWordEnd == true);
    bool isLast = isLastNode(cur);

    cout<<"The suggested words are:\n"<<endl;

    if(isWord && isLast){
        cout<<query<<endl;
        return -1;
    }

    if(!isLast){
        string prefix = query;
        suggestionsRec(cur, prefix);
        return 1;
    }
    return 0;
}

int main(){
    string x;
    struct TRIENode* root = getNode();
    fstream file;
    string word, t, q, filename;

    filename = "ttt.txt";

    file.open(filename.c_str());
    while(file >> word){
        insert(root, word);
    }
    cout<<"Enter the word:\n"<<endl;

    cin>>x;

    int comp = printAutoSuggestions(root, x);

    if(comp == -1){
        cout<<"No similar words found.\n"<<endl;
    }
}
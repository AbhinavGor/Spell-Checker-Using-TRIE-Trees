#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

using namespace std;

struct trieNode{
	bool isEnd;
	trieNode* children[26];
};

static struct trieNode* node(){
	struct trieNode* temp = new trieNode();
	temp->isEnd = false;

	for(int i=0; i<26; i++){
		temp -> children[i] = NULL;
	}
	return temp;
}

class Trie{
private:
	struct trieNode* root;
public:
	Trie(){
		root = node();
	}

	void insertWord(string word){
		trieNode* temp = root;
		for(char c: word){
			if(temp->children[CHAR_TO_INDEX(c)] == NULL){
				temp->children[CHAR_TO_INDEX(c)] = node();
			}
			temp = temp->children[CHAR_TO_INDEX(c)];
		}
		temp->isEnd = true;
	}

	bool searchWord(string word){
		trieNode* temp = root;
		for(char c: word){
			if(temp->children[CHAR_TO_INDEX(c)] == NULL){
				return 0;
			}
			temp = temp->children[CHAR_TO_INDEX(c)];
		}
		if(temp->isEnd){return 1;}
		else{return 0;}
	}

	bool isLast(string word){
		if(!searchWord(word)){return false;}
		trieNode* temp = root;
		for(char c: word){ temp = temp->children[CHAR_TO_INDEX(c)]; }
		for(int i=0; i<26; i++){
			if(temp->children[i]){ return false; }
		}
		return true;
	}

	void all(trieNode* temp, string word, int flag){
		if(temp->isEnd == true && flag){
			cout<<word<<endl;
		}
		if(temp->isEnd == false || isLast(word) == false){
			for(int i = 0; i<26 ; i++){
				if(temp->children[i] != NULL){
					if(flag == 0)
						word = "";
					all(temp->children[i],word + (char)(i+96+1),flag+1);
				}
			}
		}
	}

	trieNode* root_getter(){
		return root;
	}
};

int findDistance(string word1,string word2){
	int distance = 0, i = 0;
	for(; i<word1.length() && i<word2.length(); i++){
		if(word1[i]!=word2[i]){
			distance++;
		}
	}
	return word1.length()+ word2.length() - 2*i +distance; 
}



int main(){

	Trie obj1;

	string line;
	ifstream words ("words.txt");
	if(words){
		while(getline(words,line)){
			obj1.insertWord(line);
		}
		words.close();
	}

	while(1){
		cout<<"Enter word: ";
		cin>>line;
		if((int)obj1.searchWord(line)){
			cout<<"The spelling of this word is correct."<<endl;
		}else{
			cout<<"The word is spelled wrong."<<endl;
		}
	}

	// trieNode* temp = obj1.root_getter();
	// obj1.all(temp, "",0);

	cout<<findDistance("stack","stck");
}


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

using namespace std;
vector< pair<int, string> > ln;

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

int findDistance(string word1,string word2){
	int distance = 0, i = 0;
	for(;i<word1.length() && i<word2.length();i++){
		if(word1[i]!=word2[i]){
			distance++;
		}
	}
	return word1.length()+ word2.length() - 2*i +distance; 
}

int findUnCommon(string word1, string word2){
	int frequency[26];
	for(int i=0; i<26; i++){ frequency[i] = 0; }

	for(char c: word1){ frequency[CHAR_TO_INDEX(c)]++; }
	for(char c: word2){ frequency[CHAR_TO_INDEX(c)]--; }
	int uncommon = 0;
	for(int i=0; i<26; i++){
		uncommon+=abs(frequency[i]);
	}
	return uncommon;
}

int longestPrefix(string word1, string word2){

	int len = word1.length()>word2.length() ? word2.length() : word1.length();
	for(int i = 0; i<len; i++){
		if(word1[i] != word2[i]){return i;}
	}
	return len;
}

int cost(string word1, string word2){
	return (findDistance(word1,word2) + findUnCommon(word1,word2) - longestPrefix(word1,word2));
}



class Trie{
private:
	struct trieNode* root;
	
public:
	int size;
	Trie(){
		size = 0;
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
		size++;
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

	void printAll(trieNode* temp, string word = "", int flag = 0, string inp = ""){
		if(temp->isEnd == true && flag){
			if(cost(word,inp)<5){
				ln.push_back(make_pair(cost(word,inp),word));
			}
		}
		if(temp->isEnd == false || isLast(word) == false){
			for(int i = 0; i<26 ; i++){
				if(temp->children[i] != NULL){
					if(flag == 0)
						word = "";
					printAll(temp->children[i],word + (char)(i+96+1),flag+1,inp);
				}
			}
		}
	}

	void recommend(string word){
		if(searchWord(word)){
			cout<<word<<" is the correct spelling!"<<endl;
			return;
		}
		trieNode* temp = root;
		printAll(temp,"",0,word);
		sort(ln.begin(), ln.end());
		int i = 1;
		for(vector< pair<int, string> > :: iterator itr = ln.begin(); itr!= ln.end(); itr++){
			cout<<itr->second<<endl;
			if(i%10==0){
				cout<<"View more? [1/0]: ";
				cin>>i;
				if(!i){return;}
			}
			else{i++;}
		}
	}
};


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
		ln.clear();
		int choice;
		cout<<"1-Check\n2-Recommendation\nAnything else-Exit\n";
		cin>>choice;

		if(choice == 1){
			string word;
			cout<<"What word would you like to check? Enter here: ";
			cin>>word;
			if(obj1.searchWord(word)){
				cout<<word<<" is the correct spelling!"<<endl;
			}
			else{
				cout<<word<<" is the wrong spelling!"<<endl;	
			}
		}
		else if (choice == 2){
			string word;
			cout<<"What word would you like to check? Enter here: ";
			cin>>word;
			obj1.recommend(word);
		}
		else{ break; }
	}
}


// final055.cpp

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "defines.h"



int main() {
	// Read stop words
	string stop_words_joined;
	getline(cin, stop_words_joined);
	const set<string> stop_words = ParseStopWords(stop_words_joined);
	
	// Read query
	string query;
	getline(cin, query);
	const vector<string> query_words = ParseQuery(query, stop_words);
	
	for (const string& word : query_words) {
		cout << '[' << word << ']' << endl;
	}
    
    vector<string> documents = {
        "a fat cat sat on a mat and ate a fat rat"s,
        "little funny fluffy cat"s,
        "the cat"s,
        "huge green crocodile"s
    };
    
    map<string, set<int>> word_to_documents;
    for (int i = 0; i < documents.size(); ++i) {
        const string & doc = documents.at(i);
        AddDocument(word_to_documents, stop_words, i, doc);
    }
    
    vector<int> relevant_documents = FindDocuments(word_to_documents, stop_words, query);
    for (const int id : relevant_documents) {
        cout << id << endl;
    }
}

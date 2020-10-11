#include <map>
#include <set>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& text) {
	vector<string> words;
	string word;
	for (const char c : text) {
		if (c == ' ') {
			words.push_back(word);
			word = "";
		} else {
			word += c;
		}
	}
	words.push_back(word);
	
	return words;
}

set<string> ParseStopWords(const string& text) {
	set<string> stop_words;
	for (const string& word : SplitIntoWords(text)) {
		stop_words.insert(word);
	}
	return stop_words;
}

vector<string> ParseQuery(const string& text, const set<string>& stop_words) {
	vector<string> words;
	for (const string& word : SplitIntoWords(text)) {
		if (stop_words.count(word) == 0) {
			words.push_back(word);
		}
	}
	return words;
}

// typedef WordToDocumentsMap map<string, set<int>>;
void AddDocument(map<string, set<int>>& word_to_documents,
                 const set<string>& stop_words,
                 int document_id,
                     const string& document) {
    for (const string & word : SplitIntoWords(document)) {
        if (!stop_words.count(word)) {
            word_to_documents[word].insert(document_id);
        }
    }
}

vector<int> FindDocuments(const map<string, set<int>>& word_to_documents,
                          const set<string>& stop_words,
                          const string& query) {
    set<int> relevant_documents;
    for (const string & word : SplitIntoWords(query)) {
        if (!stop_words.count(word) && word_to_documents.count(word)) {
	  clog << "trying word " << word << endl;
            const set<int> & set_relevant_documents = word_to_documents.at(word);
            for (const int id : set_relevant_documents) {
                relevant_documents.insert( id );
            }
        }
    }
    
    return vector<int>(relevant_documents.begin(), relevant_documents.end());
}

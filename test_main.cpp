#include <gtest/gtest.h>
#include <iostream>

#include "defines.h"

/* TODO 
Задача прошла 0/44 проверок

Возможные проблемы:
- Вы неправильно обрабатываете случай, когда все документы исключены из запроса
- Вы неправильно обрабатываете общий случай
- Вы неправильно обрабатываете случай отсутствия стоп-слов
- Вы неправильно обрабатываете случай, когда один документ исключён из запроса
*/

class TestLesson4 : public ::testing::Test {
private:

protected:
  void SetUp() 
  { }
};

TEST_F(TestLesson4, testLessonExample) 
{
    set<string> stop_words = {
      "a"s, "the"s, "on"s, "cat"s
    };

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

    const string query = "funny fat cat"s;

    vector<int> vec_found = FindDocuments(word_to_documents, stop_words, query);
    //    vector<int> vec_expected = { 0, 1 };
    //    EXPECT_EQ(vec_found, vec_expected);

    set<int> set_found(vec_found.begin(), vec_found.end());
    set<int> set_expected = { 0, 1 };
    EXPECT_EQ(set_found, set_expected);
}

TEST_F(TestLesson4, testNoStopWords)
{
    set<string> stop_words = { };

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

    const string query = "funny fat cat"s;

    vector<int> vec_found = FindDocuments(word_to_documents, stop_words, query);
    set<int> set_found(vec_found.begin(), vec_found.end());
    set<int> set_expected = { 0, 1, 2 };
    EXPECT_EQ(set_found, set_expected);  
}

TEST_F(TestLesson4, testNoRelevantDocuments)
{
    set<string> stop_words = {
      "a"s, "the"s, "on"s, "cat"s
    };

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

    const string query = "no words found"s;

    vector<int> vec_found = FindDocuments(word_to_documents, stop_words, query);
    set<int> set_found(vec_found.begin(), vec_found.end());
    set<int> set_expected = { };
    EXPECT_EQ(set_found, set_expected);
}

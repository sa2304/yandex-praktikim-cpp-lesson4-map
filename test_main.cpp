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
  vector<string> m_documents;
  set<string> m_stopWords;
  map<string, set<int>> m_wordToDocuments;

  void SetUp() {
    m_documents = {
        "a fat cat sat on a mat and ate a fat rat"s,
        "little funny fluffy cat"s,
        "the cat"s,
        "huge green crocodile"s
    };

    m_stopWords = {
      "a"s, "the"s, "on"s, "cat"s
    };

    for (int i = 0; i < m_documents.size(); ++i) {
        const string & doc = m_documents.at(i);
        AddDocument(m_wordToDocuments, m_stopWords, i, doc);
    }
  }
};

TEST_F(TestLesson4, testLessonExample) 
{
    const string query = "funny fat cat"s;

    vector<int> vec_found = FindDocuments(m_wordToDocuments, m_stopWords, query);
    vector<int> vec_expected = { 0, 1 };
    EXPECT_EQ(vec_found, vec_expected);

    set<int> set_found(vec_found.begin(), vec_found.end());
    set<int> set_expected = { 0, 1 };
    EXPECT_EQ(set_found, set_expected);

}

// TEST_F(TestLesson4, testNoRelevantDocuments)

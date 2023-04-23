#pragma once
#include <string>

const int ALPHABET_SIZE = 26;                   // ������ ����.�������� 
const int MAX_LETTERS_IN_WORD = 15;             // ����.���������� ���� � �����
const int MAX_SIZE_AVTODOP = 5;                 // ����.������ �������������� = 5 ���� �� ����� 

class WordsTree                                 
{
private:
    WordsTree* children[ALPHABET_SIZE];
    bool isEndOfWord;                           // isEndOfWord - true, ���� ���� �������� ������ �����
   
public:

    WordsTree() = default;
    ~WordsTree() = default;    
   
    void branchSearch(WordsTree* root, std::string& prefix, int& countLettersPrefix);
    void choiceWord(int count, std::string arrWord[], std::string& prefix, int& countLettersPrefix);
    void autocompleteWords(WordsTree* root, char buf[], std::string arrWord[], int ind, int& count, std::string& prefix, int countLettersPrefix);
    void showAllWords(WordsTree* root, char buf[], int ind);
    WordsTree* getNewNode();
    void insert(WordsTree* root, const std::string& key);
    bool search(WordsTree* root, const std::string& key);
    bool isEmpty(WordsTree* root);
    WordsTree* remove(WordsTree* root, const std::string& key, int depth = 0);
    WordsTree* tree�reation(WordsTree* root);    
};
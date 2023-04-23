#pragma once
#include <string>

const int ALPHABET_SIZE = 26;                   // Размер англ.алфавита 
const int MAX_LETTERS_IN_WORD = 15;             // Макс.количество букв в слове
const int MAX_SIZE_AVTODOP = 5;                 // Макс.размер автодополнения = 5 слов на выбор 

class WordsTree                                 
{
private:
    WordsTree* children[ALPHABET_SIZE];
    bool isEndOfWord;                           // isEndOfWord - true, если ключ является концом слова
   
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
    WordsTree* treeСreation(WordsTree* root);    
};
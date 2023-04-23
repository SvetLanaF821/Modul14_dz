#include "WordsTree.h"
#include <iostream>
#include <conio.h>

// ����������� ������� - �����/����� ���� ����
void WordsTree::showAllWords(WordsTree* root, char buf[], int ind){
    
    if (!root) {
        std::cout << "Slovar pust." << std::endl;
        return;
    }

    if (root->isEndOfWord == true) {
        if (!isEmpty(root)) {
            buf[ind] = '\0';
            std::cout << buf << std::endl;
        }
        else {
            buf[ind] = '\0';
            std::cout << buf << std::endl;
            return;
        }        
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i] != nullptr) {
            buf[ind] = i + 'a';
            showAllWords(root->children[i], buf, ind + 1);
        }
    }
}

// ����� ���� �� �������������� "���������������"
void WordsTree::choiceWord(int count, std::string arrWord[], std::string& prefix, int& countLettersPrefix) {
    std::cout << "Libo lyuboy drugoy cimvol, esli slova net." << std::endl;
    char vibor = _getch();

    for (int i = 0; i < count; ++i) {
        if (vibor == 48 + i) {                        // ���� ������ 0, 1, 2,...
            std::cout << "Vash vybor: " << arrWord[i] << std::endl;
            countLettersPrefix = 0;
            prefix.clear();
        }        
    }

    if (countLettersPrefix != 0)
        std::cout << "Vozmozhno takogo slova net." << std::endl;    
}

// ����������� ������� - ����� �������������� 
void WordsTree::autocompleteWords(WordsTree* root, char buf[], std::string arrWord[], int ind, int& count, std::string& prefix, int countLettersPrefix)
{
    if (root->isEndOfWord == true) {            // ���� ����� �����, �� ������� ��� �� �������
        if (!isEmpty(root)) {           
            buf[ind] = '\0';
            arrWord[count] = buf;
            std::cout << buf << "\t( nazhmite - " << count << " )" << std::endl;
            count++;
        }
        else {            
            buf[ind] = '\0';
            arrWord[count] = buf;
            std::cout << buf << "\t( nazhmite - " << count << " )" << std::endl;
            count++;
            return;
        }
    }
    
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        // (���� �����-������� ���� � ������ � ���� ������ �������� � �� ����� ����� � ������)
        // ��� (���� �����-������� ���� � ������ � ��� ������� ��������) 
        // �� ���������  ����� �� ������� ����������
        if ((root->children[i] != nullptr && ind < countLettersPrefix && prefix[ind] == ('a' + i))
            || (root->children[i] != nullptr && ind >= countLettersPrefix)) { 
            buf[ind] = i + 'a';
            if (count < MAX_SIZE_AVTODOP) {
                autocompleteWords(root->children[i], buf, arrWord, ind + 1, count, prefix, countLettersPrefix);
            }
            else {                
                return;
            }
        }
    }        
}

//����� ������ ����� ��� ������ �������������� 
void WordsTree::branchSearch(WordsTree* root, std::string& prefix, int& countLettersPrefix) {
    
    if (!root) {
        std::cout << "Slovar pust." << std::endl;
        return;
    }

    int indV = 0;                               // ������ �����
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i] != nullptr && ('a' + i) == prefix[indV]) {
            char buf[MAX_LETTERS_IN_WORD]{};            
            buf[indV] = i + 'a';
            int count = 0;
            std::string arrWord[MAX_SIZE_AVTODOP] = {};

            autocompleteWords(root->children[i], buf, arrWord, indV + 1, count, prefix, countLettersPrefix);
            choiceWord(count, arrWord, prefix, countLettersPrefix);   

            std::cout << "\nVashe slovo:\t" << prefix << "......" << std::endl;
            std::cout << "Prodolzhayte dalshe vvodit slovo." << std::endl;
            return;
        }
    }
    std::cout << "Takogo slova net." << std::endl;
    prefix.clear();
    countLettersPrefix = 0;
}

// ���������� ����� ���� � ������� ������
WordsTree* WordsTree::getNewNode()
{
    // �������� ������ ��� ����� ����
    WordsTree* wNode = new WordsTree;

    // ������������� ���� ����� ����� � false
    wNode->isEndOfWord = false;
    
    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        wNode->children[i] = nullptr;

    return wNode;
}

// ��������� ���� � ������, ���� ��� ���, 
// �����, ���� ���� ������� ��������� ���� ������,
// �������� � �������� ���������, �.�. ����� �����
void WordsTree::insert(WordsTree* root, const std::string& key)
{
    WordsTree* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � �������� ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� ������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// �����. ���������� true ���� ���� ���� � ������, ����� false 
bool WordsTree::search(WordsTree* root, const std::string& key)
{
    WordsTree* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// ���������� true ���� root ����� ����, ����� false 
bool WordsTree::isEmpty(WordsTree* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������ 
WordsTree* WordsTree::remove(WordsTree* root, const std::string& key, int depth)
{
    // ���� ������ ������ 
    if (!root)
        return nullptr;

    // ���� ����� �� ����� ����� 
    if (depth == key.size()) {

        // ���� ���� ������ �� ����� ����� 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }
        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
    // ���������������� ������� 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // ���� � ����� ��� ��������� ����� 
    // (������ ������ ���� ��� �������� �������), 
    // � �� �� ������������� ������ ������. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    
    // ���������� ����� ������
    return root;
}

// �������� ������ - �������
WordsTree* WordsTree::tree�reation(WordsTree* root) {
    
    insert(root, "kaban");
    insert(root, "kalina");
    insert(root, "kaloshi");
    insert(root, "kambala");
    insert(root, "kanareyka");
    insert(root, "kanikuly");
    insert(root, "kapel");
    insert(root, "kapkan");
    insert(root, "kapusta");
    insert(root, "karavan");
    insert(root, "kartophel");
    insert(root, "karas");
    insert(root, "karp");
    insert(root, "kedr");
    insert(root, "kedrovka");
    insert(root, "klever");
    insert(root, "klen");
    insert(root, "klest");
    insert(root, "koza");
    insert(root, "kozel");
    insert(root, "kozlyonok");
    insert(root, "komar");
    insert(root, "kombayn");
    insert(root, "konek");
    insert(root, "kon");
    insert(root, "konki");
    return root;
}
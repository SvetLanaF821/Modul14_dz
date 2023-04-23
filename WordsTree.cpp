#include "WordsTree.h"
#include <iostream>
#include <conio.h>

// Рекурсивная функция - показ/вывод всех слов
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

// Выбор слов из представленных "автодополнением"
void WordsTree::choiceWord(int count, std::string arrWord[], std::string& prefix, int& countLettersPrefix) {
    std::cout << "Libo lyuboy drugoy cimvol, esli slova net." << std::endl;
    char vibor = _getch();

    for (int i = 0; i < count; ++i) {
        if (vibor == 48 + i) {                        // Если нажаты 0, 1, 2,...
            std::cout << "Vash vybor: " << arrWord[i] << std::endl;
            countLettersPrefix = 0;
            prefix.clear();
        }        
    }

    if (countLettersPrefix != 0)
        std::cout << "Vozmozhno takogo slova net." << std::endl;    
}

// Рекурсивная функция - вывод автодополнения 
void WordsTree::autocompleteWords(WordsTree* root, char buf[], std::string arrWord[], int ind, int& count, std::string& prefix, int countLettersPrefix)
{
    if (root->isEndOfWord == true) {            // Если конец слова, то выводит его на консоль
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
        // (если буква-ребенок есть в дереве И есть символ префикса И он равен букве в дереве)
        // ИЛИ (если буква-ребенок есть в дереве И нет символа префикса) 
        // то заполняем  буфер со словами рекурсивно
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

//Поиск нужной ветки для печати автодополнения 
void WordsTree::branchSearch(WordsTree* root, std::string& prefix, int& countLettersPrefix) {
    
    if (!root) {
        std::cout << "Slovar pust." << std::endl;
        return;
    }

    int indV = 0;                               // Индекс ветки
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

// Возвращает новый узел с пустыми детьми
WordsTree* WordsTree::getNewNode()
{
    // Выделяем память под новый узел
    WordsTree* wNode = new WordsTree;

    // устанавливаем флаг конца слова в false
    wNode->isEndOfWord = false;
    
    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        wNode->children[i] = nullptr;

    return wNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе, если ключ явлется префиксом узла дерева,
// помечает в качестве листового, т.е. конец слова
void WordsTree::insert(WordsTree* root, const std::string& key)
{
    WordsTree* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфавите через смещение относительно первой буквы
        int index = key[i] - 'a';

        // если указатель пустой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Поиск. Возврашает true если ключ есть в дереве, иначе false 
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

// Возвращает true если root имеет лист, иначе false 
bool WordsTree::isEmpty(WordsTree* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
WordsTree* WordsTree::remove(WordsTree* root, const std::string& key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }
        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    
    // возвращаем новый корень
    return root;
}

// Создание дерева - словаря
WordsTree* WordsTree::treeСreation(WordsTree* root) {
    
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
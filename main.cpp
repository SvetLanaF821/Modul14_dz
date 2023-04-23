#include "WordsTree.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

//установка цвета текста консоли
void SetColor(int text, int bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int main()
{
    WordsTree* root1, wordsTree;
    root1 = wordsTree.getNewNode();
    wordsTree.treeСreation(root1);
    char choice;
    while (true) {
        SetColor(14, 0);
        std::cout << "\nPokazat vse slova iz slovarya - 1" << std::endl;
        std::cout << "Poisk slova s avtodopolneniem - 2" << std::endl;
        std::cout << "Dobavit slovo v slovar        - 3" << std::endl;
        std::cout << "Udalit slovo iz slovarya      - 4" << std::endl;
        std::cout << "Vyhod                         - 0" << std::endl;

        std::cin >> choice;
        std::string word;
        char letter = 0;
        int countLettersPref = 0;
        char bufer[MAX_LETTERS_IN_WORD] = {};
        int index = 0;

        switch (choice) {
        case '1':
            SetColor(7, 0);
            wordsTree.showAllWords(root1, bufer, index);
            break;

        case '2':
            SetColor(11, 0);
            std::cout << "Vvedite slovo: " << std::endl;
            
            while (letter != 32) {
                std::cout << "*** Vyhod - probel. *** " << std::endl;
                letter = _getch();
                word += letter;
                if (letter != 32)
                    wordsTree.branchSearch(root1, word, ++countLettersPref);
                std::cout << std::endl;
            }
            break;

        case '3':
            SetColor(10, 0);
            std::cout << "Vvedite slovo: ";
            std::cin >> word;

            if (word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == std::string::npos)
                wordsTree.insert(root1, word);                
            else {
                SetColor(4, 0);
                std::cout << "Oshibka. V slove dolzhny byt tolko bukvy. " << std::endl;
            }
            break;
       
        case '4':
            SetColor(9, 0);
            std::cout << "Vvedite slovo: ";
            std::cin >> word;

            if ((word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == std::string::npos) &&
                (wordsTree.search(root1, word)))
                wordsTree.remove(root1, word, 0);
            else {
                SetColor(4, 0);
                std::cout << "Oshibka. Takogo slova net. " << std::endl;
            }
            break;

        case '0':
            SetColor(7, 0);
            return 0;
            break;

        default:
            SetColor(4, 0);
            std::cout << "Oshibka. Poprobuyte zanovo." << std::endl;
            break;
        }       
    }
    return 0;
}
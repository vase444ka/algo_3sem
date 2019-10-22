#include <iostream>
#include <time.h>
#include <string>

const int WORDLEN = 100;

void gen_correct(std::string &text, std::string &word){
    char tmp_word[WORDLEN];
    for (int i = 0; i < WORDLEN; i++)
        text = text + char(65 + rand()%26);

    std::string tmp = text + text;
    int len = tmp.copy(tmp_word, WORDLEN, rand()%WORDLEN);
    tmp_word[len] = '\0';
    word = std::string(tmp_word);
}

void gen_incorrect(std::string &text, std::string &word){
    for (int i = 0; i < WORDLEN; i++)
        text = text + char(65 + rand()%26);

    for (int i = 0; i < WORDLEN; i++)
        word = word + char(65 + rand()%26);
}

int main() {
    srand(time(0));
    std::string word, text;
    int is_correct;
    std::cout<<"enter 1 if it should be YES, 0 - if NO\n";
    freopen("input.txt", "w", stdout);
    std::cin>>is_correct;
    if (is_correct)
        gen_correct(text, word);
    else
        gen_incorrect(text, word);

    std::cout<<text<<std::endl<<word<<std::endl<<is_correct;

    return 0;
}
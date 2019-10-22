#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

std::vector <int> z_func(std::string s){
    int n = s.size(), l = 0, r = 0;
    std::vector <int> z(n);
    for (int i = 1; i < n; i++){
        if (i <= r)
            z[i] = std::min (r-i+1, z[i-l]);

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;

        if (i + z[i] - 1 > r)
            l = i,  r = i + z[i] - 1;
    }

    return z;
}

bool is_word_in_text(std::string text, const std::string &word){
    text = text + text;
    text = word + text;
    int word_len = word.size();
    std::vector <int> z = z_func(text);
    for (int i = word_len; i < text.size(); i++)
        if (z[i] >= word_len)
            return true;

    return false;
}

int main() {
    freopen("../../6lab_randomizer/cmake-build-debug/input.txt", "r", stdin);
    std::string word, text;
    std::cin>>text>>word;
    int tacts = clock();
    if (word.size() != text.size()){
        std::cout<<"NO\n";
        return 0;
    }
    bool ans = is_word_in_text(text, word);
    tacts = clock(); //- tacts;
    std::cout<<"Time needed for algorithm: "<< (float(tacts)) / CLOCKS_PER_SEC <<" s.\n";
    if (ans)
        std::cout<<"YES\n";
    else
        std::cout<<"NO\n";
    return 0;
}
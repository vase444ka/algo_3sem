#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    std::string word, text;
    std::cin>>text>>word;
    if (word.size() != text.size()){
        std::cout<<"NO\n";
        return 0;
    }
    if (is_word_in_text(text, word))
        std::cout<<"YES\n";
    else
        std::cout<<"NO\n";
    return 0;
}
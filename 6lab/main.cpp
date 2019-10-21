#include <iostream>
#include <string>
#include <vector>

std::vector <int> z_func(std::string s){
    int n = s.size(), l = 0, r = 0;
    std::vector <int> z(n);
    for (int i = 1; i < n; i++){
        if (i > r){
            l = i;
            r = i;
            while(r < n && s[r] == s[z[i]]){
                r++;
                z[i]++;
            }
        }
        else{


        }
    }

}

bool is_word_in_text(std::string text, std::string word){
    text = text + text;
    text = word + text;
    int word_len = word.size();
    std::vector <int> z = z_func(text);
}

int main() {
    std::string word, text;
    if (word.size() != text.size()){
        cout<<"NO\n";
        return 0;
    }
    if (is_word_in_text(text, word))
        cout<<"YES\n";
    else
        cout<<"NO\n";
    return 0;
}
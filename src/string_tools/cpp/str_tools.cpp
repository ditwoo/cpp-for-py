#include "str_tools.h"

bool str_tools::cpp_is_palindrome(std::string& s){
    bool is_palindrome = true;
    int s_size = s.length();
    for (int i = 0; i < s_size / 2; i++) {
        is_palindrome &= (s[i] == s[s_size - i - 1]);
    }
    return is_palindrome;
};
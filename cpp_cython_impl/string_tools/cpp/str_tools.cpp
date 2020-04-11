#include "str_tools.h"

namespace str_tools{

bool cpp_is_palindrome(std::string& s){
    bool is_palindrome = true;
    int s_size = s.length();
    for (int i = 0; i < s_size / 2; i++) {
        is_palindrome &= (s[i] == s[s_size - i - 1]);
    }
    return is_palindrome;
};

TrieNode::TrieNode() {};

TrieNode::TrieNode(char s) {
    this->symbol = s;
};

TrieNode::TrieNode(char s, std::vector<TrieNode>& c) {
    this->symbol = s;
    this->child = c;
}

void add(TrieNode* root, std::string& word) {
    TrieNode* node = root;
    for (size_t i = 0; i < word.length(); i++) {
        char cur_symbol = word[i];
        bool found_in_child = false;

        for (size_t j = 0; j < node->child.size(); j++) {
            TrieNode* child = &node->child[j];

            if (child->symbol == cur_symbol) {
                child->counter++;
                node = child;
                found_in_child = true;
                break;
            }
        }

        if (!found_in_child) {
            TrieNode new_node = TrieNode(cur_symbol);
            node->child.push_back(new_node);
            node = &new_node;
        }
    }
    node->is_leaf = true;
};

bool found_prefix(TrieNode* root, std::string& prefix) {
    TrieNode* node = root;
    if (!node->child.size()) 
        return false;
    
    for (size_t i = 0; i < prefix.length(); i++) {
        char curr_symbol = prefix[i];
        bool is_not_found = true;

        for (size_t j = 0; j < node->child.size(); j++) {
            TrieNode* child = &node->child[j];

            if (child->symbol == curr_symbol) {
                is_not_found = false;
                node = child;
                break;
            }
        }

        if (is_not_found) {
            return false;
        }
    }

    return true;
}


}
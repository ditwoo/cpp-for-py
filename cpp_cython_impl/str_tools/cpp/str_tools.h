#ifndef STR_TOOLS_H
#define STR_TOOLS_H

#include <string>
#include <vector>

namespace str_tools {

    bool cpp_is_palindrome(std::string& s);

    class TrieNode {
        public:
            char symbol;
            std::vector<TrieNode> child;
            bool is_leaf = false;
            int counter = 1;

            TrieNode();
            TrieNode(char s);
            TrieNode(char s, std::vector<TrieNode>& c);

    };

    void add(TrieNode* root, std::string& word);
    bool found_prefix(TrieNode* root, std::string& prefix);

}

#endif
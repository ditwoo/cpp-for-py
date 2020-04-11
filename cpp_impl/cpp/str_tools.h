
#ifndef STR_TOOLS_H
#define STR_TOOLS_H

#include "Python.h"
#include <string>
#include <vector>

namespace str_tools {

    bool is_palindrome(std::string &);

    class TrieNode {

        public:
            char symbol;
            std::vector<TrieNode> child;
            bool is_leaf = false;
            int counter = 1;

            TrieNode(char s);
    };

    void add(TrieNode *, std::string &);
    bool found_prefix(TrieNode *, std::string &);

    struct PyTrie {
        PyObject_HEAD
        TrieNode *trie_node; 
    };

}

#endif
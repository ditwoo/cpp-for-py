# distutils: language = c++

from libcpp cimport bool
from libcpp.string cimport string


cdef extern from "<vector>" namespace "std":
    cdef cppclass vector[T]:
        cppclass iterator:
            T operator*()
            iterator operator++()
            bint operator==(iterator)
            bint operator!=(iterator)
        vector()
        void push_back(T&)
        T& operator[](int)
        T& at(int)
        iterator begin()
        iterator end()


cdef extern from "str_tools.h" namespace "str_tools":
    bool cpp_is_palindrome(string s)

    cdef cppclass TrieNode:
        TrieNode()
        TrieNode(char) except +
        TrieNode(char, vector[TrieNode])
        char symbol
        vector[TrieNode] child
        bool is_leaf
        int counter

    void add(TrieNode* root, string word)
    bool found_prefix(TrieNode* root, string prefix)


def cy_is_palindrome(str s):
    if s is not None:
        str_bytes = s.encode()
        return cpp_is_palindrome(str_bytes)


cdef class PyTrie:
    cdef TrieNode root  # holds root node

    def __init__(self, words = None):
        self.root = TrieNode(b'*')
        if words:
            for word in words:
                self.add(word)
    
    def add(self, word):
        add(&self.root, word.encode())
    
    def update(self, words):
        for word in words:
            self.add(word)
    
    def __contains__(self, word):
        return found_prefix(&self.root, word.encode())

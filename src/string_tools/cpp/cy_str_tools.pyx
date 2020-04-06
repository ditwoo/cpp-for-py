# distutils: language = c++

from libcpp cimport bool
from libcpp.string cimport string


cdef extern from "str_tools.h" namespace "str_tools":
    bool cpp_is_palindrome(string s)


def cy_is_palindrome(str s):
    if s is not None:
        str_bytes = s.encode()
        return cpp_is_palindrome(str_bytes)

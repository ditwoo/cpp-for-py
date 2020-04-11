import pytest
import str_tools


def test_atributes_in_module():
    module_to_check = str_tools
    module_properties = dir(module_to_check)

    assert "py_is_palindrome" in module_properties
    assert "_string_tools_cython" in module_properties


def test_is_palindrome_on_correct_input():
    palindrome = "abcba"

    assert str_tools.py_is_palindrome(palindrome)


def test_is_palindrome_on_wrong_input():
    not_palindrome = "abcdef"

    assert not str_tools.py_is_palindrome(not_palindrome)


def test_pytrie_properties():
    module_to_check = str_tools.PyTrie
    module_properties = dir(module_to_check)

    assert "__contains__" in module_properties
    assert "add" in module_properties
    assert "update" in module_properties


def test_pytrie_on_correct_prefix():
    trie = str_tools.PyTrie(["a", "ab", "abc"])

    to_check = "ab"
    assert to_check in trie


def test_pytrie_on_wrong_prefix():
    trie = str_tools.PyTrie(["a", "ab", "abc"])

    to_check = "ccc"
    assert not to_check in trie

import pytest
import str_tools


def test_atributes_in_module():
    module_to_check = str_tools
    module_properties = dir(module_to_check)

    assert "PyTrie" in module_properties
    assert "is_palindrome" in module_properties


def test_is_palindrome_on_correct_input():
    palindrome = "abcba"

    assert str_tools.is_palindrome(palindrome)


def test_is_palindrome_on_wrong_input():
    not_palindrome = "abcdef"

    assert not str_tools.is_palindrome(not_palindrome)


def test_is_palindrome_on_number_input():
    number = 12345

    with pytest.raises(TypeError):
        str_tools.is_palindrome(number)


def test_pytrie_properties():
    module_to_check = str_tools.PyTrie
    module_properties = dir(module_to_check)

    assert "__contains__" in module_properties
    assert "add" in module_properties
    assert "update" in module_properties


def test_pytrie_update():
    trie = str_tools.PyTrie("a")
    trie.update(["ab", "abc"])

    to_check = "ab"

    assert trie.__contains__(to_check)


def test_pytrie_update_with_wrong_type():
    trie = str_tools.PyTrie("a")

    with pytest.raises(ValueError):
        trie.update(["ab", "abc", 12345])


# def test_pytrie_on_correct_preffix_with_in_operator():
#     trie = str_tools.PyTrie("a")
#     trie.add("ab")
#     trie.add("abc")

#     to_check = "ab"

#     assert to_check in trie


def test_pytrie_on_correct_preffix():
    trie = str_tools.PyTrie("a")
    trie.add("ab")
    trie.add("abc")

    to_check = "ab"

    assert trie.__contains__(to_check)


def test_pytrie_on_wrong_preffix():
    trie = str_tools.PyTrie("a")
    trie.add("ab")
    trie.add("abc")

    to_check = "bc"

    assert not trie.__contains__(to_check)

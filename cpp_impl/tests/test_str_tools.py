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


# def atributes(module):
#     print()
#     print(f"'{module.__name__}' atributes:")
#     for item in dir(module):
#         print(" •", item)

# def test_is_palindrome():
#     if hasattr(str_tools, "is_palindrome"):
#         print()

#         palindrome_str = "abcdcba"
#         print(f"Is palindrome '{palindrome_str}' -", str_tools.is_palindrome(palindrome_str))

#         wrong_str = "abcd"
#         print(f"Is palindrome '{wrong_str}' -", str_tools.is_palindrome(wrong_str))


# if __name__ == "__main__":
#     print("*" * 100)
#     atributes(str_tools)
#     test_is_palindrome()

#     print("*" * 100)
#     atributes(str_tools.PyTrie)

#     t = str_tools.PyTrie("a")
#     t.add("ab")
#     t.add("abc")

#     lookup_preffix = "ab"
#     print(t.__contains__(lookup_preffix))
#     print(lookup_preffix in t)

#     # print(trie.__contains__(t, "a"))

#         # num = 123
#         # print(str_tools.is_palindrome(num))
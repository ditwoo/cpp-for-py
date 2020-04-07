import string_tools

print("Atributes of 'string_tools':")
for item in dir(string_tools):
    print(item)
print()

print(f"Atributes of 'string_tools._string_tools_cython':")
for next_lvl_atr in dir(string_tools._string_tools_cython):
    print(next_lvl_atr)
print()

str_to_check = "abba"
print(f"Does palindrome detected in '{str_to_check}' - {string_tools.py_is_palindrome(str_to_check)}")

str_to_check = "abbab"
print(f"Does palindrome detected in '{str_to_check}' - {string_tools.py_is_palindrome(str_to_check)}")

print()

trie = string_tools.PyTrie(["a", "ab", "abc"])

prefix_to_check = "ab"
print(f"Does '{prefix_to_check}' in trie ?\n {prefix_to_check in trie}")

prefix_to_check = "c"
print(f"Does '{prefix_to_check}' in trie ?\n {prefix_to_check in trie}")

prefix_to_check = "cccc"
print(f"Does '{prefix_to_check}' in trie ?\n {prefix_to_check in trie}")

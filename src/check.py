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

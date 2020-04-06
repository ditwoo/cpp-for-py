import string_tools

print("Atributes of 'string_tools':")
for item in dir(string_tools):
    print(item)
print()

print(f"Atributes of 'string_tools._string_tools_cython':")
for next_lvl_atr in dir(string_tools._string_tools_cython):
    print(next_lvl_atr)
print()

print(string_tools.py_is_palindrome("abba"))
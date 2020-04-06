
import _string_tools_cython

def py_is_palindrome(text: str) -> bool:
    return _string_tools_cython.cy_is_palindrome(text)

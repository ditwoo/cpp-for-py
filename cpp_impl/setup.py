from distutils.core import setup, Extension

setup(
    name="str_tools",
    version="1.0.0",
    ext_modules=[
        Extension(
            "str_tools", [
            "cpp/str_tools.cpp",
        ]),
    ]
)
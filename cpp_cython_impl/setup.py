from setuptools import Extension
from setuptools import setup
from setuptools import find_packages
from Cython.Build import cythonize

extensions = [
    Extension(
        name="_string_tools_cython",
        sources=[
            "str_tools/cpp/cy_str_tools.pyx",
            "str_tools/cpp/str_tools.cpp"
        ],
        extra_compile_args=["-std=c++11", "-pthread", "-O3"],
        language="c++",
    )
]

setup(
    name="str_tools",
    version="1.1.0",
    packages=find_packages(),
    ext_modules=cythonize(extensions, annotate=True),
)

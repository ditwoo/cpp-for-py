
# Python Wrappers for C++ code

## Preparations

Please create sandbox environment where you can ~destroy everything~ practice. 

If you have Anaconda you can clone base env:

```bash
conda create --name cpp_packages --clone base
```

Otherwise please check [python docs about virtual envs](https://docs.python.org/3/library/venv.html).


Soo ... if you are conda user (like me) please do not forget to activate recentry created environment, <br>
you can do this with the following command:

```bash
source activate cpp_packages
```


## Building package and testing

To build a package you should do something like this:

```bash
python setup.py build_ext --inplace
```

Next good practice is to test your code. <br>
The most pythonic way to do this is to write tests using PyTest or something similar. <br>
To run tests you just need:

```bash
python -m pytest
```

This command will check `test` (or `tests`) directory and execute all files with `test*.py` pattern.

## Some links

* [Using C++ in Cython](https://cython.readthedocs.io/en/latest/src/userguide/wrapping_CPlusPlus.html#compilation-and-importing)
* [Python C API: Introduction](https://docs.python.org/3/c-api/intro.html)
* [Python C API: Defining New Types](https://docs.python.org/3.3/extending/newtypes.html?highlight=pytypeobject)
* [Python C API: Type Objects](https://docs.python.org/3/c-api/typeobj.html)
* [How to Package Cython and Cython-wrapped C++ Code within a python module](https://github.com/AshleySetter/HowToPackageCythonAndCppFuncs)
* [C++ class in Python](http://www.speedupcode.com/c-class-in-python3/)

Series of blog posts about `boost::python`:
* [part 1](https://habr.com/ru/post/168083/)
* [part 2](https://habr.com/ru/post/168233/)
* [part 3](https://habr.com/ru/post/168827/)
* [part 4](https://habr.com/ru/post/169639/)

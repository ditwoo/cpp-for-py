
# C++ -> Cython -> Python module

## 0. Preparations

Please create env where you can practice. If you have Anaconda you can easily clone base env:

```bash
conda create --name cpp_packages --clone base
```

Do not forgot to activate environment:

```
source activate cpp_packages
```

## 1. Building extension

```bash
python setup.py build_ext --inplace
```

## 2. Runing some basic tests

```
python check.py
```

## Links

[Using C++ in Cython](https://cython.readthedocs.io/en/latest/src/userguide/wrapping_CPlusPlus.html#compilation-and-importing)


#include "Python.h"
#include "str_tools.h"
#include <string>


bool 
str_tools::is_palindrome(std::string &s){
    bool is_palindrome = true;
    int s_size = s.length();
    for (int i = 0; i < s_size / 2; i++) {
        is_palindrome &= (s[i] == s[s_size - i - 1]);
    }
    return is_palindrome;
};

str_tools::TrieNode::TrieNode(char s) {
    this->symbol = s;
};

void 
str_tools::add(TrieNode* root, std::string &word) {
    TrieNode *node = root;
    for (size_t i = 0; i < word.length(); i++) {
        char cur_symbol = word[i];
        bool found_in_child = false;

        for (size_t j = 0; j < node->child.size(); j++) {
            TrieNode* child = &node->child[j];

            if (child->symbol == cur_symbol) {
                child->counter++;
                node = child;
                found_in_child = true;
                break;
            }
        }

        if (!found_in_child) {
            TrieNode new_node = TrieNode(cur_symbol);
            node->child.push_back(new_node);
            node = &new_node;
        }
    }
    node->is_leaf = true;
};

bool 
str_tools::found_prefix(TrieNode *root, std::string &prefix) {
    TrieNode *node = root;
    if (!node->child.size()) 
        return false;
    
    for (size_t i = 0; i < prefix.length(); i++) {
        char curr_symbol = prefix[i];
        bool is_not_found = true;

        for (size_t j = 0; j < node->child.size(); j++) {
            TrieNode *child = &node->child[j];

            if (child->symbol == curr_symbol) {
                is_not_found = false;
                node = child;
                break;
            }
        }

        if (is_not_found) {
            return false;
        }
    }

    return true;
};

/* 
* Example: https://docs.python.org/3.3/extending/newtypes.html?highlight=pytypeobject
*/

static PyObject * 
method_is_palindrome(PyObject *self, PyObject *args) {
    char* ctext;

    if (!PyArg_ParseTuple(args, "s", &ctext)) {
        return nullptr;
    }

    std::string text(ctext);
    auto is_palindrome = str_tools::is_palindrome(text);

    return PyBool_FromLong(int(is_palindrome));
};


using str_tools::TrieNode;
using str_tools::PyTrie;


static void
PyTrie_dealoc(PyTrie *self) {
    Py_TYPE(self)->tp_free((PyObject *)self);
};

static PyObject *
PyTrie_new(PyTypeObject *type, PyObject *args, PyObject *kwars) {
    PyTrie *self = (PyTrie *)type->tp_alloc(type, 0);;

    // if (self != nullptr) {
    //     self->trie_node = new TrieNode('*');
    // }

    return (PyObject *)self;
};

static int
PyTrie_init(PyTrie* self, PyObject *args, PyObject *kwargs) {
    char *text_arg;
    static char *kwlist[] = {"text", NULL};

    /* TODO: support string or list of strings as input */
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|s", kwlist, &text_arg)) {
        return -1;
    }

    // PyObject *str = PyUnicode_AsEncodedString(text_arg, "utf-8", "~E~");
    // printf("[!] Encoded bytes!");

    // char *bytes = PyBytes_AsString(str);
    // printf("[!] Bytes - %s", bytes);

    std::string txt(text_arg);
    if (self->trie_node == nullptr) {
        self->trie_node = new TrieNode(txt[0]);
        std::string tail = txt.substr(1, txt.length());
        str_tools::add(self->trie_node, tail);
    } else {
        str_tools::add(self->trie_node, txt);
    }

    // if (text_arg != nullptr) {
        // Py_INCREF(text_arg);
        // PyObject *str = PyUnicode_AsEncodedString(text_arg, "utf-8", "~E~");
        // printf("[!] Encoded bytes!");

        // char *bytes = PyBytes_AsString(str);
        // printf("[!] Bytes - %s", bytes);

        // printf(">> %s\n", bytes);

        // std::string txt(bytes);
        // str_tools::add(self->trie_node, txt);
        // Py_DECREF(text_arg);
    // }

    return 0;
};


static int
PyTrie_traverse(PyTrie *self, visitproc visit, void *arg) {
    return 0;
};


static int
PyTrie_clear(PyTrie *self) {
    // decref all pyobjects
    return 0;
};


static PyObject *
PyTrie_add(PyTrie *self, PyObject *args) {
    char *ctext;
    if (!PyArg_ParseTuple(args, "s", &ctext)) {
        return nullptr;
    }
    std::string text(ctext);

    str_tools::add(self->trie_node, text);

    return Py_BuildValue(""); /* return nothing */
};


static PyObject *
PyTrie_update(PyTrie *self, PyObject *args) {
    PyObject *list_arg, *list_iter, *item;

    if (!PyArg_ParseTuple(args, "O", &list_arg)) {
        return nullptr;
    }

    list_iter = PyObject_GetIter(list_arg);
    if (!list_iter) {
        PyErr_SetString(PyExc_TypeError, "Required iterable object!");
        return nullptr;
    }

    while (true) {
        item = PyIter_Next(list_iter);
        
        // end of iterator
        if (!item) 
            break;

        // check for string
        if (!PyUnicode_Check(item)) {
            std::string err_msg(item->ob_type->tp_name);
            err_msg = "Elements of should be only strings but received '" + err_msg + "' !";
            PyErr_SetString(PyExc_ValueError, err_msg.c_str());
            return nullptr;
        }

        PyObject *enc_str = PyUnicode_AsEncodedString(item, "utf-8", "~E~");
        const char *bytes = PyBytes_AS_STRING(enc_str);
        std::string text(bytes);

        str_tools::add(self->trie_node, text);

        Py_XDECREF(item);
    }

    return Py_BuildValue(""); /* return nothing */
};


static PyObject *
PyTrie_contains(PyTrie *self, PyObject *args) {
    char *ctext;
    if (!PyArg_ParseTuple(args, "s", &ctext)) {
        return nullptr;
    }
    std::string text(ctext);

    auto is_found = str_tools::found_prefix(self->trie_node, text);
    return PyBool_FromLong(int(is_found));  /* return bool */
};

static PyMethodDef PyTrie_methods[] = {
    {"add", (PyCFunction)PyTrie_add, METH_VARARGS, "Add string to trie."},
    {"__contains__", (PyCFunction)PyTrie_contains, METH_VARARGS, "Check if passed preffix contains in Trie"},
    {"update", (PyCFunction)PyTrie_update, METH_VARARGS, "Add list of strings to Trie."},
    {NULL, NULL, 0, NULL}
};


// static PyMethodDef TrieNode_methods[] = {
//     {"__init__", construct_TrieNode, METH_VARARGS, "Constructor of Trie"},
//     {"add", add_TrieNode, METH_VARARGS, "Add string to a Trie"},
//     {"__contains__", contains_TrieNode, METH_VARARGS, "Check if string contains in Trie"},
//     {NULL, NULL, 0, NULL}
// };

// struct PyModuleDef trie_class = {
//     PyModuleDef_HEAD_INIT,
//     "cpptrie",
//     "Python interface for Trie from str_tools library",
//     -1,
//     TrieNode_methods,
// };

/*
* More about slots: https://docs.python.org/3/c-api/typeobj.html
*/

static PyTypeObject PyTrieType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "trie.PyTrie",                   /* tp_name */
    sizeof(PyTrie),                  /* tp_basicsize */
    0,                               /* tp_itemsize */
    (destructor)PyTrie_dealoc,       /* tp_dealloc */
    0,                               /* tp_print */
    0,                               /* tp_getattr */
    0,                               /* tp_setattr */
    0,                               /* tp_reserved */
    0,                               /* tp_repr */
    0,                               /* tp_as_number */
    0,                               /* tp_as_sequence */
    0,                               /* tp_as_mapping */
    0,                               /* tp_hash  */
    0,                               /* tp_call */
    0,                               /* tp_str */
    0,                               /* tp_getattro */
    0,                               /* tp_setattro */
    0,                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | 
    Py_TPFLAGS_BASETYPE | 
    Py_TPFLAGS_HAVE_GC,              /* tp_flags */
    "PyTrie objects",                /* tp_doc */
    (traverseproc)PyTrie_traverse,   /* tp_traverse */
    (inquiry)PyTrie_clear,           /* tp_clear */
    0,                               /* tp_richcompare */
    0,                               /* tp_weaklistoffset */
    0,                               /* tp_iter */
    0,                               /* tp_iternext */
    PyTrie_methods,                  /* tp_methods */
    0,                               /* tp_members */
    0,                               /* tp_getset */
    0,                               /* tp_base */
    0,                               /* tp_dict */
    0,                               /* tp_descr_get */
    0,                               /* tp_descr_set */
    0,                               /* tp_dictoffset */
    (initproc)PyTrie_init,           /* tp_init */
    0,                               /* tp_alloc */
    PyTrie_new,                      /* tp_new */
};


static PyMethodDef str_tools_methods[] = {
    {"is_palindrome", method_is_palindrome, METH_VARARGS, "Python interface for is_palindrome C++ library function"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef str_tools_module = {
    PyModuleDef_HEAD_INIT,
    "str_tools",
    "Python interface for string tools library",
    -1,
    str_tools_methods,
};

// PyMODINIT_FUNC PyInit_str_tools_trie(void) {
//     return PyModule_Create(&trie_class);
// };

PyMODINIT_FUNC 
PyInit_str_tools(void) {
    PyObject *m;

    if (PyType_Ready(&PyTrieType) < 0) 
        return nullptr;

    m = PyModule_Create(&str_tools_module);
    if (m == nullptr) 
        return nullptr;

    Py_INCREF(&PyTrieType);
    PyModule_AddObject(m, "PyTrie", (PyObject *)&PyTrieType);

    return m;
};

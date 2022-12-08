#define PY_SSIZE_T_CLEAN
#include <Python.h>

typedef struct {
    PyObject_HEAD
} AssertNeverDummy;

PyObject* never;

int an_bool(PyObject* self) {
    PyErr_SetString(PyExc_AssertionError, "reached never assertion");
    return -1;
}

static PyNumberMethods number_methods = {
    .nb_bool = an_bool
};

static PyTypeObject AssertNeverDummyType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "an._AssertNeverDummy",
    .tp_doc = PyDoc_STR("Custom objects"),
    .tp_basicsize = sizeof(AssertNeverDummy),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_as_number = &number_methods,
};

static PyModuleDef mod = {
    PyModuleDef_HEAD_INIT,
    .m_name = "an",
    .m_doc = "Syntactical sugar for assert never.",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_an(void) {
    PyObject* m;
    if (PyType_Ready(&AssertNeverDummyType) < 0)
        return NULL;

    m = PyModule_Create(&mod);
    if (m == NULL)
        return NULL;

    Py_INCREF(&AssertNeverDummyType);
    never = PyObject_Call((PyObject*) &AssertNeverDummyType, PyTuple_New(0), NULL);

    if (
        PyModule_AddObject(
            m,
            "_AssertNeverDummy",
            (PyObject*) &AssertNeverDummyType
        ) < 0 ||
        !never ||
        PyModule_AddObject(m, "never", never) < 0
    ) {
        Py_DECREF(&AssertNeverDummyType);
        Py_DECREF(m);
        Py_XDECREF(never);
        return NULL;
    }

    return m;
}
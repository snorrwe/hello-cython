# distutils: language = c++

from libcpp.string cimport string

cdef extern from "../cpp/greeting.cpp":
    pass


cdef extern from "../cpp/greeting.hpp" namespace "hello":
    cdef cppclass Greeting:
        Greeting(string)
        string greet(string)


cdef class PyGreeting:
    cdef Greeting *thisptr

    def __cinit__(self, prefix):
        self.thisptr = new Greeting(prefix)

    def greet(self, name):
        return self.thisptr.greet(name)

cdef extern from "../lib/algorithms/src/merge_sort.hpp" namespace "merge_sort":
    cdef void sort[It](It begin, It end)

cdef extern from "../lib/algorithms/src/quicksort.hpp" namespace "quicksort":
    cdef void sort[It](It begin, It end)

from libcpp.vector cimport vector
from cython.operator cimport dereference as deref, preincrement as inc

def int_sort(iterable):
    cdef vector[int]* vect = new vector[int]()
    cdef int i
    vect.reserve(len(iterable))
    for i in iterable:
        vect.push_back(i)
    sort(vect.begin(), vect.end())
    result = []
    it = vect.begin()
    while it != vect.end():
        result.append(deref(it))
        inc(it)
    del vect
    return result

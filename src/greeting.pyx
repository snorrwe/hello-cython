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

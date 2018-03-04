# distutils: language=c++
cimport numpy
import numpy

cdef extern from "<random>" namespace "std":
   cdef cppclass mt19937:
      mt19937() except +
      mt19937(unsigned int) except +
   cdef cppclass normal_distribution[T]:
      normal_distribution()
      normal_distribution(double, double)
      T operator()(mt19937)

cdef class Child:
   cdef mt19937 *rng
   cdef normal_distribution[double] uniform
   def __cinit__(Child self):
      cdef unsigned int seed = 123456789
      self.rng = NULL
      self.uniform = normal_distribution[double](0.,1.)
   cdef set_rng(Child self, mt19937& rng):
      self.rng = &rng
   def gen_uniform(self):
      return self.uniform(self.rng[0])

cdef class Parent:
   cdef mt19937 rng
   cdef public list children
   def __cinit__(Parent self):
      cdef unsigned int seed = 123456789
      self.rng = mt19937(seed)
      self.children = []
   cpdef make_child(Parent self):
      child = Child()
      child.set_rng(self.rng)
      self.children.append(child)

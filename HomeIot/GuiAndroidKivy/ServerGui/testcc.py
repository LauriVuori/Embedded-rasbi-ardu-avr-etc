from ctypes import *
so_file ="./Cfunc.so"
Cfunc = CDLL(so_file)

print(Cfunc.power(5))
#!/usr/bin/env python

from ctypes import *

cdll.LoadLibrary("./libbitshift.so")
_libbitshift = CDLL("libbitshift.so")

# set_point(uint8_t x, uint8_t y, bool state, uint8_t *matrix);
def set_point(x, y, state, matrix):
	_set_point = _libbitshift.set_point
	_set_point.argtypes = [c_int, c_int, c_bool, POINTER(c_int)]
	_set_point.restype = c_bool
	
	ret = _set_point(x, y, state, addressof(matrix))
	
	return ret;

"""
class ST_TEST(Structure):
    _fields_ = [("id", c_int),
                ("string", c_char_p)]

struct string_t {
    int memsize;
    int length;
    char *text;
    int error;
};
typedef struct string_t string;


class ST_STRING(Structure):
    _fields_ = [("memsize", c_int),
                ("length", c_int),
                ("text", c_char_p),
                ("error", c_int)]

def struct_test(id, str):
    _struct_test = _libtest.struct_test
    _struct_test.argtypes = [c_int, c_char_p]
    _struct_test.restype = ST_TEST
    
    ret = _struct_test(id, str)
    
    return [("id", ret.id),
            ("string", ret.string)]

# string str_readfile(char *filename, int bs)
def str_readfile(filename):
    _str_readfile = _libtest.str_readfile
    _str_readfile.argtypes = [c_char_p, c_int]
    _str_readfile.restype = ST_STRING

    ret = _str_readfile(filename, 512)
    
    return [("memsize", ret.memsize),
            ("length", ret.length),
            ("text", ret.text),
            ("error", ret.error)]
"""

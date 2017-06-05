#!/usr/bin/env python2
#-*- coding:utf-8 -*-

import sys,os
import ctypes

# load shared library
CUR_DICT_PATH = os.path.split(os.path.realpath(__file__))[0]
testlib = ctypes.CDLL(os.path.join(CUR_DICT_PATH,"libLCS.so"))


# run 
a = u"你好啊"
b = u"你很好啊"
c = ctypes.create_unicode_buffer(min(len(a),len(b)))

print testlib.LCS_finder(a,b,c)
print c.value


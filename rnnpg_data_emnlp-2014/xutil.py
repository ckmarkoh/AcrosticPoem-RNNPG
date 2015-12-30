#!/usr/bin/python2.7
#-*-coding:UTF-8-*-

import re

def matches(reg, s):
    m = re.match(reg, s)
    if m == None or m.group() !=s:
        return None
    return m

'''
punctuations not included
'''
def isHanzi(s):
    return matches(u'[\u4e00-\u9fa5]+', s) != None


def uwrite(fout, text, encode = 'utf-8'):
    fout.write(text.encode(encode))
    
#-*- encoding:utf-8 -*-
from sys import argv
from jianfan import jtof, ftoj

f = open(argv[1])
s = (("".join([w.strip() for w in f.readlines()])).decode('utf-8')).split(" ")

f2 = open(argv[2])
lines = f2.readlines()

print "result:"
i = 0
for line in lines:
  if line[0] != " " and line[0] != "<":
    line2 = line.strip() 
    if len(line2) > 1:
      result = s[i]+jtof(line2.decode('utf-8')[1:].strip())
      print result.replace(" ","")
      i+=1

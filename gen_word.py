#-*- coding:utf-8
import sys
from jianfan import jtof, ftoj

f = open(sys.argv[1])
s = ftoj(("".join(f.readlines())).decode('utf-8'))
s2 = s.split(" ")
f.close()
f2 = open(sys.argv[2],"w")
f2.write(("%s\t%s"%(s2[0],int(sys.argv[4]))).encode('utf-8'))
f2.close()
f3 = open(sys.argv[3],"w")
f3.write( ("%s|||%s|||%s"%(s2[1],s2[2],s2[3])).encode('utf-8') )
f3.close()



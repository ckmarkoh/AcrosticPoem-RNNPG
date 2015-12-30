#!/usr/bin/python2.7
# -*- coding:utf-8 -*-

import os, sys, re, argparse
from xutil import *

ENCODE = 'utf-8'
puncts = u"。.？?！!，,、；;：:（）《》<>()"

def rawpoem2stdF(infile, outfile):
    fin = open(infile)
    fout = open(outfile, 'w')
    fields = fin.readline().decode(ENCODE).strip().split('\t')
    bodyIdx = fields.index('body')
    reg = '|'.join(puncts).replace("?", "\\?").replace(".", "\\.").replace("(", "\\(").replace(")", "\\)")
    for line in fin:
        fields = line.decode(ENCODE).strip().split('\t')
        body = fields[bodyIdx]
        sens = re.split(reg, body)
        newsens = [' '.join(sen) for sen in sens if len(sen) != 0]
        newline = '\t'.join(newsens) + '\n'
        if len(newline.strip()) > 0:
            uwrite(fout, newline)
    
    fout.close()

def rawpoem2std(indir, outdir):
    if os.path.isdir(indir):
        for f in os.listdir(indir):
            inname = os.path.join(indir, f)
            outname = os.path.join(outdir, f)
            rawpoem2stdF(inname, outname)
            
            print 'rawpoem to std poem %s done!' % inname
    else:
        rawpoem2stdF(indir, outdir)

def countSenNumCharNumF(infile):
    char_num = 0
    sen_num = 0
    for line in open(infile):
        fields = line.decode(ENCODE).strip().split('\t')
        if len(fields) == 0: continue
        sen_num += len(fields)
        for field in fields:
            char_num += len(field.strip().split())
    
    return (char_num, sen_num)

def countSenNumCharNum(infile):
    if os.path.isfile(infile):
        return countSenNumCharNumF(infile)
    else:
        char_num, sen_num = 0, 0
        for f in os.listdir(infile):
            fname = os.path.join(infile, f)
            (cnum, snum) = countSenNumCharNumF(fname)
            char_num += cnum
            sen_num += snum
        
        return (char_num, sen_num)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='a lot of functions for the poem corpus')
    parser.add_argument('--raw2std', help = 'convert raw poem data to std format: 1 2 3 4 5 \\t 1 2 3 4 5 ...', action = 'store_true')
    parser.add_argument('--count', help = 'count the number of sentences and characters in a file or folder', action = 'store_true')
    parser.add_argument('input')
    parser.add_argument('-o', '--output')
    args = parser.parse_args();
    
    if args.raw2std:
        print 'rawpoems to standard poems'
        rawpoem2std(args.input, args.output)
    elif args.count:
        print 'count the number of sentences and characters in a file or folder'
        print 'number of characters are %d, number of sentences are %d' % countSenNumCharNum(args.input)


#!/bin/bash

keywordsF=keywords.txt

python gen_word.py  $keywordsF ./first-sentence-generator/$keywordsF.tmp ./rnnpg-generator/acrostic.txt 7

#cp $keywordsF.tmp ./first-sentence-generator
#cp acrostic.txt ./rnnpg-generator

cd ./first-sentence-generator

./first-sent $keywordsF.tmp 300 300 $keywordsF.firstSent.txt ../MISC/poem.all.model.hidden200.class100.txt ../MISC/kenlm.poem.20140306.bin ../MISC/Shixuehanying.txt.cpp ../MISC/psy_table_cpp

cd ../

cp ./first-sentence-generator/$keywordsF.firstSent.txt ./rnnpg-generator/$keywordsF.firstSent.txt

cd ./rnnpg-generator

./rnnpg-generator poem_generator.conf $keywordsF.firstSent.txt $keywordsF.out.txt

cd ../

python get_word.py $keywordsF ./rnnpg-generator/$keywordsF.out.txt

#!/bin/sh

# echo "=================================="
echo "convert to standard poem"
mkdir std_poem_all
./PoemCorpus.py --raw2std raw_poem_all -o std_poem_all
echo "convert to standard poem done!"

echo "==Number of Poems=="
echo "--total number of poems--"
wc -l std_poem_all/* | tail -1

echo "--number of poems for QTRAIN--"
wc -l partitions_in_Table_2/rnnpg/qtrain

echo "--number of poems for QVALID--"
wc -l partitions_in_Table_2/rnnpg/qvalid


echo "--number of poems for QTEST--"
wc -l partitions_in_Table_2/rnnpg/qtest
echo
echo


echo "==Number of Lines and Characters=="
echo "--QTRAIN--"
./PoemCorpus.py --count partitions_in_Table_2/rnnpg/qtrain
echo "--QVALID--"
./PoemCorpus.py --count partitions_in_Table_2/rnnpg/qvalid
echo "--QTEST--"
./PoemCorpus.py --count partitions_in_Table_2/rnnpg/qtest
echo "--POEMLM--"
./PoemCorpus.py --count partitions_in_Table_2/poemlm/
# echo "=================================="

/*
 * SubsequentSentenceGenerator.h
 *
 *  Created on: 19 Mar 2014
 *      Author: s1270921
 */

#ifndef SUBSEQUENTSENTENCEGENERATOR_H_
#define SUBSEQUENTSENTENCEGENERATOR_H_

#include "xutil.h"
#include <iostream>
#include <fstream>
#include <set>
#include <stdlib.h>
using namespace std;
#include "XConfig.h"
#include "Decoder.h"

#include "Constraints.h"

/*
topK = 20
model = 
transTable = 
stackSize = 300
channelOption = 1 
weightFile = 
ngramLM = 
ngramFeatOn = 1
pingshuiyunDir =
*/

class SubsequentSentenceGenerator
{
public:
	SubsequentSentenceGenerator()
	{
		init();
	}
	~SubsequentSentenceGenerator()
	{
		int i;
		if(rnnpg) delete rnnpg;
		// if(transTable) delete transTable;
		for(i = 0; i < DECODER_NUMBER; i ++)
			delete transTables[i];
		delete []transTables;
		if(model) delete model;
		if(kenlm) delete kenlm;
		// if(decoder) delete decoder;
		for(i = 0; i < DECODER_NUMBER; i ++)
			delete decoders[i];
		delete []decoders;
	}
	void init();
	void initDecoder();
	void generatePoems(const char *firstSentFile, const char *outFile);

  vector<string> loadAcrosticWord(const char* acrosticFile);//TODO Add

private:
	int topK;		// topK sentences should be printed in the output file
	int stackSize;
	Decoder **decoders;
	enum {DECODER_NUMBER = 3};
	RNNPG *rnnpg;
	KenLMM *kenlm;
	TranslationTable **transTables;
	Model *model;
	string weightFilePaths[3][2];		// i, j... i for 12, 23, 34; j for 5 and 7 character sentence

	Constraints constraints;

	bool generatePoem(string firstSent, int tpIndex, vector<vector<string> > &allTopSents, vector<string> &poem);
	/*
	bool badRepeat(const string &trans, const string &word)
	{

		vector<string> twords, words;
		split(trans, " ", twords);
		split(word, " ", words);
		int begin = twords.size();
		twords.reserve(twords.size() + words.size());
		twords.insert(twords.end(), words.begin(), words.end());

		for(int i = begin; i < (int)twords.size(); i ++)
		{
			int cnt = 0;
			for(int j = 0; j < i; j ++)
				if(twords[j] == twords[i])
					cnt ++;
			if(cnt > 1)
				return true;
			if(cnt == 1 && twords[i] != twords[i-1])
				return true;
		}

		return false;
	}

	bool containUsedWords(set<string> &prevWords, const string &second)
	{
		vector<string> words;
		split(second, " ", words);
		for(int i = 0; i < (int)words.size(); i ++)
			if(prevWords.find(words[i]) != prevWords.end())
				return true;

		return false;
	}

	void collectUsedWords(vector<string>& prevSents, map<string,int> &usedWords)
	{
		usedWords.clear();
		size_t i, j;
		for(i = 0; i < prevSents.size(); i ++)
		{
			vector<string> words;
			split(prevSents[i], " ", words);
			for(j = 0; j < words.size(); j ++)
			{
				map<string,int>::iterator iter = usedWords.find(words[j]);
				if(iter == usedWords.end())
					usedWords[words[j]] = 1;
				else
					iter->second ++;
			}
		}
	}

	bool isOkSent(vector<string>& prevSents, string sent)
	{
		vector<string> words;
		split(sent, " ", words);
		size_t i;
		string trans = "";
		for(i = 0; i < words.size(); i ++)
		{
			if(badRepeat(trans, words[i]))
				return false;
			if(i != 0)
				trans += " ";
			trans += words[i];
		}

		map<string,int> usedWords;
		collectUsedWords(prevSents, usedWords);

		for(i = 0; i < words.size(); i ++)
		{
			int freq1Cnt = 0;
			map<string,int>::iterator iter = usedWords.find(words[i]);
			if(iter != usedWords.end())
			{
				if(iter->second > 1)
					return false;
				else if(iter->second == 1)
					freq1Cnt ++;
			}
			if(freq1Cnt > 1)
				return false;
		}

		return true;
	}
	*/
//	bool badRepeat(const string &trans, const string &word)
//	{
//
//		vector<string> twords, words;
//		split(trans, " ", twords);
//		split(word, " ", words);
//		int begin = twords.size();
//		twords.reserve(twords.size() + words.size());
//		twords.insert(twords.end(), words.begin(), words.end());
//
//		for(int i = begin; i < (int)twords.size(); i ++)
//		{
//			int cnt = 0;
//			for(int j = 0; j < i; j ++)
//				if(twords[j] == twords[i])
//					cnt ++;
//			if(cnt > 1)
//				return true;
//			if(cnt == 1 && twords[i] != twords[i-1])
//				return true;
//		}
//
//		return false;
//	}
//
//	bool containUsedWords(set<string> &prevWords, const string &second)
//	{
//		vector<string> words;
//		split(second, " ", words);
//		for(int i = 0; i < (int)words.size(); i ++)
//			if(prevWords.find(words[i]) != prevWords.end())
//				return true;
//
//		return false;
//	}
//
//	void collectUsedWords(vector<string>& prevSents, map<string,int> &usedWords)
//	{
//		usedWords.clear();
//		size_t i, j;
//		for(i = 0; i < prevSents.size(); i ++)
//		{
//			vector<string> words;
//			split(prevSents[i], " ", words);
//			for(j = 0; j < words.size(); j ++)
//			{
//				map<string,int>::iterator iter = usedWords.find(words[j]);
//				if(iter == usedWords.end())
//					usedWords[words[j]] = 1;
//				else
//					iter->second ++;
//			}
//		}
//	}
//
//	bool isOkSent(vector<string>& prevSents, string sent)
//	{
//		vector<string> words;
//		split(sent, " ", words);
//		size_t i;
//		string trans = "";
//		for(i = 0; i < words.size(); i ++)
//		{
//			if(badRepeat(trans, words[i]))
//				return false;
//			if(i != 0)
//				trans += " ";
//			trans += words[i];
//		}
//
//		map<string,int> usedWords;
//		collectUsedWords(prevSents, usedWords);
//
//		for(i = 0; i < words.size(); i ++)
//		{
//			int freq1Cnt = 0;
//			map<string,int>::iterator iter = usedWords.find(words[i]);
//			if(iter != usedWords.end())
//			{
//				if(iter->second > 1)
//					return false;
//				else if(iter->second == 1)
//					freq1Cnt ++;
//			}
//			if(freq1Cnt > 1)
//				return false;
//		}
//
//		return true;
//	}
//
//	bool isOkSent2(vector<string>& prevSents, string sent)
//	{
//		vector<string> words;
//		split(sent, " ", words);
//		size_t i;
//		string trans = "";
//		for(i = 0; i < words.size(); i ++)
//		{
//			if(badRepeat(trans, words[i]))
//				return false;
//			if(i != 0)
//				trans += " ";
//			trans += words[i];
//		}
//
//		map<string,int> usedWords;
//		collectUsedWords(prevSents, usedWords);
//
//		int freq2Cnt = 0;
//		map<string,int>::iterator iter;
//		for(iter = usedWords.begin(); iter != usedWords.end(); ++ iter)
//			if(iter->second == 2)
//				freq2Cnt ++;
//
//		for(i = 0; i < words.size(); i ++)
//		{
//			iter = usedWords.find(words[i]);
//			if(iter != usedWords.end())
//				iter->second ++;
//			else
//				usedWords[words[i]] = 1;
//
//			if(iter->second > 2)
//				return false;
//			if(iter->second == 2)
//				freq2Cnt ++;
//		}
//
//		if(freq2Cnt > 1)
//			return false;
//
//		return true;
//	}

};


#endif /* SUBSEQUENTSENTENCEGENERATOR_H_ */

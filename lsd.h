/*
    lsd.h
    12/5/14
    Joseph Young, Robert Vanhoose, Trevor Richardson
	Author: Joseph Young
	
    fsu::LSDSort
	
	Performs an LSD Radix Sort on a vector of strings. Currently supported
	alphabets are Extended ASCII, Uppercase, Lowercase, Decimal, and Binary.

    Copyright 2014
*/
#ifndef _LSD_H
#define _LSD_H

#include <xstring.h>
#include <vector.h>
//#include <vector.cpp>

namespace fsu
{
	class LSDSort
	{
		public:
					LSDSort ();//Defaults to ASCII
					LSDSort	(char aalph, size_t alogR, size_t aR);
			void	Restart (char aalph, size_t alogR, size_t aR);
			void	Sort	(fsu::Vector<fsu::String>& stringList, size_t max, size_t length);
			void	Pad		(fsu::Vector<fsu::String>& stringList, size_t max);
		private:
			size_t logR;
			size_t R;
			size_t baseChar;
			char alph;
	};


	LSDSort::LSDSort() : logR(8), R(256), baseChar(0), alph('A')
	{
	}


	LSDSort::LSDSort(char aalph, size_t alogR, size_t aR) : logR(alogR), R(aR), alph(aalph)
	{
		switch(alph)
		{
			case 'A':
				baseChar = 0;
				break;
			case 'L':
				baseChar = (size_t)'a';
				break;
			case 'U':
				baseChar = (size_t)'A';
				break;
			case 'D':
				baseChar = (size_t)'0';
				break;
			case 'B':
				baseChar = (size_t)'0';
				break;
		}
	}

	void LSDSort::Restart (char aalph, size_t alogR, size_t aR)
	{
		logR = alogR;
		R = aR;
		alph = aalph;
		switch(alph)
		{
			case 'A':
				baseChar = 0;
				break;
			case 'L':
				baseChar = (size_t)'a';
				break;
			case 'U':
				baseChar = (size_t)'A';
				break;
			case 'D':
				baseChar = (size_t)'0';
				break;
			case 'B':
				baseChar = (size_t)'0';
				break;
		}
	}

	void LSDSort::Sort(fsu::Vector<fsu::String>& stringList, size_t max, size_t length)
	{
		fsu::Vector<fsu::String> temp(length);
		fsu::Vector<size_t> counts;
		size_t i;

		for(i = max - 1; i < max; --i)
		{
			counts.Clear();
			counts.SetSize(R+1, 0);
			for(size_t a= 0; a < length; ++a)
				++counts[(size_t)stringList[a][i] - baseChar + 1];
			for(size_t b =0; b < R; ++b)
				counts[b+1] += counts[b];
			for(size_t c = 0; c < length; ++c)
				temp[counts[(size_t)stringList[c][i] - baseChar]++] = stringList[c];
			for(size_t d = 0; d < length; ++d)
				stringList[d] = temp[d];
		}
	}

	void LSDSort::Pad(fsu::Vector<fsu::String>& stringList, size_t max)
	{
		fsu::String temp;
		for(size_t i = 0; i < stringList.Size(); ++i)
			if(stringList[i].Size() < max)
			{
				temp = stringList[i];
				stringList[i].Clear();
				stringList[i].SetSize(max-temp.Size(),(char)baseChar);
				stringList[i] = stringList[i] + temp;
			}
	}
}
#endif

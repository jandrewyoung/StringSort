/*
    MSD.h
    12/5/14
    Joseph Young, Robert Vanhoose, Trevor Richardson
	Author: Joseph Young
	
    fsu::MSDSort
	
	Performs an MSD Radix Sort on a vector of strings. Currently supported
	alphabets are Extended ASCII, Uppercase, Lowercase, Decimal, and Binary.

    Copyright 2014
*/
#ifndef _MSD_H
#define _MSD_H

#include <xstring.h>
#include <vector.h>
//#include <vector.cpp>

namespace fsu
{
	class MSDSort
	{
		public:
					MSDSort ();//Defaults to ASCII
					MSDSort	(char aalph, size_t alogR, size_t aR);
			void	Restart (char aalph, size_t alogR, size_t aR);
			void	Sort	(fsu::Vector<fsu::String>& stringList);
			void	Pad		(fsu::Vector<fsu::String>& stringList, size_t max);
		private:
			void Sort(fsu::Vector<fsu::String>& stringList, fsu::Vector<fsu::String>& tempList, size_t low, size_t high, size_t counter);
			size_t logR;
			size_t R;
			size_t baseChar;
			char alph;
	};


	MSDSort::MSDSort() : logR(8), R(256), baseChar(0), alph('A')
	{
	}


	MSDSort::MSDSort(char aalph, size_t alogR, size_t aR) : logR(alogR), R(aR), alph(aalph)
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

	void MSDSort::Restart (char aalph, size_t alogR, size_t aR)
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

	void MSDSort::Sort(fsu::Vector<fsu::String>& stringList)
	{
		fsu::Vector<fsu::String> temp(stringList.Size());
		Sort(stringList, temp, 0, stringList.Size() -1, 0);
	}
	
	
	void MSDSort::Sort(fsu::Vector<fsu::String>& stringList, fsu::Vector<fsu::String>& tempList, size_t low, size_t high, size_t counter)
	{
		if((int)high <= (int)low)
			return;

		fsu::Vector<size_t> counts(R+2,0);
std::cout << counter << "." << low << "." << high << "\n";
		for(size_t a= low; a <= high; ++a)
			++counts[(size_t)stringList[a][counter] - baseChar + 2];
std::cout << "a\n";
		for(size_t b =0; b < R+1; ++b)
			counts[b+1] += counts[b];
std::cout << "b\n";
		for(size_t c = low; c <= high; ++c)
			tempList[counts[(size_t)stringList[c][counter] - baseChar+1]++] = stringList[c];
std::cout << "c\n";
		for(size_t d = low; d <= high; ++d)
			stringList[d] = tempList[d-low];
std::cout << "test\n";
		for(size_t i = 0; i < R; ++i)
			Sort(stringList, tempList, low + counts[i], low + counts[i+1]-1, counter+1);
	}
}
#endif

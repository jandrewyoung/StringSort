/*
  qs3w.h
  Author: Trevor Richardson

  Sorts string vectors using 3-way quicksort algorithm
  Suited for memory restrictions (in-place) and strings with shared prefixes
*/

#ifndef _QS3_H
#define _QS3_H

#include <xstring.h>
#include <vector.h>

namespace fsu
{
	class QS3Sort
	{
		public:
      QS3Sort() : logR(8), R(256), alph('A')	{} //Defaults to ASCII
			QS3Sort	(char aalph, size_t alogR, size_t aR) : logR(alogR), R(aR), alph(aalph) {}

      int GetChar(fsu::Vector<fsu::String>& stringList, size_t i, size_t d);
      void Swap(fsu::Vector<fsu::String>& stringList, size_t x, size_t y);
      void	Restart(char aalph, size_t alogR, size_t aR);
      void	Sort(fsu::Vector<fsu::String>& stringList, int lo, int hi, size_t d = 0);
		private:
			size_t logR;
			size_t R;
			char alph;
	};

  int QS3Sort::GetChar(fsu::Vector<fsu::String>& stringList, size_t i, size_t d)
  {
    if (d == stringList[i].Size())
      return -1;
    return (size_t)stringList[i][d];
  }

  void QS3Sort::Swap(fsu::Vector<fsu::String>& stringList, size_t x, size_t y)
  {
    fsu::String temp = stringList[x];
    stringList[x] = stringList[y];
    stringList[y] = temp;
  }

  void QS3Sort::Sort(fsu::Vector<fsu::String>& stringList, int lo, int hi, size_t d)
  {
    if (hi <= lo) return;
    int lt = lo, gt = hi;
    int v = GetChar(stringList, lo, d);
    int i = lo + 1;
    while (i <= gt)
    {
      int t = GetChar(stringList, i, d);
      if (t < v) Swap(stringList, lt++, i++);
      else if (t > v) Swap(stringList, i, gt--);
      else i++;
    }
    Sort(stringList, lo, lt - 1, d);
    if (v >= 0) Sort(stringList, lt, gt, d + 1);
    Sort(stringList, gt + 1, hi, d);
  }

  void  QS3Sort::Restart(char aalph, size_t alogR, size_t aR)
  {
    logR = alogR;
    R = aR;
    alph = aalph;
  }
}

#endif
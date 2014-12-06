

#ifndef _MSD_H
#define _MSD_H

#include <xstring.h>
#include <vector.h>

namespace fsu
{
	class MSDSort
	{
		public:
					MSDSort () logR(8), R(256), alph('A')	//Defaults to ASCII
					MSDSort	(char aalph, size_t alogR, size_t aR) : logR(alogR), R(aR), alph(aalph) {}
			void	Restart (char aalph, size_t alogR, size_t aR) : logR(alogR), R(aR), alph(aalph) {}
			void	Sort	(fsu::Vector<fsu::String>& stringList, size_t max, size_t length);			
		private:
			size_t logR;
			size_t R;
			char alph;
	};

	void MSDSort::Sort		(fsu::Vector<fsu::String>& stringList, int max, size_t length)
	{
	
	}
}
#endif
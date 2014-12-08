/**
 * msd.h - Class MSDSort
 *
 * Implements most-significant-digit-first string sort. Influenced by Robert
 * Sedgewick's design. See readme.txt for more.
 *
 * Project 6
 * COP 4531 - Fall 2014
 * Team 11:
 *   Andrew Young jay10@my.fsu.edu
 *   Rob van Hoose hrv04@my.fsu.edu
 *   Trevor Richardson
 *
 */

#ifndef _MSD_H
#define _MSD_H

#include <xstring.h>
#include <vector.h>

const size_t INS_CUTOFF = 10;

namespace fsu
{
   class MSDSort
   {
      public:
               MSDSort  () : logR(8), R(256), alph('A'){};	//Defaults to ASCII
               MSDSort  (char aalph, size_t alogR, size_t aR);
         void  Restart  (char aalph, size_t alogR, size_t aR);
         void  Sort     (fsu::Vector<fsu::String>& stringList, size_t max, size_t length);
      private:

         size_t logR;
         size_t R;
         size_t baseChar;
         char alph;
         void Sort ( fsu::Vector<fsu::String>& stringList,
                     fsu::Vector<fsu::String>& tempList,
                     size_t start,
                     size_t finish,
                     size_t letterOffset
                   );
         void InsertionSort ( fsu::Vector<fsu::String>& stringList,
                              size_t start,
                              size_t finish
                            );
   };


   /**
    * MSDSort constructor
    * sets baseChar (offset) depending on the alphabet chosen
    */
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
      R    = aR;
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


   /**
    * Sort()
    * Conducts a most significant digit first string sort
    */
   void MSDSort::Sort (fsu::Vector<fsu::String>& stringList, size_t max, size_t length)
   {

      fsu::Vector<fsu::String> tempList( length );

      // start the sort, on all elements of stringList, starting at the first letter
      Sort( stringList, tempList, 0, length - 1, 0 );


   } // end Sort()

   void MSDSort::Sort (
      fsu::Vector<fsu::String>& stringList,
      fsu::Vector<fsu::String>& tempList,
      size_t start,
      size_t finish,
      size_t letterOffset
   )
   {
      if ( finish - start <= 10 )
      {
         //std::cout << "running insertion sort" << std::endl;
         this->InsertionSort( stringList, start, finish );
         return;
      }
//       std::cout << "start: " << start << " finish: " << finish << std::endl;
//       exit(0);

      // count how many times each letter occurs at this offset
      fsu::Vector<size_t> counts( R + 2, 0 );
      for ( size_t i = start; i <= finish; ++i )
         ++counts[ (size_t)stringList[ i ][ letterOffset ] ];

      // Transform counts to indices
      for( size_t r = 0; r < R + 1; ++r )
			counts[ r + 1 ] += counts[r];

      // distribute
      for( size_t i = start; i <= finish; ++i )
         tempList[ counts[ (size_t)stringList[ i ][ letterOffset ] - baseChar + 1 ]++ ]
            = stringList[ i ];

      // copy back
      for( size_t i = start; i <= finish; ++i )
         stringList[ i ] = tempList[ i - start ];

      // Recursion...
      for( size_t r = 0; r < R; ++r )
         this->Sort( stringList,
               tempList,
               start + counts[ r ],
               start + counts[ r + 1 ] - 1,
               letterOffset+1
      );

   } // end Sort( originalList, tempList )



   void MSDSort::InsertionSort ( fsu::Vector<fsu::String>& stringList,
                           size_t start,
                           size_t finish
   )
   {
      for ( int i = start; i <= finish; ++i )
         for ( int j = i; j > start; --j )
         {
            if ( stringList[ j ] < stringList[ j - 1 ] )
            {
               fsu::String tempString = stringList[ j - 1 ];
               stringList[ j - 1 ] = stringList[ j ];
               stringList[ j ] = tempString;
            }
         }

   }

} // end namespace fsu

#endif

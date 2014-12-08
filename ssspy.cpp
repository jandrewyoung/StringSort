/**
 * ssspy.cpp - String sort spy -- string sort test harness
 *
 * Written by Andrew Young, w/ revisions by Rob van Hoose
 *
 * COP 4531 - Fall 2014
 * Team 11:
 *   Andrew Young jay10@my.fsu.edu
 *   Rob van Hoose hrv04@my.fsu.edu
 *   Trevor Richardson
 *
 */

#include <iostream>
#include <xstring.h>
#include <xstring.cpp>
#include <vector.h>
#include <lsd.h>
#include <timer.cpp>
#include <fstream>
#include <msd.h>
//#include <qs3w.h>


// EXTENDED_ASCII
//typedef uint8_t Ascii;
const size_t AlogR = 8;
const size_t AR = 256;

// UPPERCASE
//typedef enum {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z} Upper;
const size_t UlogR = 5;
const size_t UR = 26;

// LOWERCASE
//typedef enum {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z} Lower;
const size_t LlogR = 5;
const size_t LR = 26;

// DECIMAL
//typedef enum {0,1,2,3,4,5,6,7,8,9} Dec;
const size_t DlogR = 4;
const size_t DR = 10;

// BINARY
//typedef enum {0,1} Bin;
const size_t BlogR = 1;
const size_t BR = 2;


int main(int argc, char* argv[])
{
  if (!(argc == 1 || argc == 3))  // program name is argv[0]
  {
    std::cout << " ** command line arguments:\n";
	std::cout << "     1: input filename (required)\n";
	std::cout << "     2: output filename (required)\n";
	std::cout << "Or No arguments for manual entry\n";
	std::cout << " ** try again\n";
    return 0;
  }


	char c = 'z';
	char* infile = argv[1];
	char* outfile = argv[2];
	int num = 0;
	size_t max = 0;
	fsu::String in;
	fsu::Vector<fsu::String> stringList;
	fsu::LSDSort lsd;
	fsu::MSDSort msd;
//	fsu::QS3Sort qs3;
	fsu::Instant instant;
	fsu::Timer timer;
	std::ifstream inStream;
	std::ofstream outStream;

	while(1)
	{
      while(c != 'U' && c != 'u' && c != 'A' && c != 'a' && c != 'l' && c != 'l'
            && c != 'D' && c != 'd' && c != 'B' && c != 'b' && c != 'Q' && c != 'q')
      {
      if(num != 0)
         std::cout << "Character not recognized\n";
      std::cout << "Alphabet Choices:\n";
      std::cout << "  ASCII (A)\n";
      std::cout << "  Uppercase (U)\n";
      std::cout << "  Lowercase (L)\n";
      std::cout << "  Decimal (D)\n";
      std::cout << "  Binary (B)\n";
      std::cout << "  Quit (Q)\n";
      std::cout << "Please enter your choice: ";
      std::cin >> c;
      num++;
      }
      num = 0;

      if(c == 'q' || c == 'Q')
      {
         std::cout << "Exiting...\n";
         return 0;
      }

      if(argc == 3)
      {
         inStream.open(infile);
         if(inStream.fail())
         {
            std::cout << "File could not be opened for read\nExiting...";
            return 0;
         }
         while(inStream)
         {
            in.GetLine(inStream);
            stringList.PushBack(in);
            if(in.Length() > max)
               max = in.Length();
         }
      }
      else
      {
         std::cout << "Please enter the number of strings to be sorted: ";
         std::cin >> num;
         for(int i = 1; i < num+1; i++)
         {
            std::cout << "Enter string " << i <<": ";
            std::cin >> in;
            stringList.PushBack(in);
            if(in.Length() > max)
               max = in.Length();
         }
      }

      switch(c)
      {
         case 'A':
         case 'a':
            lsd.Restart('A', 8, 256);
            msd.Restart('A', 8, 256);
   //			qs3.Restart('A', 8, 256);
            break;
         case 'U':
         case 'u':
            lsd.Restart('U', 5, 26);
            msd.Restart('U', 5, 26);
   //			qs3.Restart('U', 5, 26)	;
            break;
         case 'L':
         case 'l':
            lsd.Restart('L', 5, 26);
            msd.Restart('L', 5, 26);
   //			qs3.Restart('L', 5, 26);
            break;
         case 'D':
         case 'd':
            lsd.Restart('D', 4, 10);
            msd.Restart('D', 4, 10);
   //			qs3.Restart('D', 4, 10);
            break;
         case 'B':
         case 'b':
            lsd.Restart('B', 1, 2);
            msd.Restart('B', 1, 2);
   //			qs3.Restart('B', 1, 2);
            break;
      }
      fsu::Vector<fsu::String> lsdList(stringList);
      lsd.Pad(lsdList, max);
      fsu::Vector<fsu::String> msdList(stringList);
   //	fsu::Vector<fsu::String> qs3List(stringList);

      msd.Sort(msdList, max, msdList.Size());
   //	qs3.Sort(qs3List, max, qs3List.Size());

      timer.SplitReset();
      lsd.Sort(lsdList, max, lsdList.Size());
      instant = timer.SplitTime();
      std::cout << "\nLSD Sorted in " << instant.Get_useconds() << " useconds\n";

      if(argc == 3)
      {
         outStream.open(outfile);
         if(outStream.fail())
         {
            std::cout << "File could not be opened for write\nExiting...";
            return 0;
         }
         outStream <<"LSD Sorted in "<< instant.Get_useconds() << " useconds\n";
         outStream <<"LSD Sorted list: \n";
      }
      for(size_t i = 0; i < lsdList.Size(); i++)
      {
         if(argc == 3)
            outStream <<"   " << lsdList[i] << "\n";
         else
            std::cout << "   " << lsdList[i] << "\n";
      }
      std::cout << "MSD Sorted:\n";
      for(size_t i = 0; i < msdList.Size(); i++)
         std::cout << "   " << msdList[i] << "\n";
   //	std::cout << "QS3W Sorted:\n";
   //	for(size_t i = 0; i < qs3List.Size(); i++)
   //		std::cout << "   " << qs3[i] << "\n";

      c = 'z';
      num = 0;
      stringList.Clear();
      if(argc == 3)
      {
         std::cout << "\nExiting...\n";
         return 0;
      }
   }
}


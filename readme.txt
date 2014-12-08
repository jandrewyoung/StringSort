String Sorts
Team: Joseph Young, Robert Vanhoose, Trevor Richardson

Files:
ssspy.cpp - Joseph Young
lsd.h - Joseph Young
msd.h - Robert Vanhoose
qs3w.h - Trevor Richardson

LSD Development Notes:
I implemented the Pad function to allow strings of different sizes to be sorted by padding
the left side of the string with the smallest character in the alphabet being used. Basechar
is used to keep the index of the character corresponding to 0 through R-1 as opposed to its
actual ASCII value.

MSD development notes:
As soon as I read about MSD and the way it creates bucket lists, I thought there must ways
to optimize it. I would have preferred to factor out the regression but that did not seem
practical in this case. Instead, I focused on applying Robert Sedgewick's optimization
to recurse over the same vector.

QS3 Development Notes:
I borrowed my optimized 3-way quicksort from one of the previous projects and re-factored
it to work with string vectors. Since it functions using a simple comparison that 
converts characters from ASCII to integers, very little tweaking had to be done to 
account for different alphabets. A GetChar() method was added to avoid boundary issues
resulting from reaching the end of the vector or trying to read a character from a string
past its length, alongside a simple swap method for swapping string vector elements. One
issue that put a spoke in the wheels was that the string vector from sortspy had an end
iterator past the actual end. This was dealt with by popping all null elements off the 
end of vector before sorting it.

SSSPY Use:
Strings can be entered manually through the menu by running the program with no arguments. The
user will then give which alphabet they want to use - ASCII, uppercase, lowercase, decimal, or
binary - then the number of strings and then each string. The program will then sort and output
the sorted strings and the time it took to sort them to the command line.
Strings can also be read from a file and output to a file by running with two arguments, i.e.
ssspy.x input.file output.file. If this is done, the user will still have to give the alphabet
that is being used, and the file should have one string per line.
A stringCheck method was added to check that the strings were in the specified alphabet and return
an error if not.


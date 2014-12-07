String Sorts
Team: Joseph Young, Robert Vanhoose, Trevor Richardson

Files:
ssspy.cpp - Joseph Young
lsd.h - Joseph Young
msd.h - Robert Vanhoose
qs3w.h - Trevor Richardson

LSD Development Notes:
I implemented the Pad function to allow strings of different sizes to be sorted by padding
the left side of the string with the smallest character in the alphabet being used.

MSD development notes:
As soon as I read about MSD and the way it creates bucket lists, I thought there must ways
to optimize it. I would have preferred to factor out the regression but that did not seem
practical in this case. Instead, I focused on applying Robert Sedgewick's optimization
to recurse over the same vector.

SSSPY Use:
Strings can be entered manually through the menu by running the program with no arguments. The
user will then give which alphabet they want to use - ASCII, uppercase, lowercase, decimal, or
binary - then the number of strings and then each string. The program will then sort and output
the sorted strings and the time it took to sort them to the command line.
Strings can also be read from a file and output to a file by running with two arguments, i.e.
ssspy.x input.file output.file. If this is done, the user will still have to give the alphabet
that is being used, and the file should have one string per line.


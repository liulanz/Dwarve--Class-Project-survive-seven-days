# Dwarve-Class-Project-survive-seven-days

In this project, I only modified bot.cpp file.

When you run the program, it does not stop at 21:00 at the end of the first day. Instead, it will run for 7 days.
Each day consists of two parts:  Daytime from 6:00 to 21:00, and Nighttime from 21:00 to 6:00 of the next day. 
At nighttime, zombies come. There are two types of them: ZOMBIE and PUMPKIN_ZOMBIE. You cannot attack them, 
but they cannot go through fences, so it can be a good idea to build a shelter. In the morning, all zombies quickly die,
and pumpkin zombies leave pumpkins that can be picked up.

To compile the program, go to that directory, and while inside of it, type:

make

Building this software requires development files for “ncurses” library. They are already installed on the Linux Lab computers. 
To setup your own computer: On Ubuntu, this is package libncurses5-dev. On Cygwin, this is libncurses-devel.
On Mac OS, this is ncurses package (brew install ncurses).
After building the software, you get an executable file dwarves. To run it with the default parameters, type:

./dwarves

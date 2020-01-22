# Dwarve-Class-Project-survive-seven-days

In this class project, the only file that is told to modified is the bot.cpp file. Out of 128 submissions, I got a THIRD place on the leaderboard on gradescope.

The task was to modified only the bot.cpp file to improve the code controlling actions of the dwarves.
The map has a dimensions between 25 and 35, the number of dwarves can be 6, 7, or 8. There will be daytime, nighttime,
trees, and zombies. Zombies will attack my dwarves, I wrote my code by allowing my dwarves to build fences around them 
during nighttime to protect them. Dwarves need to pick up apples pumpkins. Since I need to maximize the number of apples, 
I wrote my code in a way that my dwarves will go to the nearest apple tree at night, and they will build fence then start 
picking up apples until daytime. 

The goal is to have following requirements at the end of the 7th day in the game:
  - All dwarves must survive
  - Must build a contiguous fence structure of size 30 or more
  - Must collect at least 30 pumpkins
  - Must collect at least 1000 apples



To compile the program, go to that directory, and while inside of it, type:

make

Running the program deterministically with the same random seed
For that, run the program as follows:

./dwarves c ROWS COLS NUM SEED

Where replace ROWS, COLS, NUM, and SEED with the number of rows (25-35), number of columns (25-35), number of dwarves (6-8), and the SEED can be any non-negative integer number. For example:

./dwarves c 27 31 8 55555 

will run the game on the map 27×31, with 8 dwarves, and using the random seed 55555.


  


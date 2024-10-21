# MY_BSQ

MY_BSQ is an algorithm-focused project that finds and prints the largest square on a given board while avoiding obstacles. The board is represented by a file passed as the program’s argument. This project is optimized for speed, memory efficiency, or both—challenging you to push algorithmic performance to the limit.

## Overview

### The task is to find the largest square on a 2D board made up of:

	•	. - representing empty spaces.
	•	o - representing obstacles.

### The goal is to maximize the size of the square while avoiding obstacles and print the result, marking the largest found square with x. The challenge lies in creating an efficient algorithm that balances performance (speed) and memory usage.

## Features

	•	🟢 Efficient algorithm for finding the largest possible square.
	•	🚀 Optimized for performance: supports fast execution on large boards.
	•	📉 Low memory usage: scalable for memory-limited systems.
	•	📂 Simple input: board provided via an input file as the program argument.
	•	🔄 Clear output: prints the board with the largest square marked by x.

## Installation

	1.	Clone the repository:

```bash
git clone https://github.com/kendrajmoore/my_bsq.git
cd my_bsq

```


	2.	Compile the project:
If you’re using gcc:
```bash
gcc -o my_bsq my_bsq.c
```

### Usage

./my_bsq <input_file>

	•	Input: A file containing the board representation.
	•	Output: The board printed with the largest square marked by x.

Input Constraints

	•	First line: Number of lines on the board.
	•	Characters:
	•	. (empty space)
	•	o (obstacle)
	•	All lines must have the same length (except the first).
	•	Each line ends with \n.
	•	There will always be at least one line in the input.

Example

Input (board.txt):

5
.....
.o.o.
.....
.o.o.
.....

Command:

./my_bsq board.txt

Output:

xxxxx
xoxo.
xxxxx
.o.o.
.....

How it Works

	•	The program scans the board to find the largest square of empty spaces.
	•	It avoids obstacles (o) by skipping blocked areas.
	•	The largest square is printed with x marking the filled space.

Performance Tips

	•	Optimize for Speed: Use dynamic programming or memoization techniques to avoid redundant calculations.
	•	Minimize Memory Usage: Use in-place modifications or efficient data structures to reduce memory footprint.

### Contributing

Contributions are welcome! If you’d like to improve the algorithm or add features:

	1.	Fork the repository.
	2.	Create a new branch:

git checkout -b feature-name


	3.	Commit your changes:

git commit -m "Add feature or fix bug"


	4.	Push to your branch:

git push origin feature-name


	5.	Create a pull request.


Acknowledgments

	•	Inspired by classic algorithm challenges and board-solving puzzles.
	•	Special thanks to all contributors and testers!

This README provides a clear description, usage instructions, and invites collaboration, making your project accessible and engaging for contributors and users.
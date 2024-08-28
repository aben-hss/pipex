|Pipex|

# Description
Pipex is a program that simulates the functionality of the shell pipe operator (|). It takes four arguments: two filenames and two shell commands. The program reads from the first file, executes the first command, pipes the output to the second command, and then writes the final output to the second file.
# Features

Simulates the behavior of the shell command: < file1 cmd1 | cmd2 > file2
Handles input and output file redirection
Executes shell commands with arguments
Utilizes environment variables to locate command executables

# Installation

Clone the repository:
git clone https://github.com/aben-hss/pipex

Navigate to the project directory:
cd pipex

Compile the project:
make


# Usage
Run the program with four arguments:
./pipex file1 cmd1 cmd2 file2

file1: Input file
cmd1: First command to execute
cmd2: Second command to execute
file2: Output file

# Example:
./pipex infile "ls -l" "wc -l" outfile

# Project Structure
pipex.c: Main program logic
pipex_utils.c: Utility functions for file operations and command path resolution
pipex.h: Header file with function prototypes and necessary includes
libft/: Custom C library with various utility functions

# Cleaning Up
To remove object files:
make clean

To remove object files and the executable:
make fclean

To recompile the project:
make re

# Author
This push_swap project was developed by aben-hss as part of the 42 school curriculum.

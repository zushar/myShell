#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <pwd.h>
#include <dirent.h>
#include <errno.h>
#define SIZE_BUFF 4096
#define SIZE_HOSTNAME 256
/**
 * Reads a line of input from the user.
 * 
 * This function reads characters from the standard input (stdin) until a newline
 * character ('\n') is encountered. It dynamically allocates memory for a string
 * to store the input. The caller is responsible for freeing the memory allocated
 * for the string when it's no longer needed.
 * 
 * @return A dynamically allocated string (char*) containing the user input.
 *         The string is null-terminated. Returns NULL if no input is given or
 *         if memory allocation fails.
 * 
 * @note The function will crash with a segmentation fault if no input is given
 *       and the enter key is pressed. This is a known bug.
 * 
 * @warning The caller is responsible for freeing the memory allocated for
 *          the returned string using free().
 */
char* getInputFromUser();

/**
 * Splits a string into individual tokens based on whitespace.
 * 
 * This function takes a string as input and tokenizes it based on whitespace
 * characters (space, tab, newline). It dynamically allocates memory for an
 * array of strings to store the tokens. The caller is responsible for freeing
 * the memory allocated for the array and its elements when it's no longer needed.
 * 
 * @param input A pointer to the string to be split.
 * 
 * @return A dynamically allocated array of strings (char**) containing the tokens.
 *         The last element of the array is NULL. Returns NULL if input is NULL
 *         or if memory allocation fails.
 * 
 * @note The input string will be modified (tokenized) by this function.
 *       Make sure to use a copy of the original string if preservation
 *       of the original string is required.
 * 
 * @warning The caller is responsible for freeing the memory allocated for
 *          the returned array and its elements using free().
 */
char** splitArgument(char*);

/**
 * Prints the current working directory.
 * 
 * This function uses the getcwd() system call to obtain the current working
 * directory and prints it to the standard output (stdout).
 * 
 * @return void
 * 
 * @note If an error occurs while obtaining the current working directory,
 *       the function will print an error message to the standard error (stderr).
 */
void getLocation();

/**
 * Logs out the user from the shell.
 * 
 * This function checks if the input string is "exit". If it is, the function
 * terminates the shell program by calling the exit() system call.
 * 
 * @param input A pointer to the string to be checked.
 * 
 * @return void
 * 
 * @note If the input string is not "exit", the function does nothing.
 */
void logout(char* input);

/**
 * Prints the given arguments to the standard output.
 * 
 * This function takes an array of strings as input where the first element is
 * the "echo" command and the remaining elements are the arguments to be printed.
 * It prints the arguments to the standard output (stdout) separated by spaces.
 * 
 * @param args An array of strings where the first element is the "echo" command
 *             and the remaining elements are the arguments to be printed.
 * 
 * @return void
 * 
 * @note If no arguments are given, the function prints a newline character.
 */
void echo(char** arguments);

/**
 * Appends the given arguments to a file.
 * 
 * This function takes an array of strings as input where the first element is
 * the "echoppend" command, the second element is the filename, and the remaining
 * elements are the arguments to be appended to the file. It opens the file in
 * append mode and writes the arguments to the file separated by spaces.
 * 
 * @param args An array of strings where the first element is the "echoppend" command,
 *             the second element is the filename, and the remaining elements are the
 *             arguments to be appended to the file.
 * 
 * @return void
 * 
 * @note If the file does not exist, it will be created.
 * 
 * @warning If an error occurs while opening or writing to the file, the function
 *          will print an error message to the standard error (stderr).
 */
void echoppend(char **arguments);

/**
 * Writes the given arguments to a file.
 * 
 * This function takes an array of strings as input where the first element is
 * the "echorite" command, the second element is the filename, and the remaining
 * elements are the arguments to be written to the file. It opens the file in
 * write mode and writes the arguments to the file separated by spaces.
 * 
 * @param args An array of strings where the first element is the "echorite" command,
 *             the second element is the filename, and the remaining elements are the
 *             arguments to be written to the file.
 * 
 * @return void
 * 
 * @note If the file exists, its contents will be overwritten.
 * 
 * @warning If an error occurs while opening or writing to the file, the function
 *          will print an error message to the standard error (stderr).
 */
void echorite(char **arguments);

/**
 * Changes the current working directory.
 * 
 * This function takes an array of strings as input where the first element is
 * the "cd" command and the second element is the path to the directory to change to.
 * It uses the chdir() system call to change the current working directory.
 * 
 * @param args An array of strings where the first element is the "cd" command
 *             and the second element is the path to the directory to change to.
 * 
 * @return void
 * 
 * @note If the path is not valid or if an error occurs during the chdir() system call,
 *       the function will print an error message to the standard error (stderr).
 */
void cd(char **);

/**
 * Copies a file.
 * 
 * This function takes an array of strings as input where the first element is
 * the "cp" command, the second element is the source filename, and the third
 * element is the destination filename. It uses the standard C library functions
 * to open the source file in read mode, create the destination file in write mode,
 * and copy the contents of the source file to the destination file.
 * 
 * @param args An array of strings where the first element is the "cp" command,
 *             the second element is the source filename, and the third element
 *             is the destination filename.
 * 
 * @return void
 * 
 * @note If the destination file exists, its contents will be overwritten.
 * 
 * @warning If an error occurs while opening, reading from, or writing to the files,
 *          the function will print an error message to the standard error (stderr).
 */
void cp(char ** arguments);

/**
 * Deletes a file.
 * 
 * This function takes an array of strings as input where the first element is
 * the "delete" command and the second element is the filename of the file to be deleted.
 * It uses the remove() system call to delete the file.
 * 
 * @param args An array of strings where the first element is the "delete" command,
 *             and the second element is the filename of the file to be deleted.
 * 
 * @return void
 * 
 * @note If the file does not exist, the function will print an error message to
 *       the standard error (stderr).
 * 
 * @warning If an error occurs while deleting the file, the function will print
 *          an error message to the standard error (stderr).
 */
void delete(char **path);

/**
 * Lists the contents of the current directory.
 * 
 * This function uses the opendir() and readdir() system calls to open the current
 * directory and read its contents. It prints the names of the files and directories
 * in the current directory to the standard output (stdout).
 * 
 * @return void
 * 
 * @note If an error occurs while opening or reading the directory, the function
 *       will print an error message to the standard error (stderr).
 */
void get_dir();

/**
 * Executes a system call.
 * 
 * This function takes an array of strings as input where the first element is
 * the name of the system call and the remaining elements are the arguments to
 * the system call. It uses the execvp() system call to execute the system call.
 * 
 * @param args An array of strings where the first element is the name of the
 *             system call and the remaining elements are the arguments to the
 *             system call.
 * 
 * @return void
 * 
 * @note If the system call does not exist or if an error occurs during the
 *       execvp() system call, the function will print an error message to
 *       the standard error (stderr).
 */
void SystemCall(char **arguments);

/**
 * Executes a pipe operation between two commands.
 * 
 * This function takes two arrays of strings as input where the first array
 * represents the first command and its arguments, and the second array represents
 * the second command and its arguments. It creates a pipe using the pipe() system
 * call and forks a new process using the fork() system call. In the child process,
 * it redirects the standard output to the write end of the pipe and executes the
 * first command. In the parent process, it redirects the standard input from the
 * read end of the pipe and executes the second command.
 * 
 * @param argv1 An array of strings representing the first command and its arguments.
 * @param argv2 An array of strings representing the second command and its arguments.
 * 
 * @return void
 * 
 * @note If an error occurs during the pipe(), fork(), dup2(), or execvp() system calls,
 *       the function will print an error message to the standard error (stderr).
 */
void mypipe(char **argv1, char **argv2);

/**
 * Moves a file.
 * 
 * This function takes an array of strings as input where the first element is
 * the "move" command, the second element is the source filename, and the third
 * element is the destination filename. It uses the rename() system call to move
 * the file from the source location to the destination location.
 * 
 * @param args An array of strings where the first element is the "move" command,
 *             the second element is the source filename, and the third element
 *             is the destination filename.
 * 
 * @return void
 * 
 * @note If the source file does not exist or if a file with the same name already
 *       exists at the destination location, the function will print an error message
 *       to the standard error (stderr).
 */
void move(char **arguments);

/**
 * Reads a file and prints its contents.
 * 
 * This function takes an array of strings as input where the first element is
 * the "readFile" command and the second element is the filename of the file to be read.
 * It uses the standard C library functions to open the file in read mode and read its
 * contents. It prints the contents of the file to the standard output (stdout).
 * 
 * @param args An array of strings where the first element is the "readFile" command,
 *             and the second element is the filename of the file to be read.
 * 
 * @return void
 * 
 * @note If the file does not exist, the function will print an error message to
 *       the standard error (stderr).
 * 
 * @warning If an error occurs while opening or reading the file, the function will
 *          print an error message to the standard error (stderr).
 */
void readFile(char **arguments);

/**
 * Counts the number of words in a file.
 * 
 * This function takes an array of strings as input where the first element is
 * the "wordCount" command and the second element is the filename of the file to be read.
 * It uses the standard C library functions to open the file in read mode and read its
 * contents. It counts the number of words in the file and prints the count to the
 * standard output (stdout).
 * 
 * @param args An array of strings where the first element is the "wordCount" command,
 *             and the second element is the filename of the file to be read.
 * 
 * @return void
 * 
 * @note A word is defined as a sequence of characters separated by whitespace.
 * 
 * @note If the file does not exist, the function will print an error message to
 *       the standard error (stderr).
 * 
 * @warning If an error occurs while opening or reading the file, the function will
 *          print an error message to the standard error (stderr).
 */
void wordCount(char **arguments);
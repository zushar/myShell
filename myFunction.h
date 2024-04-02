#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
# include <sys/types.h>
#include <sys/wait.h>
# include <pwd.h>
#include <dirent.h>
#include <errno.h>
#define SIZE_BUFF 4096
#define SIZE_HOSTNAME 256
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
void getLocation();


void logout(char* input);
void echo(char** arguments);
void cd(char **);
void cp(char ** arguments);
void delete(char **path);
void get_dir();
void SystemCall(char **arguments);
void mypipe(char **argv1, char **argv2);
void move(char **arguments);
void echoppend(char **arguments);
void echorite(char **arguments);
read(char **arguments);
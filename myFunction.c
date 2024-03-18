#include "myFunction.h"

void getLocation()
{
    char location[SIZE_BUFF];
//get the complete path of the current working directory including the name of the current user
    struct passwd *pw;
    pw = getpwuid(getuid());
    if (pw == NULL) {
        printf("Error getting user name\n");
        return;
    }
    if (getcwd(location, SIZE_BUFF) == NULL){
        printf("Error getting current directory\n");
        return;
    }
    printf("\033[0;34m");
    printf("%s@\033[0;32m%s\033[0m$ ", pw->pw_name, location);
    printf("\033[0m");
}

char *getInputFromUser()
//bug to fix here if no input is given and enter is pressed program crashes with segmentation fault
{
    char ch;  // Variable to hold each character as it's read
    int size = 1;  // Size of the input string (starts at 1 for the null terminator)
    int index = 0;  // Current position in the input string
    char *str = (char *)malloc(size * sizeof(char));  // Allocate initial input string

    // Read characters until a newline is encountered
    while ((ch = getchar()) != '\n')
    {
        // Add the character to the input string
        *(str + index) = ch;

        // Increase the size and index
        size++;
        index++;

        // Reallocate the input string to the new size
        str = (char *)realloc(str, size);
    }
    // Null-terminate the input string
    *(str + index) = '\0';
    return str;  // Return the input string
}

char **splitArgument(char *str)
{
    // Allocate memory for the array of pointers to strings
    char **args = (char **)malloc(SIZE_BUFF * sizeof(char *));
    if (args == NULL)
    {
        printf("Error\n");
        return NULL;
    }
    int i = 0;
    while (*str != '\0')  // While the end of the string has not been reached
    {
        // Skip leading whitespace
        str += strspn(str, " \t");
        // Find the end of the word
        char *end = str + strcspn(str, " \t");
        // Allocate memory for the word and copy it
        args[i] = (char *)malloc(SIZE_BUFF * sizeof(char));
        if (args[i] == NULL)
        {
            printf("Error\n");
            return NULL;
        }
        strncpy(args[i], str, end - str);
        args[i][end - str] = '\0';  // Null-terminate the string
        // Move on to the next word
        str = end;
        i++;
    }
    // If the last argument ends with a newline, replace it with a null character
    if (i > 0 && args[i-1][strlen(args[i-1])-1] == '\n') {
        args[i-1][strlen(args[i-1])-1] = '\0';
    }
    // Null-terminate the array of arguments
    args[i] = NULL;
    return args;  // Return the array of arguments
}

void logout(char *input)
{
    free(input);
    puts("logout");
    exit(EXIT_SUCCESS);// exit_success = 0;
}

void echo(char **arguments)
{
    while (*(++arguments))
    {
        printf("%s ", *arguments);
    }
    puts("");
}

void cd(char **path)
{
    if(path[1] == NULL){
        printf("-myShell: cd: No argument provided\n");
        return;
    }
    if(strcmp(path[1], "..")==0){
        chdir("..");
        return;
    }
    if(strncmp(path[1], "\"", 1) == 0){
        char *dir = malloc(SIZE_BUFF * sizeof(char));
        if (dir == NULL) {
            printf("Failed to allocate memory\n");
            return;
        }
        if (path[1][0] == '\"')
            strcpy(dir, path[1] + 1);
        else
            strcpy(dir, path[1]); // Skip the initial quote
        for (int i = 2; path[i] != NULL; i++)
        {
            strcat(dir, " ");
            strcat(dir, path[i]);
        }
        // Remove the final quote, if present
        int len = strlen(dir);
        if (dir[len - 1] == '\"')
            dir[len - 1] = '\0';
        // Attempt to change directory
        if (chdir(dir) != 0)
            printf("-myShell: cd: %s: No such file or directory\n", dir);
            
        free(dir);
    }
    else
    {
        if(strncmp(path[1], "/", 1) == 0 && path[2] != NULL){
        printf("-myShell: cd: Too many arguments\n");
        return;
    }
        // Attempt to change directory
        if (chdir(path[1]) != 0)
            printf("-myShell: cd: %s: No such file or directoryyyyyyyyy\n", path[1]);
    }

}





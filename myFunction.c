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


char **splitArgument(char* input) {
    int argsCapacity = 10; // Initial capacity for argument array
    char** args = malloc(sizeof(char*) * argsCapacity);
    int argCount = 0;
    const char* p = input;
    char* arg = malloc(strlen(input) + 1); // Temp storage for the current argument
    char* writePtr = arg;

    while (*p) {
        while (*p == ' ' && writePtr == arg) p++; // Skip leading spaces if we're at the start of a new argument

        if (!*p) break; // End of string

        if (*p == '"') {
            p++; // Skip the opening quote
            while (*p && *p != '"') {
                if (*p == '\\' && *(p + 1) == '"') { // Handle escaped quote
                    *writePtr++ = '"';
                    p += 2;
                } else {
                    *writePtr++ = *p++;
                }
            }
            if (*p) p++; // Skip the closing quote
        } else {
            while (*p && *p != ' ') {
                *writePtr++ = *p++;
            }
        }

        // If we've reached a space or the end of the string, finalize the current argument.
        if (*p == ' ' || *p == '\0') {
            *writePtr = '\0'; // Null-terminate the argument

            // Allocate just enough memory for the argument and copy it from temp storage.
            args[argCount] = malloc(writePtr - arg + 1);
            strcpy(args[argCount++], arg);

            // Reset writePtr to start of arg for next argument
            writePtr = arg;

            if (argCount >= argsCapacity) { // Increase capacity of args array if needed
                argsCapacity *= 2;
                args = realloc(args, sizeof(char*) * argsCapacity);
            }
        }

        if (*p) p++; // Move past the space or continue if not at the end
    }

    if (writePtr != arg) { // Handle case where last argument doesn't end with a space
        *writePtr = '\0'; // Null-terminate the argument
        args[argCount++] = strdup(arg); // Copy the last argument
    }

    free(arg); // Free the temporary storage
    args[argCount] = NULL; // NULL-terminate the array
    return args;
}

void freeArguments(char** args) {
    char** p = args;
    while (*p) {
        free(*p++);
    }
    free(args);
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
    if(strncmp(path[1], "\"", 1) == 0){
        char *dir = malloc(SIZE_BUFF * sizeof(char));
        if (dir == NULL) {
            printf("Failed to allocate memory\n");
            return;
        }
        if (path[1][0] == '\"')
            strcpy(dir, path[1] + 1);// Skip the initial quote
        // else
        //     strcpy(dir, path[1]); 
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
            printf("-myShell: cd: %s: No such file or directory\n", path[1]);
    }

}



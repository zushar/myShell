#include "myFunction.h"

void getLocation()
{
    char location[SIZE_BUFF];
    struct passwd *pw; // struct passwd is a structure that stores user account information
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
{
    char ch;  // Variable to hold each character as it's read
    int size = 1;  // Size of the input string (starts at 1 for the null terminator)
    int index = 0;  // Current position in the input string
    char *str = (char *)malloc(size * sizeof(char));  // Allocate initial input string
    if (str == NULL)
    {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    while ((ch = getchar()) != '\n')
    {
        *(str + index) = ch;

        size++;
        index++;

        // Reallocate the input string to the new size
        str = (char *)realloc(str, size);
    }
    *(str + index) = '\0';
    return str;  
}


char **splitArgument(char* input) {
    int argsCapacity = 10; // Initial capacity for the arguments array
    // Dynamically allocate space for the arguments array with initial capacity
    char** args = (char**)malloc(sizeof(char*) * argsCapacity);
    // Counter for the number of arguments added to the args array
    int argCount = 0;
    // Pointer to iterate through the input string
    const char* p = input;
    // Allocate temporary storage for collecting characters of the current argument
    char* arg = (char*)malloc(strlen(input) + 1);
    // Pointer to write into the temporary storage (arg)
    char* writePtr = arg;

    // Iterate over each character in the input string
    while (*p) {
        // Skip leading spaces for a new argument
        while (*p == ' ' && writePtr == arg) p++;

        if (!*p) break; // If end of string is reached, exit the loop

        // If a double quote is encountered, treat it as the start of a quoted argument
        if (*p == '"') {
            p++; // Skip the opening quote
            // Collect characters until the closing quote is encountered
            while (*p && *p != '"') {
                // Handle escaped double quotes
                if (*p == '\\' && *(p + 1) == '"') {
                    *writePtr++ = '"';
                    p += 2; // Skip the escape character and the quote
                } else {
                    *writePtr++ = *p++; // Collect the character
                }
            }
            if (*p) p++; // Skip the closing quote
        } else {
            // Collect characters until a space is encountered, indicating the end of the argument
            while (*p && *p != ' ') {
                *writePtr++ = *p++; // Collect the character
            }
        }

        // Finalize the current argument if a space or the end of the string is reached
        if (*p == ' ' || *p == '\0') {
            *writePtr = '\0'; // Null-terminate the current argument

            // Allocate just enough memory for the argument and copy it from temp storage
            args[argCount] = (char*)malloc(writePtr - arg + 1);
            strcpy(args[argCount++], arg);

            // Reset the temporary storage for the next argument
            writePtr = arg;

            // Double the capacity of the args array if the current capacity is exceeded
            if (argCount >= argsCapacity) {
                argsCapacity *= 2;
                args = (char**)realloc(args, sizeof(char*) * argsCapacity);
            }
        }

        if (*p) p++; // Move past the space to the start of the next argument
    }

    // Add the last argument if it doesn't end with a space
    if (writePtr != arg) {
        *writePtr = '\0'; // Null-terminate the current argument
        args[argCount++] = strdup(arg); // Copy the last argument
    }

    free(arg); // Free the temporary storage
    args[argCount] = NULL; // NULL-terminate the arguments array

    return args; // Return the array of arguments
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
    if (path[1] == NULL) {
        chdir(getenv("HOME"));
        return;
    }    
    if (path[2] != NULL) {
        printf("-myShell: cd: too many arguments\n");
        return;
    } 
     if (chdir(path[1]) != 0)  // chdir() returns 0 on success, -1 on failure
        printf("-myShell: cd: %s: No such file or directory\n", path[1]);
}

void cp(char ** arguments)
{
    if (arguments[1] == NULL || arguments[2] == NULL){
        printf("cp: missing file operand\n");
        return;
    }
    if (arguments[3] != NULL){
        printf("cp: too many arguments\n");
        return;
    }
    FILE *source, *target; 
    char ch;
    source = fopen(arguments[1], "r");
    if (source == NULL){
        printf("cp: cannot stat '%s': No such file or directory\n", arguments[1]);
        return;
    }
    target = fopen(arguments[2], "w");
    if (target == NULL){
        printf("cp: cannot create regular file '%s': No such file or directory\n", arguments[2]);
        return;
    }
    while ((ch = fgetc(source)) != EOF){
        fputc(ch, target);
    }
    fclose(source);
    fclose(target);
    printf("File copied successfully.\n");
}

void delete(char **path)
{
    if (path[2] != NULL)
    {
        printf("-myShell: delete: too many arguments\n");
        return;
    }
    if (unlink(path[1]) != 0)
        printf("-myShell: delete: %s: No such file or directory\n", path[1]);
}

void get_dir()
{
    // Declare a directory stream pointer 'dir' and a directory entry pointer 'entry'
    DIR *dir;
    struct dirent *entry;

    // Try to open the current directory
    if((dir = opendir("./")) == NULL)
    {
        // If opening the directory fails, print an error message and return
        printf("Error in opening directory\n");
        return;
    }

    // Read the entries in the directory
    while((entry = readdir(dir)) != NULL)
    {
        // Print the name of each entry
        printf("%s\n", entry->d_name);
    }

    // Close the directory stream
    closedir(dir);
}

void SystemCall(char **arguments)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("Error forking\n");
        return;
    }
    if (pid == 0)
    {
        if (execvp(arguments[0], arguments) == -1)
        {
            printf("Error executing command\n");
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
}

void mypipe(char **argv1,char ** argv2){

    int fildes[2];
    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            /* first component of command line */
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            execvp(argv1[0], argv1);
        }
        /* 2nd command component of command line */
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        /* standard input now comes from pipe */
        execvp(argv2[0], argv2);
    }
}

void move(char **arguments){
    if (arguments[1] == NULL || arguments[2] == NULL){
        printf("move: missing file operand\n");
        return;
    }
    if (arguments[3] != NULL){
        printf("move: too many arguments\n");
        return;
    }
    FILE *source, *target;
    char ch;
    source = fopen(arguments[1], "r");
    if (source == NULL){
        printf("mv: cannot stat '%s': No such file or directory\n", arguments[1]);
        return;
    }
    target = fopen(arguments[2], "w");
    if (target == NULL){
        printf("mv: cannot create regular file '%s': No such file or directory\n", arguments[2]);
        return;
    }
    while ((ch = fgetc(source)) != EOF){
        fputc(ch, target);
    }
    if (unlink(arguments[1]) != 0){
        printf("-myShell: delete: %s: No such file or directory\n", arguments[1]);
    }
    printf("File moved successfully.\n");
}

void echoppend(char **arguments){
    if (arguments[1] == NULL){
        printf("echoppend: missing file operand\n");
        return;
    }
    if (arguments[2] != NULL){
        printf("echoppend: too many arguments\n");
        return;
    }
    FILE *target;
    char ch;
    target = fopen(arguments[1], "a");// append mode apend the new to the old and creats new file in nut exist
    if (target == NULL){
        printf("echoppend: cannot create regular file '%s': No such file or directory\n", arguments[1]);
        return;
    }
    while ((ch = getchar()) != EOF){
        fputc(ch, target);
    }
    fclose(target);
    printf("File appended successfully.\n");
}

void echorite(char **arguments){
    if (arguments[1] == NULL){
        printf("echorite: missing file operand\n");
        return;
    }
    if (arguments[2] != NULL){
        printf("echorite: too many arguments\n");
        return;
    }
    FILE *target;
    char ch;
    target = fopen(arguments[1], "w");
    if (target == NULL){
        printf("echorite: cannot create regular file '%s': No such file or directory\n", arguments[1]);
        return;
    }
    while ((ch = getchar()) != EOF){
        fputc(ch, target);
    }
    fclose(target);
    printf("File written successfully.\n");
}

void readFile(char **arguments){
    if (arguments[1] == NULL){
        printf("read: missing file operand\n");
        return;
    }
    if (arguments[2] != NULL){
        printf("read: too many arguments\n");
        return;
    }
    FILE *source;
    char ch;
    source = fopen(arguments[1], "r");
    if (source == NULL){
        return;
    }
    while ((ch = fgetc(source)) != EOF){
        putchar(ch);
    }
    fclose(source);
}

void wordCount(char **args) {
    // Check if the correct number of arguments has been provided
    if (args[1] == NULL || args[2] == NULL) {
        printf("wordCount: missing file operand\n");
        return;
    }
    // Open the file in read mode
    FILE *file = fopen(args[2], "r");
    if (file == NULL) {
        // File does not exist, return without printing anything
        return;
    }
    int count = 0;
    if (strcmp(args[1], "-l") == 0) {
        // Count lines
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '\n') {
                count++;
            }
        }
    } else if (strcmp(args[1], "-w") == 0) {
        // Count words
        char word[1024];
        while (fscanf(file, "%1023s", word) == 1) {
            count++;
        }
    } else {
        printf("wordCount: invalid option %s\n", args[1]);
        fclose(file);
        return;
    }
    printf("%d\n", count);
    fclose(file);
}
    
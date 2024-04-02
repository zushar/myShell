#include "myShell.h"
#include "myFunction.h"
void freeArguments(char** args) {
    char** p = args;
    while (*p) {
        free(*p++);
    }
    free(args);
}

int argumentArraySize(char** args) {
    int count = 0;
    while (*args++) {
        count++;
    }
    return count;
}

int pipeCheck(char **arguments)
{
    int i = 0;
    while (arguments[i] != NULL)
    {
        if (strcmp(arguments[i], "|") == 0)
        {
            free(arguments[i]);// free the pipe character because we can't free null
            arguments[i] = NULL;
            return 1;
        }
        i++;
    }
    return 0;
}

char ***splitArgumentsArray(char **arguments, int size) {
    int numSubArrays = 1;
    for (int i = 0; i < size; i++) {
        if (arguments[i] == NULL) {
            numSubArrays++;
        }
    }

    char ***splitArray = (char ***)malloc((numSubArrays + 1) * sizeof(char **));
    if (splitArray == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int subArrayIndex = 0;
    int start = 0;
    int sizeOfSubArray = 0;
    for (int i = 0; i < size; i++, sizeOfSubArray++) {
        if (arguments[i] == NULL || i == size - 1) {

            char **subArray = (char **)malloc((sizeOfSubArray + 1) * sizeof(char *));
            if (subArray == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            for(int j = start; j <= i; j++){
                subArray[j - start] = arguments[j];
            }

            subArray[sizeOfSubArray] = NULL;
            splitArray[subArrayIndex++] = subArray;
            start = i + 1;
            sizeOfSubArray = 0;
        }
    }
    splitArray[subArrayIndex] = NULL;
    return splitArray;
}

int main()
{
    welcome();
    while (1)
    {
        getLocation();
        char *input = getInputFromUser();

        if (input == NULL)
        {
            printf("Error: Unable to read input\n");
            continue;
        }

        char **arguments = splitArgument(input);
        int size = argumentArraySize(arguments);
        int isPipe = pipeCheck(arguments);
        if (strcmp(arguments[0], "exit") == 0){
            freeArguments(arguments);
            logout(input);
        } 
        if(isPipe){
            char ***args = splitArgumentsArray(arguments, size);
            mypipe(args[0], args[1]);
            wait(NULL);
            for (int i = 0; args[i] != NULL; i++)
            {
                free(args[i]);
            }
            free(args);
        }else if(strcmp(arguments[0], "echo") == 0){
            if (strcmp(arguments[1], ">") == 0){
                echorite(arguments);
            }else if (strcmp(arguments[1], ">>") == 0){
                echoppend(arguments);
            }else{
                echo(arguments);
            }
        }else if (strcmp(arguments[0], "cd") == 0){
            cd(arguments);
        }else if (strcmp(arguments[0], "cp") == 0){
            cp(arguments);
        }else if (strcmp(arguments[0], "delete") == 0){
            delete(arguments);
        }else if (strcmp(arguments[0], "dir") == 0){
            get_dir();
        }else if (strcmp(arguments[0], "mv") == 0){
            move(arguments);
        }else if (strcmp(arguments[0], "read") == 0){
            readFile(arguments);
        }else if (strcmp(arguments[0], "wc") == 0){
            wordCount(arguments);
        }else{
            SystemCall(arguments);
        }
        for (int i = 0; i < size; i++) {
            free(arguments[i]);
        }
        free(arguments);
        free(input);
    }
    return 0;
}

void welcome()
{
    const char *ptexts[] = {
        "Welcome to Zusha Shell - ",
        "A simple shell written in C",
        "Version 0.0.1",
        "https://github.com/zushar",
        "Have Fun!"
    };
    const char *part_lines[] = {
        "ZZZZZZ   U       U  SSSSSS  H   H    AAAAA     |   ",
        "    Z    U       U  S       H   H   A     A    |   ",
        "   Z     U       U   SSSSS  HHHHH   AAAAAAA    |   ",
        " Z       U       U       S  H   H   A     A    |   ",
        "ZZZZZZ    UUUUUUU   SSSSSS  H   H   A     A    |   ",
    };
    const char *pcolors[] = {
        "\033[0;31m", // Red
        "\033[0;32m", // Green
        "\033[0;34m", // Blue
        "\033[0;33m", // Yellow
        "\033[0;35m", // Magenta
    };
    const int colors_count = sizeof(pcolors) / sizeof(pcolors[0]);

    // Print each line of the ASCII art in a different color
    for (int i = 0; i < colors_count; ++i) {
        printf("%s%s%s\n", pcolors[i], part_lines[i] , ptexts[i]);
    }
    // Reset text color to default
    printf("\033[0;31mtype 'exit' to quit.\n");
    printf("\033[0m");
}
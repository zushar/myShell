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
    printf("%s@%s\033[0m$ ", pw->pw_name, location);
    printf("\033[0m");
}

char *getInputFromUser()
{
    char *input = (char *)malloc(SIZE_BUFF * sizeof(char));
    if (input == NULL)
    {
        printf("Error\n");
        return NULL;
    }
    printf("\033[0;32m");
    fgets(input, SIZE_BUFF, stdin);
    printf("\033[0m");
    return input;
}

char **splitArgument(char *str)
{

    char **args = (char **)malloc(SIZE_BUFF * sizeof(char *));
    if (args == NULL)
    {
        printf("Error\n");
        return NULL;
    }
    int i = 0;
    //So token is indeed pointing to the address of the first character in the first token of str.
    char *token = strtok(str, " \t");
    while (token != NULL)
    {
        args[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
        if (args[i] == NULL)
        {
            printf("Error\n");
            for (int j = 0; j < i; j++) {
                free(args[j]);
            }
            free(args);
            return NULL;
        }
        strcpy(args[i], token);
        token = strtok(NULL, " \t");
        i++;
    }
        if (i > 0 && args[i-1][strlen(args[i-1])-1] == '\n') {
            args[i-1][strlen(args[i-1])-1] = '\0';
        }
    args[i] = NULL;
    return args;
}
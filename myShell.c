#include "myShell.h"
#include "myFunction.h"
int main()
{
    welcome();
    char **args = NULL;
    while (1)
    {
        getLocation();
        char *input = getInputFromUser();
        if (input == NULL)
        {
            printf("Error\n");
            free(input);   
            return 1;
        }
        if (strcmp(input, "exit\n") == 0)
        {
            free(input);
            break;
        }
        args = splitArgument(input);
        if (args == NULL)
        {
            printf("Error\n");
            free(input);
            return 1;
        }
        free(input);
    }
    if (args != NULL)
    {for(int i = 0; args[i] != NULL; i++)
    {
        printf("%s\n", args[i]);
    }
    printf("Goodbye\n");
    printf("\033[0;31m");
    for(int i = 0; args[i] != NULL; i++) {
    free(args[i]);
    }
    free(args);}
    return 0;
}

void welcome()
{
    puts("Welcome to my Shell");
    puts("Type 'exit' to quit");
}
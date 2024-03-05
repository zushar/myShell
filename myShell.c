#include "myShell.h"
#include "myFunction.h"
int main()
{
    welcome();
    while (1)
    {
        getLocation();
        char *input = getInputFromUser();
        puts(input);
        char **arguments = splitArgument(input);
        for (int i = 0; *(arguments + i) != NULL; i++)
        {
            puts(*(arguments+i));
            // puts(arguments[i]);
        }

        free(arguments);
        free(input);

        break;
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
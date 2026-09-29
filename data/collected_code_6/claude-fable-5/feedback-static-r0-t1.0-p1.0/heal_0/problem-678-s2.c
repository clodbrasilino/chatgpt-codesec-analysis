#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_spaces(char *str)
{
    size_t i;
    size_t j;

    if (str == NULL) {
        return;
    }

    j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

int main(void)
{
    char input[] = "Hello World, this is a test string.";

    printf("Before: \"%s\"\n", input);
    remove_spaces(input);
    printf("After:  \"%s\"\n", input);

    return EXIT_SUCCESS;
}
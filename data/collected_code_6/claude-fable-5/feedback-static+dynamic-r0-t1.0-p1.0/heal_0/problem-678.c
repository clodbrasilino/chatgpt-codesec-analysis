#include <stdio.h>
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
    char text[] = "Hello World, this is a test string.";

    printf("Before: \"%s\"\n", text);
    remove_spaces(text);
    printf("After:  \"%s\"\n", text);

    return 0;
}
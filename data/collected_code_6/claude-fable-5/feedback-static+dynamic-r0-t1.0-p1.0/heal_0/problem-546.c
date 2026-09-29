#include <stdio.h>
#include <stdlib.h>

const char *find_last_occurrence(const char *str, char ch)
{
    const char *last = NULL;

    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0') {
        if (*str == ch) {
            last = str;
        }
        str++;
    }

    if (ch == '\0') {
        last = str;
    }

    return last;
}

int main(void)
{
    const char *text = "hello world";
    char target = 'o';
    const char *result = NULL;

    result = find_last_occurrence(text, target);

    if (result != NULL) {
        printf("Last occurrence of '%c' found at index %td\n",
               target, result - text);
    } else {
        printf("Character '%c' not found in \"%s\"\n", target, text);
    }

    return EXIT_SUCCESS;
}
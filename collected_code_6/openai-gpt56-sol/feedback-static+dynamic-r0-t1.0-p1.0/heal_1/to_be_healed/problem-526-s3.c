#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void capitalize_first_and_last(char *string)
{
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(string);
    size_t index = 0;

    while (index < length) {
        while (index < length && isspace((unsigned char)string[index])) {
            ++index;
        }

        if (index == length) {
            break;
        }

        size_t first = index;

        while (index < length && !isspace((unsigned char)string[index])) {
            ++index;
        }

        size_t last = index - 1;
        string[first] = (char)toupper((unsigned char)string[first]);
        string[last] = (char)toupper((unsigned char)string[last]);
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (length > 0 && line[(size_t)length - 1] == '\n') {
        line[(size_t)length - 1] = '\0';
    }

    capitalize_first_and_last(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}
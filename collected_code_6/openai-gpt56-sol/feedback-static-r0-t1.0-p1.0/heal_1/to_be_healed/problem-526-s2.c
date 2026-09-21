#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void capitalize_word_boundaries(char *string)
{
    size_t length;

    if (string == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);

    for (size_t i = 0U; i < length; ++i) {
        unsigned char current = (unsigned char)string[i];

        if (isspace(current)) {
            continue;
        }

        if (i == 0U || isspace((unsigned char)string[i - 1U])) {
            string[i] = (char)toupper(current);
        }

        if (i + 1U == length || isspace((unsigned char)string[i + 1U])) {
            string[i] = (char)toupper((unsigned char)string[i]);
        }
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (length > 0 && line[(size_t)length - 1U] == '\n') {
        line[(size_t)length - 1U] = '\0';
    }

    capitalize_word_boundaries(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}
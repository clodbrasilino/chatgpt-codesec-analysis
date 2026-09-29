#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_all_vowels(const char *string)
{
    bool found[5] = {false, false, false, false, false};

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        switch (tolower((unsigned char)*string)) {
            case 'a':
                found[0] = true;
                break;
            case 'e':
                found[1] = true;
                break;
            case 'i':
                found[2] = true;
                break;
            case 'o':
                found[3] = true;
                break;
            case 'u':
                found[4] = true;
                break;
            default:
                break;
        }
        ++string;
    }

    return found[0] && found[1] && found[2] && found[3] && found[4];
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        if (ferror(stdin) != 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (contains_all_vowels(line)) {
        if (fputs("Accepted\n", stdout) == EOF) {
            free(line);
            return EXIT_FAILURE;
        }
    } else {
        if (fputs("Rejected\n", stdout) == EOF) {
            free(line);
            return EXIT_FAILURE;
        }
    }

    free(line);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
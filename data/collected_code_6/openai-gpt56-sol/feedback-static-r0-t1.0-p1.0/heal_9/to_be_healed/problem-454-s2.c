#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    size_t capacity = 64;
    size_t length = 0;
    char *word = malloc(capacity);

    if (word == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(word);
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n' || ch == '\r') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(word);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            char *new_word = realloc(word, new_capacity);
            if (new_word == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = new_word;
            capacity = new_capacity;
        }

        word[length++] = (char)(unsigned char)ch;
    }

    word[length] = '\0';

    int result = puts(contains_z(word) ? "match" : "no match");
    free(word);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}
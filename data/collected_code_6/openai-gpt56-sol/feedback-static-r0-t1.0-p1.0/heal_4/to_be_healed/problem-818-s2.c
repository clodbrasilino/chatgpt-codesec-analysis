#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_lowercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (islower((unsigned char)*string) != 0) {
            if (count == SIZE_MAX) {
                return SIZE_MAX;
            }
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t total = 0;
    ssize_t length;

    /* Possible weaknesses found:
     *  Although the value stored to 'length' is used in the enclosing expression, the value is never actually read from 'length' [deadcode.DeadStores]
     */
    while ((length = getline(&line, &capacity, stdin)) != -1) {
        size_t count = count_lowercase(line);

        if (count > SIZE_MAX - total) {
            free(line);
            fputs("Lowercase character count overflow.\n", stderr);
            return EXIT_FAILURE;
        }

        total += count;
    }

    free(line);

    if (ferror(stdin) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", total) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
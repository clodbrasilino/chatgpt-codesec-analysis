#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool all_characters_same(const char *string)
{
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    for (size_t i = 1; string[i] != '\0'; ++i) {
        if (string[i] != string[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    puts(all_characters_same(line) ? "All characters are the same."
                                   : "Not all characters are the same.");

    free(line);
    return EXIT_SUCCESS;
}
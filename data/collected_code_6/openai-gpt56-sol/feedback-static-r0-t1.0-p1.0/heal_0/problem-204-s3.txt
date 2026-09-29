#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t count_character(const char *string, char character)
{
    size_t count = 0U;

    if (string == NULL) {
        return 0U;
    }

    while (*string != '\0') {
        if (*string == character) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    char character = '\0';

    if (getline(&line, &capacity, stdin) == -1) {
        free(line);
        return EXIT_FAILURE;
    }

    if (scanf("%c", &character) != 1) {
        free(line);
        return EXIT_FAILURE;
    }

    line[strcspn(line, "\n")] = '\0';

    if (printf("%zu\n", count_character(line, character)) < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}
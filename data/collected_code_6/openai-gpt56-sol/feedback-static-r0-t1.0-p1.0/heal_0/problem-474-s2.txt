#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_characters(const char *source, char target, char replacement)
{
    char *result;
    char *position;
    size_t length;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);
    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, source, length + 1U);

    for (position = result; *position != '\0'; ++position) {
        if (*position == target) {
            *position = replacement;
        }
    }

    return result;
}

int main(void)
{
    const char source[] = "The quick brown fox jumps over the lazy dog.";
    char *result = replace_characters(source, 'o', '0');

    if (result == NULL) {
        fputs("Failed to replace characters.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_spaces(const char *input)
{
    size_t len;
    size_t space_count = 0;
    size_t i;
    size_t j = 0;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);

    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            space_count++;
        }
    }

    if (space_count > (SIZE_MAX - len - 1) / 2) {
        return NULL;
    }

    result = malloc(len + (space_count * 2) + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            result[j] = '%';
            result[j + 1] = '2';
            result[j + 2] = '0';
            j += 3;
        } else {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test = "Hello World example string";
    char *converted;

    converted = replace_spaces(test);
    if (converted == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original:  %s\n", test) < 0) {
        free(converted);
        return EXIT_FAILURE;
    }

    if (printf("Converted: %s\n", converted) < 0) {
        free(converted);
        return EXIT_FAILURE;
    }

    free(converted);
    converted = NULL;

    return EXIT_SUCCESS;
}
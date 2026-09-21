#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *remove_digits(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)input[i])) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int remove_digits_from_list(const char **input, char **output, size_t count)
{
    size_t i;

    if (input == NULL || output == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        output[i] = remove_digits(input[i]);
        if (output[i] == NULL) {
            size_t k;
            for (k = 0; k < i; k++) {
                free(output[k]);
                output[k] = NULL;
            }
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const char *strings[] = {
        "hello123world",
        "abc456",
        "789def",
        "no digits here",
        "1234567890"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    char **results;
    size_t i;

    results = malloc(count * sizeof(char *));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (remove_digits_from_list(strings, results, count) != 0) {
        fprintf(stderr, "Failed to process string list\n");
        free(results);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("\"%s\" -> \"%s\"\n", strings[i], results[i]) < 0) {
            break;
        }
    }

    for (i = 0; i < count; i++) {
        free(results[i]);
    }
    free(results);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096U

char *remove_odd_characters(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LENGTH);
    if (len >= MAX_INPUT_LENGTH) {
        return NULL;
    }

    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if ((i % 2U) == 0U) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *original = "abcdefghij";
    char *filtered;

    filtered = remove_odd_characters(original);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", original);
    printf("Filtered: %s\n", filtered);

    free(filtered);
    filtered = NULL;

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *remove_lowercase(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (!islower((unsigned char)input[i])) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test1 = "HeLLoWorLD";
    const char *test2 = "abcDEFghi";
    const char *test3 = "ALLUPPER";
    char *output;

    output = remove_lowercase(test1);
    if (output == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }
    printf("Input: %s -> Output: %s\n", test1, output);
    free(output);

    output = remove_lowercase(test2);
    if (output == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }
    printf("Input: %s -> Output: %s\n", test2, output);
    free(output);

    output = remove_lowercase(test3);
    if (output == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }
    printf("Input: %s -> Output: %s\n", test3, output);
    free(output);

    return EXIT_SUCCESS;
}
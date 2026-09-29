#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096U

char *squeeze_char(const char *input, char target)
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

    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        if ((input[i] == target) && (j > 0U) && (result[j - 1U] == target)) {
            continue;
        }
        result[j] = input[i];
        j++;
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *text = "aaabbbcccaaa   hello   worldaaa";
    char *squeezed;

    squeezed = squeeze_char(text, 'a');
    if (squeezed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("Original: %s\n", text);
    printf("Squeezed: %s\n", squeezed);
    free(squeezed);
    squeezed = NULL;

    squeezed = squeeze_char(text, ' ');
    if (squeezed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("Squeezed spaces: %s\n", squeezed);
    free(squeezed);
    squeezed = NULL;

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_lowercase_substrings(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char *src = input;
    char *dst = result;

    while (*src != '\0') {
        if (!islower((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }

    *dst = '\0';
    return result;
}

int main(void)
{
    const char *input = "Hello World lowercase example ABC";
    char *output = remove_lowercase_substrings(input);

    if (output == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", input);
    printf("Output: %s\n", output);
    free(output);
    return EXIT_SUCCESS;
}
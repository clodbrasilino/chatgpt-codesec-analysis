#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_delimiters(const char *str, size_t n)
{
    size_t len;
    size_t i;
    size_t count = 0;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (count < n && (str[i] == ' ' || str[i] == ',' || str[i] == '.')) {
            result[i] = ':';
            count++;
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';

    return result;
}

int main(void)
{
    const char *input = "Hello, world. This is a test, with spaces, commas and dots.";
    size_t max_replacements = 5;
    char *output;

    output = replace_delimiters(input, max_replacements);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Modified: %s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}
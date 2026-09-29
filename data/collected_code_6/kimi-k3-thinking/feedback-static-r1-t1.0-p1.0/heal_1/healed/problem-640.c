#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parentheses(const char *str, size_t max_len)
{
    size_t len;
    size_t i;
    size_t j = 0;
    size_t depth = 0;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, max_len);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char input[] = "Hello (world) this is (a (nested) test) string";
    char *output;

    output = remove_parentheses(input, sizeof(input));
    if (output == NULL) {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}
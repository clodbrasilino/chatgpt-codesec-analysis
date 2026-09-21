#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split_string_to_chars(const char *input, char ***output, int *len) {
    if (!input || !output || !len) return;
    *len = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len == 0) return;

    *output = (char **)malloc((input_len + 1) * sizeof(char *));
    if (!*output) return;

    for (int i = 0; i < input_len; ++i) {
        (*output)[i] = (char *)malloc(2 * sizeof(char));
        if (!(*output)[i]) {
            for (int j = 0; j < i; ++j) {
                free((*output)[j]);
            }
            free(*output);
            *output = NULL;
            return;
        }
        (*output)[i][0] = input[i];
        (*output)[i][1] = '\0';
    }

    *len = input_len;
    (*output)[*len] = NULL;
}

int main() {
    const char *str = "Hello, World!";
    char **result = NULL;
    int length = 0;

    split_string_to_chars(str, &result, &length);

    for (int i = 0; i < length; ++i) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}
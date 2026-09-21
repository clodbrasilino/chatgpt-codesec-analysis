#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_duplicates(const char *str, char ch) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int prev_was_ch = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            if (!prev_was_ch) {
                result[j++] = str[i];
                prev_was_ch = 1;
            }
        } else {
            result[j++] = str[i];
            prev_was_ch = 0;
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *input = "heeelllooooo wooooorllld";
    char target = 'o';

    char *output = remove_duplicates(input, target);
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
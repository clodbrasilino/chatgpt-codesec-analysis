#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* move_numbers(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(src);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)src[i])) {
            result[idx++] = src[i];
        }
    }

    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)src[i])) {
            result[idx++] = src[i];
        }
    }

    result[idx] = '\0';
    return result;
}

int main(void) {
    const char *input = "C3 1s f4n!";
    char *output = move_numbers(input);

    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original: %s\n", input);
    printf("Modified: %s\n", output);

    free(output);
    output = NULL;

    return 0;
}
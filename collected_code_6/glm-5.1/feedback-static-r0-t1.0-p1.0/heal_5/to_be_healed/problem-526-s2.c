#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char *capitalize_first_last(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, str, len + 1);

    size_t i = 0;
    while (i < len) {
        while (i < len && isspace((unsigned char)result[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        size_t start = i;
        while (i < len && !isspace((unsigned char)result[i])) {
            i++;
        }
        size_t end = i - 1;

        result[start] = (char)toupper((unsigned char)result[start]);
        result[end] = (char)toupper((unsigned char)result[end]);
    }

    return result;
}

int main(void) {
    const char *input = "hello world from c programming";
    char *output = capitalize_first_last(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("%s\n", output);
    free(output);
    return 0;
}
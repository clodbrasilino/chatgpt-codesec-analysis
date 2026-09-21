#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *extract_quoted(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    const char *start = strchr(str, '"');
    if (start == NULL) {
        return NULL;
    }

    start++;

    const char *end = strchr(start, '"');
    if (end == NULL) {
        return NULL;
    }

    size_t len = (size_t)(end - start);
    if (len == 0) {
        return NULL;
    }

    if (len >= SIZE_MAX) {
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (len + 1 < len) {
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, start, len);
    result[len] = '\0';

    return result;
}

void print_result(const char *input) {
    char *extracted = extract_quoted(input);
    if (extracted != NULL) {
        printf("Extracted: %s\n", extracted);
        free(extracted);
    } else {
        printf("No valid quoted string found\n");
    }
}

int main(void) {
    print_result("This is a \"test\" string");
    print_result("No quotes here");
    print_result("Empty \"\" quotes");
    print_result("Multiple \"first\" and \"second\" quotes");
    print_result(NULL);
    print_result("\"unterminated");

    return 0;
}
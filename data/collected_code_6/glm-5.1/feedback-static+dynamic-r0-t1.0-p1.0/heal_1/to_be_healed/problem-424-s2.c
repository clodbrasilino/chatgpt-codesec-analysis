#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* extract_rear_indices(const char** strings, size_t count) {
    if (strings == NULL) {
        return NULL;
    }

    char* result = (char*)malloc(count + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(strings[i]);
        if (len == 0) {
            free(result);
            return NULL;
        }

        result[i] = strings[i][len - 1];
    }

    result[count] = '\0';
    return result;
}

int main(void) {
    const char* arr[] = {
        "hello",
        "world",
        "C",
        "programming"
    };

    size_t count = sizeof(arr) / sizeof(arr[0]);

    char* rear_chars = extract_rear_indices(arr, count);
    if (rear_chars == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", rear_chars);

    free(rear_chars);
    rear_chars = NULL;

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char* const* list, size_t count) {
    size_t total_length = 0;
    char* result;
    char* current;
    size_t i;
    size_t len;

    if (list == NULL && count > 0) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        if (list[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(list[i]);
        }
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    current = result;
    for (i = 0; i < count; ++i) {
        if (list[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            len = strlen(list[i]);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, list[i], len);
            current += len;
        }
    }
    *current = '\0';

    return result;
}

int main(void) {
    const char* elements[] = {"Concatenating ", "a ", "list ", "of ", "strings ", "safely."};
    size_t count = sizeof(elements) / sizeof(elements[0]);
    char* concatenated_string;

    concatenated_string = concatenate_list(elements, count);

    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }
}
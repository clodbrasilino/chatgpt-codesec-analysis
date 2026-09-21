#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* move_numbers_first(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t num_idx = 0;
    size_t other_idx = 0;
    size_t i;

    for (i = 0; i < len; ++i) {
        if (input[i] >= '0' && input[i] <= '9') {
            num_idx++;
        }
    }

    other_idx = num_idx;
    num_idx = 0;

    for (i = 0; i < len; ++i) {
        if (input[i] >= '0' && input[i] <= '9') {
            result[num_idx++] = input[i];
        } else {
            result[other_idx++] = input[i];
        }
    }
    result[len] = '\0';

    return result;
}

int main(void) {
    const char* original = "a1b2c3d4e5";
    char* modified = move_numbers_first(original);

    if (modified != NULL) {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", modified);
        free(modified);
    } else {
        printf("Memory allocation failed or invalid input.\n");
    }

    return 0;
}
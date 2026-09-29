#include <stdio.h>
#include <stdlib.h>

char* move_numbers_first(const char* input) {
    size_t len = 0;
    size_t num_count = 0;
    size_t num_idx = 0;
    size_t other_idx = 0;
    size_t i;
    char* result;

    if (input == NULL) {
        return NULL;
    }

    while (input[len] != '\0') {
        if (input[len] >= '0' && input[len] <= '9') {
            num_count++;
        }
        len++;
    }

    result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    other_idx = num_count;

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
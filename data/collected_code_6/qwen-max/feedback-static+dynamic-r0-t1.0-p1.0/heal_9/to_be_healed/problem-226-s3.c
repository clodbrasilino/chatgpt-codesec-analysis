#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_odd_index_chars(char *str, size_t len) {
    char *result = malloc(len + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    int i, j = 0;
    for (i = 0; i < len && j < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    memmove(str, result, j + 1);
    free(result);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0) {
            remove_odd_index_chars(input, len);
            printf("Modified string: %s\n", input);
        } else {
            printf("Empty string.\n");
        }
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}
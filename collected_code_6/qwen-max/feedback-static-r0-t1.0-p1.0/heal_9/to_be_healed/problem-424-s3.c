#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extract_rear_index_elements(char *output[], char **input, int n) {
    for (int i = 0; i < n; ++i) {
        if (input[i] && *input[i]) {
            size_t length = strnlen(input[i], 1024);
            if (length > 0) {
                output[i] = (char *)malloc(2 * sizeof(char));
                if (!output[i]) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                output[i][0] = input[i][length - 1];
                output[i][1] = '\0';
            } else {
                output[i] = (char *)malloc(sizeof(char));
                if (!output[i]) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                output[i][0] = '\0';
            }
        } else {
            output[i] = (char *)malloc(1);
            if (!output[i]) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            output[i][0] = '\0';
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "!", "", NULL};
    int n = 5;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *result[5];

    extract_rear_index_elements(result, strings, n);

    for (int i = 0; i < n; ++i) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    return 0;
}
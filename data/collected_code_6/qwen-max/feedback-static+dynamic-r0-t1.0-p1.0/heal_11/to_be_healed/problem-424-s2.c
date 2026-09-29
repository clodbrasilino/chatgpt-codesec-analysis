#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void extract_rear(char *output[], char *input[], int len) {
    for (int i = 0; i < len; ++i) {
        if (input[i] != NULL && input[i][0] != '\0') {
            size_t str_len = 0;
            while (input[i][str_len] != '\0') {
                str_len++;
            }
            if (str_len > 0) {
                output[i] = malloc(2 * sizeof(char));
                if (output[i] != NULL) {
                    output[i][0] = input[i][str_len - 1];
                    output[i][1] = '\0';
                }
            } else {
                output[i] = malloc(sizeof(char));
                if (output[i] != NULL) {
                    *output[i] = '\0';
                }
            }
        } else {
            output[i] = malloc(sizeof(char));
            if (output[i] != NULL) {
                *output[i] = '\0';
            }
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "", NULL};
    int len = sizeof(strings) / sizeof(strings[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *results[len];

    extract_rear(results, strings, len);

    for (int i = 0; i < len; ++i) {
        if (results[i] != NULL) {
            printf("%s\n", results[i]);
            free(results[i]);
        }
    }

    return 0;
}
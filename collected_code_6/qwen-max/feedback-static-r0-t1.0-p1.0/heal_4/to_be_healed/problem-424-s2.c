#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void extract_rear(char *output[], const char *input[], int len) {
    for (int i = 0; i < len; ++i) {
        if (input[i] != NULL && input[i][0] != '\0') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t str_len = strlen(input[i]);
            const char *end_ptr = memchr(input[i], '\0', (1 + str_len) * sizeof(char));
            if (end_ptr == NULL) {
                output[i] = NULL;
                continue;
            }
            str_len = end_ptr - input[i];
            output[i] = (char *)malloc(2 * sizeof(char));
            if (output[i] == NULL) {
                continue;
            }
            output[i][0] = input[i][str_len - 1];
            output[i][1] = '\0';
        } else {
            output[i] = (char *)malloc(sizeof(char));
            if (output[i] == NULL) {
                continue;
            }
            output[i][0] = '\0';
        }
    }
}

int main() {
    const char *strings[] = {"hello", "world", "", NULL};
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
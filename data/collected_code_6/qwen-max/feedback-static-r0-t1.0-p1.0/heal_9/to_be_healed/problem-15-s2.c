#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void split_at_lowercase(const char *input) {
    const char *start = input;
    while (*input) {
        if (!islower((unsigned char)*input)) {
            if (input != start && islower((unsigned char)input[-1])) {
                size_t token_len = input - start;
                char *token = (char *)malloc(token_len + 1);
                if (token != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(token, start, token_len);
                    token[token_len] = '\0';
                    printf("%s\n", token);
                    free(token);
                }
            }
            start = input;
        }
        ++input;
    }
    if (input != start) {
        size_t token_len = input - start;
        char *token = (char *)malloc(token_len + 1);
        if (token != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(token, start, token_len);
            token[token_len] = '\0';
            printf("%s\n", token);
            free(token);
        }
    }
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    split_at_lowercase(argv[1]);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void split_at_lowercase(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    const char *start = input;
    for (size_t i = 0; i <= len; ++i) {
        if (i == len || !islower((unsigned char)input[i])) {
            if (i != 0 && islower((unsigned char)input[i - 1])) {
                size_t token_len = i - (start - input);
                char *token = (char *)malloc(token_len + 1);
                if (token != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(token, start, token_len);
                    token[token_len] = '\0';
                    printf("%s\n", token);
                    free(token);
                }
            }
            start = input + i;
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
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
                char *token = (char *)malloc(i - (start - input) + 1);
                if (token != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(token, start, i - (start - input));
                    token[i - (start - input)] = '\0';
                    printf("%s\n", token);
                    free(token);
                }
            }
            start = input + i;
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    split_at_lowercase(argv[1]);
    return EXIT_SUCCESS;
}
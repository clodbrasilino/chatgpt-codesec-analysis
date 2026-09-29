#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* remove_lowercase_substrings(const char* input) {
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

    size_t r_idx = 0;
    size_t i = 0;

    while (input[i] != '\0') {
        if (islower((unsigned char)input[i])) {
            while (input[i] != '\0' && islower((unsigned char)input[i])) {
                i++;
            }
        } else {
            result[r_idx++] = input[i++];
        }
    }

    result[r_idx] = '\0';

    char* shrunk = (char*)realloc(result, r_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const* const argv[argc]) {
    if (argc < 2) {
        return 1;
    }

    char* filtered = remove_lowercase_substrings(argv[1]);
    if (filtered == NULL) {
        return 1;
    }

    printf("%s\n", filtered);

    free(filtered);
    filtered = NULL;

    return 0;
}
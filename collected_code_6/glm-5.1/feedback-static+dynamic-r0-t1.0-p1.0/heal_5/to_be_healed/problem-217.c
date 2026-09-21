#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strnlen(str, max_len);
    if (len < 2) {
        return '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char char_set[256] = {0};
    /* Possible weaknesses found:
     *  Assignment 'limit=len<256?len:256', assigned value is less than 1
     */
    size_t limit = len < 256 ? len : 256;

    /* Possible weaknesses found:
     *  Condition 'i<limit' is always false
     *  Condition 'i<limit' is always false [knownConditionTrueFalse]
     */
    for (size_t i = 0; i < limit; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] == 1) {
            return c;
        }
        char_set[c] = 1;
    }

    return '\0';
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char result = find_first_repeated(argv[1], MAX_LEN);
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}
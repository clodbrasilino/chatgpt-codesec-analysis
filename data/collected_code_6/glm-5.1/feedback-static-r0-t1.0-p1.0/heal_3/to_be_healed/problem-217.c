#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

#define MAX_LEN 4096

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strnlen(str, max_len);
    if (len < 2) {
        return '\0';
    }

    /* Possible weaknesses found:
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UCHAR_MAX'
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char char_set[UCHAR_MAX + 1] = {0};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] == 1) {
            return c;
        }
        char_set[c] = 1;
    }

    return '\0';
}

int main(int argc, char const * const argv[]) {
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
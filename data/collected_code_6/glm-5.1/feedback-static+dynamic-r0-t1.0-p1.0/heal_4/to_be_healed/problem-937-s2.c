#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

char find_most_common_char(const char *str, size_t length, size_t *max_count) {
    if (str == NULL || max_count == NULL) {
        return '\0';
    }

    size_t counts[UCHAR_MAX + 1] = {0};
    size_t current_max = 0;
    char most_common = '\0';

    for (size_t i = 0; i < length; i++) {
        unsigned char index = (unsigned char)str[i];
        counts[index]++;
    }

    for (size_t i = 0; i < UCHAR_MAX + 1; i++) {
        if (counts[i] > current_max) {
            current_max = counts[i];
            most_common = (char)i;
        }
    }

    *max_count = current_max;
    return most_common;
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t count = 0;
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char result = find_most_common_char(argv[1], strlen(argv[1]), &count);

    if (count > 0) {
        printf("Most common character: '%c' (Count: %zu)\n", result, count);
    } else {
        printf("String is empty.\n");
    }

    return EXIT_SUCCESS;
}
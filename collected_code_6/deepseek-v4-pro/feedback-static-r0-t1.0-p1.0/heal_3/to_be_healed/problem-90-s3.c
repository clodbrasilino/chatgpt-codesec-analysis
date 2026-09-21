#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  'INT_MAX' undeclared (first use in this function)
             *  use of undeclared identifier 'INT_MAX'
             */
            if (current_length < INT_MAX) {
                current_length++;
            } else {
                return max_length;
            }
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        i++;
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    printf("Enter a sentence: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = 0;
    while (len < sizeof(buffer) && buffer[len] != '\0') {
        len++;
    }

    if (len > 0 && buffer[len - 1] != '\n' && len == sizeof(buffer) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == '\0') {
                break;
            }
        }
    }

    size_t pos = 0;
    while (pos < sizeof(buffer) && buffer[pos] != '\0' && buffer[pos] != '\n') {
        pos++;
    }
    if (pos < sizeof(buffer)) {
        buffer[pos] = '\0';
    }

    int result = longest_word_length(buffer);
    printf("Longest word length: %d\n", result);

    return EXIT_SUCCESS;
}
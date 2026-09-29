#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_range(char *str, size_t start, size_t end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void reverse_words(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }

    reverse_range(str, 0, len - 1);

    size_t word_start = 0;
    size_t i = 0;

    while (i <= len) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (i > word_start) {
                reverse_range(str, word_start, i - 1);
            }
            word_start = i + 1;
        }
        i++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t buffer_size = sizeof(buffer);

    if (fgets(buffer, buffer_size, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t len = strnlen(buffer, buffer_size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else if (len == buffer_size - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            /* Possible weaknesses found:
             *  'continue' is redundant since it is the last statement in a loop. [redundantContinue]
             */
            continue;
        }
    }

    reverse_words(buffer, len);

    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}
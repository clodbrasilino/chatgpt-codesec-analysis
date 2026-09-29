#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

void reverse_range(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char *reverse_words(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, 256);
    
    if (len >= 256) {
        return NULL;
    }

    if (len == 0) {
        return str;
    }

    reverse_range(str, str + len - 1);

    char *word_start = str;
    char *p = str;

    while (*p != '\0') {
        if (*p == ' ') {
            reverse_range(word_start, p - 1);
            word_start = p + 1;
        }
        p++;
    }

    reverse_range(word_start, p - 1);

    return str;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[257];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF && c >= 0) {
        }
    }

    reverse_words(input);

    printf("Reversed words: %s\n", input);

    return 0;
}
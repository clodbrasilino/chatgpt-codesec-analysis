#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool match_word_with_internal_z(const char *text) {
    if (text == NULL) {
        return false;
    }

    const char *word_start = text;
    const char *p = text;

    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
            size_t len = (size_t)(p - word_start);
            if (len > 2) {
                const char *q = word_start + 1;
                const char *q_end = p - 1;
                for (; q < q_end; q++) {
                    if (*q == 'z' || *q == 'Z') {
                        return true;
                    }
                }
            }
            word_start = p + 1;
        }
        p++;
    }

    size_t len = (size_t)(p - word_start);
    if (len > 2) {
        const char *q = word_start + 1;
        const char *q_end = p - 1;
        for (; q < q_end; q++) {
            if (*q == 'z' || *q == 'Z') {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    printf("Enter text: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (match_word_with_internal_z(input)) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}
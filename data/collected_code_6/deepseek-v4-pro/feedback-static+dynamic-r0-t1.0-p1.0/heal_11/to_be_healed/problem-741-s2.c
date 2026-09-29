#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

bool all_chars_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    char first = str[0];
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first) {
            return false;
        }
    }
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    int c;
    size_t i = 0;
    bool truncated = false;

    printf("Enter a string: ");

    while (i < sizeof(input) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            break;
        }
        input[i] = (char)c;
        i++;
    }

    if (i == sizeof(input) - 1 && c != '\n' && c != EOF) {
        truncated = true;
        int discard;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((discard = getchar()) != '\n' && discard != EOF) {
        }
    }

    input[i] = '\0';

    if (i == 0 && c == EOF) {
        return 1;
    }

    if (truncated) {
        printf("False\n");
        return 0;
    }

    if (all_chars_same(input)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}
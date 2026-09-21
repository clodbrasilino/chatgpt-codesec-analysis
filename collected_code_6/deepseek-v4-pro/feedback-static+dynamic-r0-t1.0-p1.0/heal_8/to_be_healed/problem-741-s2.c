#include <stdio.h>
#include <string.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

int all_chars_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return 1;
    }

    char first = str[0];
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    int c;
    size_t i = 0;

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
    input[i] = '\0';

    if (i == 0 && c == EOF) {
        return 1;
    }

    if (c != '\n' && c != EOF) {
        int discard;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((discard = getchar()) != '\n' && discard != EOF) {
        }
    }

    if (i == 0) {
        printf("Characters are not all the same.\n");
        return 0;
    }

    if (all_chars_same(input)) {
        printf("All characters are the same.\n");
    } else {
        printf("Characters are not all the same.\n");
    }

    return 0;
}
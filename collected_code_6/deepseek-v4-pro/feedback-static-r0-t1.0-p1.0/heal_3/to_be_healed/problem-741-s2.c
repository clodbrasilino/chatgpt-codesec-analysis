#include <stdio.h>
#include <string.h>

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
    char input[256] = {0};

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (all_chars_same(input)) {
        printf("All characters are the same.\n");
    } else {
        printf("Characters are not all the same.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL) {
        return true;
    }

    if (str[0] == '\0') {
        return true;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 1; i < len; i++) {
        if (str[i] != str[0]) {
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

    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        if (are_all_chars_same(input)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}
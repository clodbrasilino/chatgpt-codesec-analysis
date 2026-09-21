#include <stdio.h>
#include <string.h>

void replace_chars(char *str) {
    for (char *p = str; *p; p++) {
        if (*p == ' ' || *p == ',' || *p == '.') {
            *p = ':';
        }
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        replace_chars(input);
        printf("Modified string: %s\n", input);
    } else {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    return 0;
}
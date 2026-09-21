#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_upper(char *str, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        to_upper(input, strlen(input));
        printf("Upper case: %s\n", input);
    } else {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }
    return 0;
}
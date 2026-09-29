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
        size_t len = strnlen(input, sizeof(input) - 1);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            --len;
        }
        to_upper(input, len);
        printf("Upper case: %s\n", input);
    } else {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }
    return 0;
}
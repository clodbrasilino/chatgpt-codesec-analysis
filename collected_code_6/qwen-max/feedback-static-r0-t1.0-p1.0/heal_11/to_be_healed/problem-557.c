#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        } else if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        if (len < sizeof(input) - 1) {
            toggle_case(input, len);
            printf("Toggled case: %s\n", input);
        } else {
            printf("Input is too long.\n");
        }
    }
    return 0;
}
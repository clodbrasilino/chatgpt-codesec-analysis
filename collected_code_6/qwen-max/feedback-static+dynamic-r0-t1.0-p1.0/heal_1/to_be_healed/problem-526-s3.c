#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int i = 0, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (i == 0 || (i > 0 && str[i - 1] == ' ') || (i < len - 1 && str[i + 1] == ' ')) {
            str[i] = toupper(str[i]);
        }
        if (i > 0 && (i == len - 1 || str[i + 1] == ' ')) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character if present
    capitalize_first_last(input);
    printf("Capitalized: %s\n", input);
    return 0;
}
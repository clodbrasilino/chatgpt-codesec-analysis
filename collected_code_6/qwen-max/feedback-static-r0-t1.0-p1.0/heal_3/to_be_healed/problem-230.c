#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, size_t len, char new_char) {
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            str[i] = new_char;
        }
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    char replacement;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
    }

    printf("Enter the character to replace spaces with: ");
    scanf(" %c", &replacement);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    replace_spaces(input, strlen(input), replacement);

    printf("Modified string: %s\n", input);

    return 0;
}
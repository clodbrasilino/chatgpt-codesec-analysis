#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char new_char) {
    for (size_t i = 0; str[i] != '\0'; i++) {
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
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';
    }

    printf("Enter the character to replace spaces with: ");
    scanf(" %c", &replacement);

    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF);

    replace_spaces(input, replacement);

    printf("Modified string: %s\n", input);

    return 0;
}
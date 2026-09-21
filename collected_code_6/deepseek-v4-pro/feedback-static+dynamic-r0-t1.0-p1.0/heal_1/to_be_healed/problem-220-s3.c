#include <stdio.h>
#include <string.h>

void replace_chars(char *str, int n) {
    int count = 0;
    while (*str && count < n) {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
            count++;
        }
        str++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[256];
    int max_replace;

    printf("Enter a string: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 1;
    }
    text[strcspn(text, "\n")] = '\0';

    printf("Enter maximum replacements: ");
    if (scanf("%d", &max_replace) != 1) {
        return 1;
    }

    replace_chars(text, max_replace);
    printf("Result: %s\n", text);

    return 0;
}
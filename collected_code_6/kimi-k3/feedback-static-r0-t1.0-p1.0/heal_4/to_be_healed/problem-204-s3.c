#include <stdio.h>
#include <string.h>

size_t count_char(const char *str, char ch) {
    size_t count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str != '\0') {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[257];
    char ch;
    size_t result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Enter a character to count: ");
    if (scanf(" %c", &ch) != 1) {
        fprintf(stderr, "Error reading character.\n");
        return 1;
    }

    result = count_char(buffer, ch);
    printf("The character '%c' appears %zu time(s) in the string.\n", ch, result);

    return 0;
}
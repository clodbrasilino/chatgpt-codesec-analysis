#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 256

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
    char buffer[MAX_INPUT_LENGTH + 1];
    char ch;
    size_t result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    size_t len = strcspn(buffer, "\n");
    buffer[len] = '\0';

    printf("Enter a character to count: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error reading character.\n");
        return 1;
    }
    ch = (char)c;

    int extra;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((extra = getchar()) != '\n' && extra != EOF) {
    }

    result = count_char(buffer, ch);
    printf("The character '%c' appears %zu time(s) in the string.\n", ch, result);

    return 0;
}
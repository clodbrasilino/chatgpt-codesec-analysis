#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_vowels(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str != '\0') {
        char c = tolower((unsigned char)*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
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
    char buffer[256];
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    int result = count_vowels(buffer);
    printf("Number of vowels: %d\n", result);
    return 0;
}
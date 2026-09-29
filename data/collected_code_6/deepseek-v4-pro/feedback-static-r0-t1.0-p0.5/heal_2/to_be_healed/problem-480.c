#include <stdio.h>
#include <string.h>
#include <limits.h>

char max_occurring_char(const char *str) {
    int count[UCHAR_MAX + 1] = {0};
    int max_count = 0;
    char max_char = '\0';
    const unsigned char *s = (const unsigned char *)str;

    if (str == NULL || *str == '\0') {
        return '\0';
    }

    while (*s) {
        count[*s]++;
        s++;
    }

    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_char = (char)i;
        }
    }

    return max_char;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1000];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        str[strlen(str) - 1] = '\0';
    }
    else {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
    }

    if (sizeof(str) > 0 && str[0] == '\0') {
        printf("Empty string\n");
        return 0;
    }

    char result = max_occurring_char(str);
    printf("Maximum occurring character: %c\n", result);

    return 0;
}
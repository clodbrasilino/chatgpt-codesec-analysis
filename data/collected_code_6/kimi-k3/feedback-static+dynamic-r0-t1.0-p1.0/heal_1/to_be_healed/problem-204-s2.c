#include <stdio.h>
#include <string.h>

int count_char(const char *str, char ch) {
    int count = 0;
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
    char str[100];
    char ch;
    int result;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    printf("Enter a character to count: ");
    if (scanf(" %c", &ch) != 1) {
        fprintf(stderr, "Error reading character\n");
        return 1;
    }

    result = count_char(str, ch);
    printf("The character '%c' occurs %d time(s) in the string.\n", ch, result);

    return 0;
}
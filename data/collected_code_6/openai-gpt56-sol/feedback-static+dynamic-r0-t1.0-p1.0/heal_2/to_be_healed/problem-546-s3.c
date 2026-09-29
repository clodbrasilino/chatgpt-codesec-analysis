#include <stdio.h>
#include <stddef.h>

const char *find_last_char(const char *str, int ch)
{
    const char *last = NULL;
    unsigned char target = (unsigned char)ch;

    if (str == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*str == target) {
            last = str;
        }
    } while (*str++ != '\0');

    return last;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    const char *result;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = getchar();
    if (ch == EOF) {
        fputs("Failed to read the character.\n", stderr);
        return 1;
    }

    result = find_last_char(input, ch);

    if (result != NULL) {
        printf("%td\n", result - input);
    } else {
        puts("Character not found.");
    }

    return 0;
}
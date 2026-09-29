#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

size_t count_lowercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (islower((unsigned char)*string) != 0) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];

    if (fgets(string, sizeof string, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    printf("%zu\n", count_lowercase(string));
    return 0;
}
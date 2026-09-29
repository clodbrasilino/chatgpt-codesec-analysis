#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

static size_t count_lowercase(const char *string)
{
    size_t count = 0U;

    if (string == NULL) {
        return 0U;
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
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    if (printf("%zu\n", count_lowercase(input)) < 0) {
        return 1;
    }

    return 0;
}
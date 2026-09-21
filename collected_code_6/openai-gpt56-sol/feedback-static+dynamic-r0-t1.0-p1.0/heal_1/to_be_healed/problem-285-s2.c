#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_pattern(const char *string)
{
    size_t index = 0U;
    size_t b_count = 0U;

    if (string == NULL || string[index] != 'a') {
        return false;
    }

    ++index;

    while (string[index] == 'b' && b_count < 3U) {
        ++index;
        ++b_count;
    }

    return b_count >= 2U && string[index] == '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    size_t length = 0U;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        return 1;
    }

    if (matches_pattern(input)) {
        if (puts("Match") == EOF) {
            return 1;
        }
    } else {
        if (puts("No match") == EOF) {
            return 1;
        }
    }

    return 0;
}
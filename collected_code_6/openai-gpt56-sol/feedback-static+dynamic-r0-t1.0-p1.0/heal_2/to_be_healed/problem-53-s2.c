#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    length = strcspn(input, "\r\n");

    if (input[length] != '\0') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        return 1;
    }

    if (first_and_last_are_equal(input, length)) {
        puts("Equal");
    } else {
        puts("Not equal");
    }

    return 0;
}
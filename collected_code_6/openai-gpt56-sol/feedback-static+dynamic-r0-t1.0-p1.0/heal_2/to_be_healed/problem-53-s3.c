#include <stdio.h>
#include <string.h>

#define STRING_CAPACITY 1024U

static int first_and_last_equal(const char *string, size_t length)
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
    char string[STRING_CAPACITY];
    size_t length;

    if (fgets(string, (int)sizeof string, stdin) == NULL) {
        return 1;
    }

    length = strnlen(string, sizeof string);

    if (length == sizeof string) {
        return 1;
    }

    if (length > 0U && string[length - 1U] == '\n') {
        string[--length] = '\0';
    } else if (length == sizeof string - 1U) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character == EOF) {
            return 1;
        }
    }

    puts(first_and_last_equal(string, length) ? "Equal" : "Not equal");
    return 0;
}
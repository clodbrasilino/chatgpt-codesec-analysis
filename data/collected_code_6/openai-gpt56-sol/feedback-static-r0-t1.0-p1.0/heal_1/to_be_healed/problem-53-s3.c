#include <stdio.h>
#include <string.h>

static int first_and_last_equal(const char *string)
{
    size_t length;

    if (string == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);
    return length > 0U && string[0] == string[length - 1U];
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];
    size_t length;

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);
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

        if (character != '\n') {
            return 1;
        }
    }

    puts(first_and_last_equal(string) ? "Equal" : "Not equal");
    return 0;
}
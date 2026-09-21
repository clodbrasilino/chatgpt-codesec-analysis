#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2 &&
           string[0] == 'a' &&
           string[length - 1] == 'b';
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                (argc > 0 && argv != NULL && argv[0] != NULL)
                    ? argv[0]
                    : "program");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const size_t length = strlen(argv[1]);

    puts(matches_pattern(argv[1], length) ? "Match" : "No match");
    return 0;
}
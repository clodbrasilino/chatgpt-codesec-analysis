#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string)
{
    if (string == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const size_t length = strlen(string);

    return length >= 2 && string[0] == 'a' && string[length - 1] == 'b';
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                (argc > 0 && argv != NULL && argv[0] != NULL)
                    ? argv[0]
                    : "program");
        return 1;
    }

    puts(matches_pattern(argv[1]) ? "Match" : "No match");

    return 0;
}
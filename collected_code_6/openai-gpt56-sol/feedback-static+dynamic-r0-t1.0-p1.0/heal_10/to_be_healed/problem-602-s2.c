#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int first_repeated_character(FILE *stream, unsigned char *result)
{
    bool seen[UCHAR_MAX + 1] = { false };
    int character;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        unsigned char value = (unsigned char)character;

        if (seen[value]) {
            *result = value;
            return 1;
        }

        seen[value] = true;
    }

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    unsigned char repeated;
    int status = first_repeated_character(stdin, &repeated);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        if (puts("No repeated character") == EOF) {
            return EXIT_FAILURE;
        }
    } else if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
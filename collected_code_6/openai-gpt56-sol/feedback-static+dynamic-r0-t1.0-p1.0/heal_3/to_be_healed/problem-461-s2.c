#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int count_uppercase_stream(FILE *stream, size_t *count)
{
    int character;

    if (stream == NULL || count == NULL) {
        return -1;
    }

    *count = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (isupper((unsigned char)character)) {
            ++(*count);
        }
    }

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    size_t uppercase_count;

    if (count_uppercase_stream(stdin, &uppercase_count) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", uppercase_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_uppercase_stream(FILE *stream, int *read_error)
{
    size_t count = 0;
    int ch;

    if (read_error != NULL) {
        *read_error = 0;
    }

    if (stream == NULL) {
        if (read_error != NULL) {
            *read_error = 1;
        }
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        if (isupper((unsigned char)ch) != 0) {
            if (count == SIZE_MAX) {
                if (read_error != NULL) {
                    *read_error = 1;
                }
                return 0;
            }
            ++count;
        }
    }

    if (ferror(stream) != 0 && read_error != NULL) {
        *read_error = 1;
    }

    return count;
}

int main(void)
{
    int read_error = 0;
    size_t count = count_uppercase_stream(stdin, &read_error);

    if (read_error != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
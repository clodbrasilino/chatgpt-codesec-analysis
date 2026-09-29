#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t max_uppercase_run(FILE *stream, int *error)
{
    size_t maximum = 0;
    size_t current = 0;
    int ch;

    if (error != NULL) {
        *error = 0;
    }

    if (stream == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        if (isupper((unsigned char)ch)) {
            ++current;
            if (current > maximum) {
                maximum = current;
            }
        } else {
            current = 0;
        }
    }

    if (ferror(stream) && error != NULL) {
        *error = 1;
    }

    return maximum;
}

int main(void)
{
    int error;
    size_t maximum = max_uppercase_run(stdin, &error);

    if (error) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
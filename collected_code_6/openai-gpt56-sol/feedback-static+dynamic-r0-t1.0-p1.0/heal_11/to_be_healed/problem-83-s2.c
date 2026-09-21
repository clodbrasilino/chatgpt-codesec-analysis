#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int add_characters(FILE *stream, unsigned char *result)
{
    unsigned int sum = 0U;
    int character;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            break;
        }

        sum = (sum + (unsigned int)(unsigned char)character)
            % ((unsigned int)UCHAR_MAX + 1U);
    }

    if (ferror(stream)) {
        return -1;
    }

    *result = (unsigned char)sum;
    return 0;
}

int main(void)
{
    unsigned char result;

    if (add_characters(stdin, &result) != 0) {
        perror("stdin");
        return EXIT_FAILURE;
    }

    if (fputc((int)result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        perror("stdout");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
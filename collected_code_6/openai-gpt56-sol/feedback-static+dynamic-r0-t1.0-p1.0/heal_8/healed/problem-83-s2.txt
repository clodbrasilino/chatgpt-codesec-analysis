#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned char add_characters(FILE *stream, int *status)
{
    unsigned int sum = 0U;
    int character;

    while ((character = fgetc(stream)) != '\n' && character != EOF) {
        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (character == EOF && ferror(stream)) {
        *status = -1;
    } else {
        *status = 0;
    }

    return (unsigned char)sum;
}

int main(void)
{
    int status;
    unsigned char result = add_characters(stdin, &status);

    if (status != 0) {
        perror("stdin");
        return EXIT_FAILURE;
    }

    if (fputc((int)result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        perror("stdout");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
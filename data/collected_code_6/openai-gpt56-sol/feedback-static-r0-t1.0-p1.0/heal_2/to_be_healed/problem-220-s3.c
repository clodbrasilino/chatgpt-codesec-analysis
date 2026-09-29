#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

size_t replace_delimiters(char *string, size_t maximum)
{
    size_t replaced = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0' && replaced < maximum) {
        if (*string == ' ' || *string == ',' || *string == '.') {
            *string = ':';
            ++replaced;
        }
        ++string;
    }

    return replaced;
}

static int discard_line(FILE *stream)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t maximum;
    int result;
    int character;

    if (printf("Maximum replacements: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    result = scanf("%zu", &maximum);
    if (result != 1) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = fgetc(stdin);
    if (character != '\n' && character != EOF) {
        if (discard_line(stdin) != 0) {
            return EXIT_FAILURE;
        }
    } else if (character == EOF && ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("Text: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    replace_delimiters(line, maximum);

    if (fputs(line, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
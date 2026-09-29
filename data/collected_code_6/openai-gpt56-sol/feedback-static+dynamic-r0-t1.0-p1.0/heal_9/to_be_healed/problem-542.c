#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int replace_delimiters(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (char *p = string; *p != '\0'; ++p) {
        if (*p == ' ' || *p == ',' || *p == '.') {
            *p = ':';
        }
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const size_t length = strlen(argv[1]);

    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too long\n");
        return EXIT_FAILURE;
    }

    char *string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(string, argv[1], length + 1);

    if (replace_delimiters(string) != 0) {
        fprintf(stderr, "Replacement failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", string) < 0) {
        fprintf(stderr, "Output failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}
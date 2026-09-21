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

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t maximum;
    int result;

    if (printf("Maximum replacements: ") < 0) {
        return EXIT_FAILURE;
    }

    result = scanf("%zu", &maximum);
    if (result != 1) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    result = getchar();
    if (result != '\n' && result != EOF) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((result = getchar()) != '\n' && result != EOF) {
        }
    }

    if (printf("Text: ") < 0) {
        return EXIT_FAILURE;
    }

    if (getline(&line, &capacity, stdin) == -1) {
        free(line);
        return EXIT_FAILURE;
    }

    replace_delimiters(line, maximum);

    if (fputs(line, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}
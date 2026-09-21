#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *remove_non_alnum(char *str);

char *remove_non_alnum(char *str)
{
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    size_t read;
    size_t write;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    write = 0;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (read = 0; read < len && str[read] != '\0'; read++) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (isalnum((unsigned char)str[read])) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            str[write] = str[read];
            write++;
        }
    }
    str[write] = '\0';

    return str;
}

int main(void)
{
    char input[] = "Hello, World! 123 #$%^ test_case-42";
    char *result;

    result = remove_non_alnum(input);
    if (result == NULL) {
        fprintf(stderr, "Error: NULL input string\n");
        return EXIT_FAILURE;
    }

    if (printf("Result: %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
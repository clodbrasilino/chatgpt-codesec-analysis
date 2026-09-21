#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_character(char *string, unsigned char character)
{
    char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        if ((unsigned char)*source != character) {
            *destination++ = *source;
        }
        source++;
    }

    *destination = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;
    int input;
    int status = EXIT_FAILURE;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        if (ferror(stdin)) {
            clearerr(stdin);
        }
        goto cleanup;
    }

    while (length > 0 &&
           (string[length - 1] == '\n' || string[length - 1] == '\r')) {
        string[--length] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input = fgetc(stdin);
    if (input == EOF) {
        if (ferror(stdin)) {
            goto cleanup;
        }
        status = EXIT_SUCCESS;
        goto cleanup;
    }

    remove_character(string, (unsigned char)input);

    if (puts(string) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(string);
    return status;
}
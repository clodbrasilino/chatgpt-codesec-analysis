#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_character(char *string, unsigned char character)
{
    char *source = string;
    char *destination = string;

    if (string == NULL) {
        return;
    }

    while (*source != '\0') {
        if ((unsigned char)*source != character) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;
    int input;
    int result = EXIT_FAILURE;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        goto cleanup;
    }

    if (length > 0 && string[length - 1] == '\n') {
        string[--length] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input = fgetc(stdin);
    if (input == EOF) {
        goto cleanup;
    }

    remove_character(string, (unsigned char)input);

    if (puts(string) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(string);
    return result;
}
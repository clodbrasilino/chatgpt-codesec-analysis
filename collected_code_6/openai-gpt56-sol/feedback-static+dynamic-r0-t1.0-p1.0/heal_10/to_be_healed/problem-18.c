#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_characters(char *string, const char *characters)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char remove_table[UCHAR_MAX + 1] = {0};
    const unsigned char *current;
    const unsigned char *source;
    unsigned char *destination;

    if (string == NULL || characters == NULL) {
        return;
    }

    for (current = (const unsigned char *)characters; *current != '\0'; ++current) {
        remove_table[*current] = 1;
    }

    source = (const unsigned char *)string;
    destination = (unsigned char *)string;

    while (*source != '\0') {
        if (remove_table[*source] == 0) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

static void trim_line_ending(char *string, ssize_t *length)
{
    if (string == NULL || length == NULL || *length < 0) {
        return;
    }

    while (*length > 0) {
        unsigned char character = (unsigned char)string[*length - 1];

        if (character != '\n' && character != '\r') {
            break;
        }

        --(*length);
        string[*length] = '\0';
    }
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_capacity = 0;
    size_t second_capacity = 0;
    ssize_t first_length;
    ssize_t second_length;
    int status = EXIT_FAILURE;

    first_length = getline(&first, &first_capacity, stdin);
    if (first_length < 0) {
        goto cleanup;
    }

    second_length = getline(&second, &second_capacity, stdin);
    if (second_length < 0) {
        goto cleanup;
    }

    trim_line_ending(first, &first_length);
    trim_line_ending(second, &second_length);
    remove_characters(first, second);

    if (puts(first) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return status;
}
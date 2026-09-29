#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_characters(char *string, const char *characters)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char remove_table[256] = {0};
    const unsigned char *source;
    unsigned char *destination;
    const unsigned char *current;

    if (string == NULL || characters == NULL) {
        return;
    }

    current = (const unsigned char *)characters;
    while (*current != '\0') {
        remove_table[*current++] = 1;
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
    if (string == NULL || length == NULL) {
        return;
    }

    while (*length > 0 &&
           (string[*length - 1] == '\n' || string[*length - 1] == '\r')) {
        string[--(*length)] = '\0';
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

    if (printf("%s\n", first) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(first);
    free(second);
    return status;
}
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
    char *source = string;
    char *destination = string;

    while (*characters != '\0') {
        remove_table[(unsigned char)*characters++] = 1;
    }

    while (*source != '\0') {
        unsigned char value = (unsigned char)*source++;

        if (remove_table[value] == 0) {
            *destination++ = (char)value;
        }
    }

    *destination = '\0';
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

    if (first_length > 0 && first[(size_t)first_length - 1] == '\n') {
        first[(size_t)first_length - 1] = '\0';
    }

    if (second_length > 0 && second[(size_t)second_length - 1] == '\n') {
        second[(size_t)second_length - 1] = '\0';
    }

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
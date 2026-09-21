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
    char *source;
    char *destination;

    if (string == NULL || characters == NULL) {
        return;
    }

    for (; *characters != '\0'; ++characters) {
        remove_table[(unsigned char)*characters] = 1;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        unsigned char value = (unsigned char)*source++;

        if (remove_table[value] == 0) {
            *destination++ = (char)value;
        }
    }

    *destination = '\0';
}

static void remove_trailing_newline(char *string, ssize_t length)
{
    if (string != NULL && length > 0 && string[(size_t)length - 1] == '\n') {
        string[(size_t)length - 1] = '\0';
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

    remove_trailing_newline(first, first_length);
    remove_trailing_newline(second, second_length);
    remove_characters(first, second);

    if (printf("%s\n", first) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return status;
}
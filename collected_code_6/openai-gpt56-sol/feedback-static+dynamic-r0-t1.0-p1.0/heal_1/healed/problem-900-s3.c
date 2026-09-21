#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(const char *prompt, char **line, size_t *capacity)
{
    if (prompt == NULL || line == NULL || capacity == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    ssize_t length = getline(line, capacity, stdin);
    if (length < 0) {
        return false;
    }

    if (length > 0 && (*line)[length - 1] == '\n') {
        (*line)[--length] = '\0';
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        (*line)[length - 1] = '\0';
    }

    return true;
}

static bool string_starts_with_number(const char *string, const char *number)
{
    if (string == NULL || number == NULL || number[0] == '\0') {
        return false;
    }

    while (*number != '\0') {
        if (*string == '\0' || *string != *number) {
            return false;
        }

        ++string;
        ++number;
    }

    return true;
}

int main(void)
{
    char *string = NULL;
    char *number = NULL;
    size_t string_capacity = 0;
    size_t number_capacity = 0;
    int status = EXIT_FAILURE;

    if (!read_line("Enter a string: ", &string, &string_capacity)) {
        goto cleanup;
    }

    if (!read_line("Enter the starting number: ", &number, &number_capacity)) {
        goto cleanup;
    }

    if (number[0] == '\0') {
        if (fputs("The number must not be empty.\n", stderr) == EOF) {
            goto cleanup;
        }
        goto cleanup;
    }

    if (string_starts_with_number(string, number)) {
        if (printf("The string starts with %s.\n", number) < 0) {
            goto cleanup;
        }
    } else {
        if (printf("The string does not start with %s.\n", number) < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(number);
    free(string);
    return status;
}
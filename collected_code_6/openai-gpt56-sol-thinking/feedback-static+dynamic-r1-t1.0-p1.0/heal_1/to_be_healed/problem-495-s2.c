#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void set_error_message(char *buffer, size_t size, const char *message)
{
    if (buffer != NULL && size > 0) {
        (void)snprintf(buffer, size, "%s", message);
    }
}

int remove_lowercase_substrings(char *string, char *error, size_t error_size)
{
    regex_t regex;
    regmatch_t match;
    char *position;
    int result;

    if (string == NULL) {
        set_error_message(error, error_size, "Invalid string argument");
        return -1;
    }

    if (error != NULL && error_size > 0) {
        error[0] = '\0';
    }

    result = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (result != 0) {
        if (error != NULL && error_size > 0) {
            (void)regerror(result, &regex, error, error_size);
        }
        return -1;
    }

    position = string;

    for (;;) {
        size_t remaining;
        size_t start;
        size_t end;

        result = regexec(&regex, position, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            if (error != NULL && error_size > 0) {
                (void)regerror(result, &regex, error, error_size);
            }
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        remaining = strlen(position);

        if (match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            set_error_message(error, error_size, "Invalid regular expression match");
            regfree(&regex);
            return -1;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        memmove(position + start, position + end, remaining - end + 1);
        position += start;
    }

    regfree(&regex);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *string;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error[256];
    size_t length;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(argv[1]);

    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Unable to allocate memory\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(string, argv[1], length + 1);

    if (remove_lowercase_substrings(string, error, sizeof(error)) != 0) {
        fprintf(stderr, "Error: %s\n", error);
        free(string);
        return EXIT_FAILURE;
    }

    printf("%s\n", string);
    free(string);

    return EXIT_SUCCESS;
}
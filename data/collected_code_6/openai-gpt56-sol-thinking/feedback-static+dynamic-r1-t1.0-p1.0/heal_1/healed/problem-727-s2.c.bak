#include <errno.h>
#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_non_alnum(const char *input, char **output)
{
    static const char pattern[] = "[^[:alnum:]]+";
    regex_t regex;
    regmatch_t match;
    char *result;
    char *destination;
    const char *cursor;
    size_t input_length;
    size_t consumed = 0;
    int status;

    if (input == NULL || output == NULL) {
        errno = EINVAL;
        return -1;
    }

    *output = NULL;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        errno = status == REG_ESPACE ? ENOMEM : EINVAL;
        return -1;
    }

    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        regfree(&regex);
        errno = EOVERFLOW;
        return -1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        regfree(&regex);
        errno = ENOMEM;
        return -1;
    }

    cursor = input;
    destination = result;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t match_start;
        size_t match_end;
        size_t remaining = input_length - consumed;

        if (match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            free(result);
            regfree(&regex);
            errno = EIO;
            return -1;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        memcpy(destination, cursor, match_start);
        destination += match_start;
        cursor += match_end;
        consumed += match_end;
    }

    if (status != REG_NOMATCH) {
        free(result);
        regfree(&regex);
        errno = status == REG_ESPACE ? ENOMEM : EIO;
        return -1;
    }

    {
        size_t remaining = input_length - consumed;

        memcpy(destination, cursor, remaining);
        destination += remaining;
        *destination = '\0';
    }

    regfree(&regex);
    *output = result;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *filtered = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (remove_non_alnum(argv[1], &filtered) != 0) {
        perror("remove_non_alnum");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", filtered) < 0) {
        free(filtered);
        return EXIT_FAILURE;
    }

    free(filtered);
    return EXIT_SUCCESS;
}
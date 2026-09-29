#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_with_colons(char *string)
{
    const char pattern[] = "[ ,.]";
    regex_t regex;
    regmatch_t match;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_message[256];
    char *cursor;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        regerror(result, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return -1;
    }

    cursor = string;

    for (;;) {
        size_t remaining;
        size_t start;
        size_t end;

        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            regerror(result, &regex, error_message, sizeof(error_message));
            fprintf(stderr, "Regex matching failed: %s\n", error_message);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        remaining = strlen(cursor);

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (start >= remaining || end > remaining) {
            regfree(&regex);
            return -1;
        }

        cursor[start] = ':';
        cursor += end;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s \"string\"\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (replace_with_colons(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
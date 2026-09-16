#include <ctype.h>
#include <errno.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_case_to_camel_case(const char *input)
{
    static const char pattern[] = "_([A-Za-z0-9])";
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    char *result;
    char *destination;
    size_t length;
    size_t remaining;
    int status;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    length = strlen(input);
    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        errno = EINVAL;
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    destination = result;
    remaining = length;

    while ((status = regexec(&regex, cursor, 2, matches, 0)) == 0) {
        size_t match_start;
        size_t match_end;
        size_t capture_start;
        size_t capture_end;

        if (matches[0].rm_so < 0 || matches[0].rm_eo < matches[0].rm_so ||
            matches[1].rm_so < 0 || matches[1].rm_eo < matches[1].rm_so) {
            free(result);
            regfree(&regex);
            errno = EINVAL;
            return NULL;
        }

        match_start = (size_t)matches[0].rm_so;
        match_end = (size_t)matches[0].rm_eo;
        capture_start = (size_t)matches[1].rm_so;
        capture_end = (size_t)matches[1].rm_eo;

        if (match_end > remaining || capture_start < match_start ||
            capture_end > match_end || capture_end - capture_start != 1) {
            free(result);
            regfree(&regex);
            errno = EINVAL;
            return NULL;
        }

        memcpy(destination, cursor, match_start);
        destination += match_start;
        *destination++ = (char)toupper((unsigned char)cursor[capture_start]);

        cursor += match_end;
        remaining -= match_end;
    }

    if (status != REG_NOMATCH) {
        free(result);
        regfree(&regex);
        errno = EINVAL;
        return NULL;
    }

    memcpy(destination, cursor, remaining + 1);
    regfree(&regex);

    return result;
}

int main(int argc, char *argv[])
{
    char *camel_case;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    camel_case = snake_case_to_camel_case(argv[1]);
    if (camel_case == NULL) {
        perror("snake_case_to_camel_case");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", camel_case) < 0) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}
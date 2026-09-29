#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <regex.h>

static char *copy_match(const char *src, size_t len)
{
    char *dest;

    if (src == NULL || len == 0 || len == SIZE_MAX) {
        return NULL;
    }

    dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }

    memmove(dest, src, len);
    dest[len] = '\0';
    return dest;
}

int extract_max_number(const char *input, long *result)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    long max_value = LONG_MIN;
    int found = 0;
    int rc;

    if (input == NULL || result == NULL) {
        return -1;
    }

    rc = regcomp(&regex, "-?[0-9]+", REG_EXTENDED);
    if (rc != 0) {
        return -1;
    }

    cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t len;
        long value;
        char *endptr;
        char *buffer;

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        len = (size_t)(match.rm_eo - match.rm_so);

        buffer = copy_match(cursor + match.rm_so, len);
        if (buffer == NULL) {
            regfree(&regex);
            return -1;
        }

        errno = 0;
        value = strtol(buffer, &endptr, 10);
        if (errno == ERANGE || endptr == buffer || *endptr != '\0') {
            free(buffer);
            regfree(&regex);
            return -1;
        }

        free(buffer);

        if (!found || value > max_value) {
            max_value = value;
            found = 1;
        }

        cursor += match.rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);

    if (!found) {
        return -1;
    }

    *result = max_value;
    return 0;
}

int main(void)
{
    const char *test1 = "abc 42 def -17 ghi 305 jkl 7";
    const char *test2 = "no numbers here";
    long max = 0;

    if (extract_max_number(test1, &max) == 0) {
        printf("Max value in \"%s\" is %ld\n", test1, max);
    } else {
        fprintf(stderr, "Failed to extract number from \"%s\"\n", test1);
    }

    if (extract_max_number(test2, &max) == 0) {
        printf("Max value in \"%s\" is %ld\n", test2, max);
    } else {
        fprintf(stderr, "Failed to extract number from \"%s\"\n", test2);
    }

    return EXIT_SUCCESS;
}
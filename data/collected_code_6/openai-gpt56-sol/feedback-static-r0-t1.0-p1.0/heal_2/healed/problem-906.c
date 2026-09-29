#include <errno.h>
#include <limits.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_match(const char *source, const regmatch_t *match,
                       long minimum, long maximum, int *output)
{
    size_t start;
    size_t length;
    char *buffer;
    char *end;
    long value;

    if (source == NULL || match == NULL || output == NULL ||
        match->rm_so < 0 || match->rm_eo < match->rm_so) {
        return -1;
    }

    start = (size_t)match->rm_so;
    length = (size_t)(match->rm_eo - match->rm_so);

    if (length == 0 || length == SIZE_MAX || start > SIZE_MAX - length) {
        return -1;
    }

    buffer = malloc(length + 1);
    if (buffer == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        char c = source[start + i];

        if (c < '0' || c > '9') {
            free(buffer);
            return -1;
        }

        buffer[i] = c;
    }
    buffer[length] = '\0';

    errno = 0;
    value = strtol(buffer, &end, 10);

    if (errno == ERANGE || end != buffer + length ||
        value < minimum || value > maximum ||
        value < INT_MIN || value > INT_MAX) {
        free(buffer);
        return 1;
    }

    *output = (int)value;
    free(buffer);
    return 0;
}

static int extract_date_from_url(const char *url, int *year,
                                 int *month, int *day)
{
    static const char pattern[] =
        "([^0-9]|^)([0-9]{4})[-/]([0-9]{2})[-/]([0-9]{2})([^0-9]|$)";
    regex_t regex;
    regmatch_t matches[6];
    int parsed_year;
    int parsed_month;
    int parsed_day;
    int result;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, url,
                     sizeof(matches) / sizeof(matches[0]), matches, 0);
    if (result != 0) {
        regfree(&regex);
        return result == REG_NOMATCH ? 1 : -1;
    }

    result = parse_match(url, &matches[2], 1, 9999, &parsed_year);
    if (result == 0) {
        result = parse_match(url, &matches[3], 1, 12, &parsed_month);
    }
    if (result == 0) {
        result = parse_match(url, &matches[4], 1, 31, &parsed_day);
    }

    regfree(&regex);

    if (result != 0) {
        return result;
    }

    *year = parsed_year;
    *month = parsed_month;
    *day = parsed_day;

    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    const char *url;
    int year;
    int month;
    int day;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <url>\n", program_name);
        return EXIT_FAILURE;
    }

    url = argv[1];

    if (extract_date_from_url(url, &year, &month, &day) != 0) {
        fprintf(stderr, "Unable to extract a valid date from the URL\n");
        return EXIT_FAILURE;
    }

    printf("Year: %04d\nMonth: %02d\nDate: %02d\n", year, month, day);
    return EXIT_SUCCESS;
}
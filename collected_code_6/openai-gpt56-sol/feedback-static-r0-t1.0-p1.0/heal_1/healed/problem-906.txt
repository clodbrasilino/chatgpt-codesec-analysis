#include <errno.h>
#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_match(const char *source, const regmatch_t *match,
                       long minimum, long maximum, int *output)
{
    char buffer[32];
    size_t length;
    char *end;
    long value;

    if (source == NULL || match == NULL || output == NULL ||
        match->rm_so < 0 || match->rm_eo < match->rm_so) {
        return -1;
    }

    length = (size_t)(match->rm_eo - match->rm_so);
    if (length == 0 || length >= sizeof(buffer)) {
        return -1;
    }

    if ((size_t)match->rm_so > SIZE_MAX - length) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        char c = source[(size_t)match->rm_so + i];

        if (c < '0' || c > '9') {
            return -1;
        }
        buffer[i] = c;
    }
    buffer[length] = '\0';

    errno = 0;
    value = strtol(buffer, &end, 10);
    if (errno == ERANGE || end != buffer + length ||
        value < minimum || value > maximum || value > INT_MAX) {
        return 1;
    }

    *output = (int)value;
    return 0;
}

static int extract_date_from_url(const char *url, int *year, int *month, int *day)
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

    result = regexec(&regex, url, sizeof(matches) / sizeof(matches[0]),
                     matches, 0);
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
    int year;
    int month;
    int day;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (extract_date_from_url(argv[1], &year, &month, &day) != 0) {
        fprintf(stderr, "Unable to extract a valid date from the URL\n");
        return EXIT_FAILURE;
    }

    printf("Year: %04d\nMonth: %02d\nDate: %02d\n", year, month, day);
    return EXIT_SUCCESS;
}
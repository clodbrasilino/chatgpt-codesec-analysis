#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 4
#define MAX_URL_LENGTH 2048
#define YEAR_DIGITS 4
#define MONTH_DIGITS 2
#define DAY_DIGITS 2

static int copy_match(const char *url, regmatch_t match, size_t url_len,
                      size_t expected_len, char **out)
{
    size_t len;
    size_t capacity;
    size_t start;
    size_t end;
    size_t i;
    char *buf;

    *out = NULL;

    if (match.rm_so < 0 || match.rm_eo <= match.rm_so ||
        (size_t)match.rm_so >= url_len ||
        (size_t)match.rm_eo > url_len) {
        return -1;
    }

    start = (size_t)match.rm_so;
    end = (size_t)match.rm_eo;
    len = end - start;

    if (len != expected_len) {
        return -1;
    }

    if (len > url_len - start) {
        return -1;
    }

    capacity = expected_len + 1;
    if (capacity <= expected_len) {
        return -1;
    }

    buf = malloc(capacity);
    if (buf == NULL) {
        return -1;
    }

    if (len >= capacity) {
        free(buf);
        return -1;
    }

    for (i = 0; i < len; i++) {
        buf[i] = url[start + i];
    }
    buf[len] = '\0';
    *out = buf;
    return 0;
}

static int parse_component(const char *s, size_t expected_len, int *value)
{
    int result = 0;
    size_t i;

    for (i = 0; i < expected_len; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return -1;
        }
        result = result * 10 + (s[i] - '0');
    }

    if (s[expected_len] != '\0') {
        return -1;
    }

    *value = result;
    return 0;
}

int extract_date_from_url(const char *url, char **year, char **month, char **day)
{
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    const char *pattern = "([0-9]{4})/([0-9]{2})/([0-9]{2})";
    size_t url_len;
    int status;
    int year_value;
    int month_value;
    int day_value;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    *year = NULL;
    *month = NULL;
    *day = NULL;

    url_len = strnlen(url, MAX_URL_LENGTH);
    if (url_len == 0 || url_len >= MAX_URL_LENGTH) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, url, MAX_MATCHES, matches, 0);
    if (status != 0) {
        regfree(&regex);
        return -1;
    }

    if (copy_match(url, matches[1], url_len, YEAR_DIGITS, year) != 0 ||
        copy_match(url, matches[2], url_len, MONTH_DIGITS, month) != 0 ||
        copy_match(url, matches[3], url_len, DAY_DIGITS, day) != 0) {
        free(*year);
        free(*month);
        free(*day);
        *year = NULL;
        *month = NULL;
        *day = NULL;
        regfree(&regex);
        return -1;
    }

    regfree(&regex);

    if (parse_component(*year, YEAR_DIGITS, &year_value) != 0 ||
        parse_component(*month, MONTH_DIGITS, &month_value) != 0 ||
        parse_component(*day, DAY_DIGITS, &day_value) != 0 ||
        year_value < 1 ||
        month_value < 1 || month_value > 12 ||
        day_value < 1 || day_value > 31) {
        free(*year);
        free(*month);
        free(*day);
        *year = NULL;
        *month = NULL;
        *day = NULL;
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *url = "https://example.com/2024/01/15/article";
    char *year = NULL;
    char *month = NULL;
    char *day = NULL;

    if (extract_date_from_url(url, &year, &month, &day) != 0) {
        fprintf(stderr, "Failed to extract date from URL\n");
        return EXIT_FAILURE;
    }

    printf("Year: %s\n", year);
    printf("Month: %s\n", month);
    printf("Day: %s\n", day);

    free(year);
    free(month);
    free(day);

    return EXIT_SUCCESS;
}
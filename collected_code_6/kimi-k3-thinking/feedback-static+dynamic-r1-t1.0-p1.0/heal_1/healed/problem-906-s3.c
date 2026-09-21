#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DATE_PATTERN "([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})"
#define MATCH_COUNT 4
#define YEAR_BUF_SIZE 5
#define MONTH_BUF_SIZE 3
#define DAY_BUF_SIZE 3

typedef struct {
    int year;
    int month;
    int day;
} DateComponents;

static int parse_component(const char *buf, int *out)
{
    char *endptr = NULL;
    long value;

    if (buf == NULL || out == NULL) {
        return -1;
    }

    value = strtol(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0') {
        return -1;
    }

    *out = (int)value;
    return 0;
}

static int copy_match(char *dest, size_t dest_size, const char *src, regoff_t len)
{
    if (dest == NULL || src == NULL || len < 0) {
        return -1;
    }

    if ((size_t)len >= dest_size) {
        return -1;
    }

    memcpy(dest, src, (size_t)len);
    dest[len] = '\0';
    return 0;
}

static int extract_date_from_url(const char *url, DateComponents *date)
{
    regex_t regex;
    regmatch_t matches[MATCH_COUNT];
    char year_buf[YEAR_BUF_SIZE];
    char month_buf[MONTH_BUF_SIZE];
    char day_buf[DAY_BUF_SIZE];
    regoff_t year_len;
    regoff_t month_len;
    regoff_t day_len;
    int ret = -1;

    if (url == NULL || date == NULL) {
        return -1;
    }

    if (regcomp(&regex, DATE_PATTERN, REG_EXTENDED) != 0) {
        return -1;
    }

    if (regexec(&regex, url, MATCH_COUNT, matches, 0) != 0) {
        goto cleanup;
    }

    if (matches[1].rm_so < 0 || matches[1].rm_eo < matches[1].rm_so ||
        matches[2].rm_so < 0 || matches[2].rm_eo < matches[2].rm_so ||
        matches[3].rm_so < 0 || matches[3].rm_eo < matches[3].rm_so) {
        goto cleanup;
    }

    year_len = matches[1].rm_eo - matches[1].rm_so;
    month_len = matches[2].rm_eo - matches[2].rm_so;
    day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len != 4 || month_len < 1 || month_len > 2 ||
        day_len < 1 || day_len > 2) {
        goto cleanup;
    }

    if (copy_match(year_buf, sizeof(year_buf), url + matches[1].rm_so, year_len) != 0 ||
        copy_match(month_buf, sizeof(month_buf), url + matches[2].rm_so, month_len) != 0 ||
        copy_match(day_buf, sizeof(day_buf), url + matches[3].rm_so, day_len) != 0) {
        goto cleanup;
    }

    if (parse_component(year_buf, &date->year) != 0 ||
        parse_component(month_buf, &date->month) != 0 ||
        parse_component(day_buf, &date->day) != 0) {
        goto cleanup;
    }

    if (date->year < 1000 || date->year > 9999 ||
        date->month < 1 || date->month > 12 ||
        date->day < 1 || date->day > 31) {
        goto cleanup;
    }

    ret = 0;

cleanup:
    regfree(&regex);
    return ret;
}

int main(int argc, char *argv[])
{
    const char *default_url = "https://example.com/2024/03/15/sample-article";
    const char *url;
    DateComponents date;

    if (argc > 1) {
        url = argv[1];
    } else {
        url = default_url;
    }

    if (extract_date_from_url(url, &date) != 0) {
        fprintf(stderr, "Failed to extract date from URL: %s\n", url);
        return EXIT_FAILURE;
    }

    printf("URL: %s\n", url);
    printf("Year: %d\n", date.year);
    printf("Month: %02d\n", date.month);
    printf("Day: %02d\n", date.day);

    return EXIT_SUCCESS;
}
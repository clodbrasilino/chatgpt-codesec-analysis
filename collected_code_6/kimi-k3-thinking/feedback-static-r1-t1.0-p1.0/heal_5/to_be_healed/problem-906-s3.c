#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

#define DATE_PATTERN "([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})"
#define MATCH_COUNT 4
#define MAX_YEAR_DIGITS 4
#define MAX_MONTH_DIGITS 2
#define MAX_DAY_DIGITS 2
#define YEAR_BUF_SIZE (MAX_YEAR_DIGITS + 4)
#define MONTH_BUF_SIZE (MAX_MONTH_DIGITS + 2)
#define DAY_BUF_SIZE (MAX_DAY_DIGITS + 2)

typedef struct {
    int year;
    int month;
    int day;
} DateComponents;

static int parse_component(const char *buf, int *out)
{
    char *endptr = NULL;
    long value;

    if (buf == NULL || out == NULL || buf[0] == '\0') {
        return -1;
    }

    errno = 0;
    value = strtol(buf, &endptr, 10);
    if (errno != 0 || endptr == buf || *endptr != '\0') {
        return -1;
    }

    if (value < 0 || value > INT_MAX) {
        return -1;
    }

    *out = (int)value;
    return 0;
}

static int copy_match(char *dest, size_t dest_size, const char *src, regoff_t len)
{
    size_t copy_len;
    int written;

    if (dest == NULL || src == NULL || len < 0 || dest_size < 2) {
        return -1;
    }

    copy_len = (size_t)len;
    if (copy_len == 0 || copy_len >= dest_size || copy_len > (size_t)INT_MAX) {
        dest[0] = '\0';
        return -1;
    }

    written = snprintf(dest, dest_size, "%.*s", (int)copy_len, src);
    if (written < 0 || (size_t)written != copy_len) {
        dest[0] = '\0';
        return -1;
    }

    return 0;
}

static int extract_date_from_url(const char *url, DateComponents *date)
{
    regex_t regex;
    regmatch_t matches[MATCH_COUNT];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year_buf[YEAR_BUF_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month_buf[MONTH_BUF_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day_buf[DAY_BUF_SIZE] = {0};
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

    if (year_len != MAX_YEAR_DIGITS ||
        month_len < 1 || month_len > MAX_MONTH_DIGITS ||
        day_len < 1 || day_len > MAX_DAY_DIGITS) {
        goto cleanup;
    }

    if ((size_t)year_len >= sizeof(year_buf) ||
        (size_t)month_len >= sizeof(month_buf) ||
        (size_t)day_len >= sizeof(day_buf)) {
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
    DateComponents date = {0, 0, 0};

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [url]\n", argv[0]);
        return EXIT_FAILURE;
    }

    url = (argc == 2) ? argv[1] : default_url;

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
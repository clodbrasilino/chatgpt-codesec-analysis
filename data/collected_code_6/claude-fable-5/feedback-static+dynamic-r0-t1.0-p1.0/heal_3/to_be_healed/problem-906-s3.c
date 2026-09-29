#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DATE_PATTERN "/([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})(/|$)"
#define MAX_FIELD_LEN 8
#define MAX_URL_LEN 2048

struct url_date {
    int year;
    int month;
    int day;
};

static int extract_substring(const char *source, size_t source_len,
                             const regmatch_t *match,
                             char *dest, size_t dest_size)
{
    size_t length;

    if (source == NULL || match == NULL || dest == NULL || dest_size == 0) {
        return -1;
    }

    if (match->rm_so < 0 || match->rm_eo < match->rm_so) {
        return -1;
    }

    if ((size_t)match->rm_eo > source_len) {
        return -1;
    }

    length = (size_t)(match->rm_eo - match->rm_so);
    if (length >= dest_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, source + match->rm_so, length);
    dest[length] = '\0';
    return 0;
}

int extract_date_from_url(const char *url, struct url_date *result)
{
    regex_t regex;
    regmatch_t matches[5];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year_str[MAX_FIELD_LEN] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month_str[MAX_FIELD_LEN] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day_str[MAX_FIELD_LEN] = {0};
    int rc;
    long year_val;
    long month_val;
    long day_val;
    char *endptr;
    size_t url_len;

    if (url == NULL || result == NULL) {
        return -1;
    }

    url_len = strnlen(url, MAX_URL_LEN);
    if (url_len >= MAX_URL_LEN) {
        return -1;
    }

    rc = regcomp(&regex, DATE_PATTERN, REG_EXTENDED);
    if (rc != 0) {
        return -1;
    }

    rc = regexec(&regex, url, 5, matches, 0);
    if (rc != 0) {
        regfree(&regex);
        return -1;
    }

    if (extract_substring(url, url_len, &matches[1], year_str, sizeof(year_str)) != 0 ||
        extract_substring(url, url_len, &matches[2], month_str, sizeof(month_str)) != 0 ||
        extract_substring(url, url_len, &matches[3], day_str, sizeof(day_str)) != 0) {
        regfree(&regex);
        return -1;
    }

    regfree(&regex);

    endptr = NULL;
    year_val = strtol(year_str, &endptr, 10);
    if (endptr == year_str || *endptr != '\0') {
        return -1;
    }

    endptr = NULL;
    month_val = strtol(month_str, &endptr, 10);
    if (endptr == month_str || *endptr != '\0') {
        return -1;
    }

    endptr = NULL;
    day_val = strtol(day_str, &endptr, 10);
    if (endptr == day_str || *endptr != '\0') {
        return -1;
    }

    if (year_val < 1000L || year_val > 9999L) {
        return -1;
    }
    if (month_val < 1L || month_val > 12L) {
        return -1;
    }
    if (day_val < 1L || day_val > 31L) {
        return -1;
    }

    result->year = (int)year_val;
    result->month = (int)month_val;
    result->day = (int)day_val;
    return 0;
}

int main(void)
{
    const char *urls[] = {
        "https://example.com/blog/2023/07/15/article-title",
        "https://news.site.org/2021/12/03/",
        "https://example.com/no/date/here",
        "https://example.com/2024/02/30/leap-check"
    };
    size_t count;
    size_t i;
    struct url_date date;

    count = sizeof(urls) / sizeof(urls[0]);

    for (i = 0; i < count; i++) {
        if (extract_date_from_url(urls[i], &date) == 0) {
            if (printf("URL: %s -> Year: %d, Month: %d, Day: %d\n",
                       urls[i], date.year, date.month, date.day) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("URL: %s -> no valid date found\n", urls[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}
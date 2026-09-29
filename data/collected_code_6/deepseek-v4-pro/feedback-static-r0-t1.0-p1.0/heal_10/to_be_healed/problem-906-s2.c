#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

static int safe_str_to_int(const char *str, int *value) {
    char *endptr;
    long tmp;

    if (str == NULL || *str == '\0') {
        return -1;
    }

    errno = 0;
    tmp = strtol(str, &endptr, 10);

    if (errno != 0 || *endptr != '\0') {
        return -1;
    }

    if (tmp < INT_MIN || tmp > INT_MAX) {
        return -1;
    }

    *value = (int)tmp;
    return 0;
}

static int validate_date(int year, int month, int day) {
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (year < 1 || year > 9999) {
        return -1;
    }

    if (month < 1 || month > 12) {
        return -1;
    }

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[2] = 29;
    }

    if (day < 1 || day > days_in_month[month]) {
        return -1;
    }

    return 0;
}

int extract_ymd(const char *url, int *year, int *month, int *day) {
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    size_t url_len = strnlen(url, SSIZE_MAX + 1);
    if (url_len > SSIZE_MAX) {
        return -1;
    }

    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})(/|$)";
    int ret;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year_str[5] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month_str[3] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day_str[3] = {0};

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    if (matches[1].rm_so < 0 || matches[1].rm_eo < 0 ||
        matches[2].rm_so < 0 || matches[2].rm_eo < 0 ||
        matches[3].rm_so < 0 || matches[3].rm_eo < 0) {
        regfree(&regex);
        return -1;
    }

    if ((size_t)matches[1].rm_so >= url_len || (size_t)matches[1].rm_eo > url_len ||
        (size_t)matches[2].rm_so >= url_len || (size_t)matches[2].rm_eo > url_len ||
        (size_t)matches[3].rm_so >= url_len || (size_t)matches[3].rm_eo > url_len) {
        regfree(&regex);
        return -1;
    }

    size_t year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    size_t month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    size_t day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);

    if (year_len == 0 || year_len >= sizeof(year_str) ||
        month_len == 0 || month_len >= sizeof(month_str) ||
        day_len == 0 || day_len >= sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }

    size_t year_offset = (size_t)matches[1].rm_so;
    size_t month_offset = (size_t)matches[2].rm_so;
    size_t day_offset = (size_t)matches[3].rm_so;

    if (year_offset + year_len > url_len ||
        month_offset + month_len > url_len ||
        day_offset + day_len > url_len) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year_str, url + year_offset, year_len);
    year_str[year_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month_str, url + month_offset, month_len);
    month_str[month_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day_str, url + day_offset, day_len);
    day_str[day_len] = '\0';

    regfree(&regex);

    int y, m, d;

    if (safe_str_to_int(year_str, &y) != 0 ||
        safe_str_to_int(month_str, &m) != 0 ||
        safe_str_to_int(day_str, &d) != 0) {
        return -1;
    }

    if (validate_date(y, m, d) != 0) {
        return -1;
    }

    *year = y;
    *month = m;
    *day = d;

    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2023/10/05/article",
        "http://test.org/2024/1/9",
        "https://nodate.com/path",
        NULL
    };

    int year, month, day;

    for (int i = 0; test_urls[i] != NULL; i++) {
        int result = extract_ymd(test_urls[i], &year, &month, &day);
        if (result == 0) {
            printf("%s -> %d-%d-%d\n", test_urls[i], year, month, day);
        } else {
            printf("%s -> no date found\n", test_urls[i]);
        }
    }

    return 0;
}
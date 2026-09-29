#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})";
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -2;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -3;
    }

    int year_len = matches[1].rm_eo - matches[1].rm_so;
    int month_len = matches[2].rm_eo - matches[2].rm_so;
    int day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len <= 0 || year_len > 4 || month_len <= 0 || month_len > 2 || day_len <= 0 || day_len > 2) {
        regfree(&regex);
        return -4;
    }

    char year_str[5] = {0};
    char month_str[3] = {0};
    char day_str[3] = {0};

    memcpy(year_str, url + matches[1].rm_so, year_len);
    year_str[year_len] = '\0';
    memcpy(month_str, url + matches[2].rm_so, month_len);
    month_str[month_len] = '\0';
    memcpy(day_str, url + matches[3].rm_so, day_len);
    day_str[day_len] = '\0';

    char *endptr;
    long val;

    errno = 0;
    val = strtol(year_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 9999) {
        regfree(&regex);
        return -5;
    }
    *year = (int)val;

    errno = 0;
    val = strtol(month_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 12) {
        regfree(&regex);
        return -5;
    }
    *month = (int)val;

    errno = 0;
    val = strtol(day_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 31) {
        regfree(&regex);
        return -5;
    }
    *day = (int)val;

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2024/03/15/article",
        "http://test.org/2023/12/01/post",
        "https://site.com/2022/7/5/news",
        "https://invalid.com/no/date/here",
        NULL
    };

    int year, month, day;

    for (int i = 0; test_urls[i] != NULL; i++) {
        printf("URL: %s\n", test_urls[i]);
        int result = extract_date_from_url(test_urls[i], &year, &month, &day);
        if (result == 0) {
            printf("Extracted date: %04d-%02d-%02d\n", year, month, day);
        } else {
            printf("Failed to extract date (error code: %d)\n", result);
        }
        printf("\n");
    }

    return 0;
}
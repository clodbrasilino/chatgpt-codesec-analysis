#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

#define YEAR_LEN   4
#define MONTH_LEN  2
#define DAY_LEN    2
#define YEAR_BUF   (YEAR_LEN + 1)
#define MONTH_BUF  (MONTH_LEN + 1)
#define DAY_BUF    (DAY_LEN + 1)

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "([0-9]{4})[-/]([0-9]{1,2})[-/]([0-9]{1,2})";
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    size_t year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    size_t month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    size_t day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);

    if (year_len > YEAR_LEN || month_len > MONTH_LEN || day_len > DAY_LEN) {
        regfree(&regex);
        return -1;
    }

    if (year_len == 0 || month_len == 0 || day_len == 0) {
        regfree(&regex);
        return -1;
    }

    char year_str[YEAR_BUF] = {0};
    char month_str[MONTH_BUF] = {0};
    char day_str[DAY_BUF] = {0};

    if (year_len >= YEAR_BUF) {
        regfree(&regex);
        return -1;
    }
    memcpy(year_str, url + matches[1].rm_so, year_len);
    year_str[year_len] = '\0';

    if (month_len >= MONTH_BUF) {
        regfree(&regex);
        return -1;
    }
    memcpy(month_str, url + matches[2].rm_so, month_len);
    month_str[month_len] = '\0';

    if (day_len >= DAY_BUF) {
        regfree(&regex);
        return -1;
    }
    memcpy(day_str, url + matches[3].rm_so, day_len);
    day_str[day_len] = '\0';

    char *endptr;
    long year_val = strtol(year_str, &endptr, 10);
    if (*endptr != '\0' || year_val < 1 || year_val > 9999) {
        regfree(&regex);
        return -1;
    }

    long month_val = strtol(month_str, &endptr, 10);
    if (*endptr != '\0' || month_val < 1 || month_val > 12) {
        regfree(&regex);
        return -1;
    }

    long day_val = strtol(day_str, &endptr, 10);
    if (*endptr != '\0' || day_val < 1 || day_val > 31) {
        regfree(&regex);
        return -1;
    }

    regfree(&regex);

    *year = (int)year_val;
    *month = (int)month_val;
    *day = (int)day_val;

    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2024/03/15/article",
        "http://test.org/2023-12-01/news",
        "https://site.com/2022/7/9/post",
        "https://invalid.com/2024/13/45/bad",
        "https://nodate.com/hello/world",
        NULL
    };

    int year, month, day;

    for (int i = 0; test_urls[i] != NULL; i++) {
        int result = extract_date_from_url(test_urls[i], &year, &month, &day);
        if (result == 0) {
            printf("URL: %s\nDate: %04d-%02d-%02d\n\n", test_urls[i], year, month, day);
        } else {
            printf("URL: %s\nNo valid date found\n\n", test_urls[i]);
        }
    }

    return 0;
}
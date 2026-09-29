#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})(/|$)";
    int ret;
    size_t year_len, month_len, day_len;
    char year_str[5];
    char month_str[3];
    char day_str[3];
    long val;
    char *endptr;
    int result = -1;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        goto cleanup_regex;
    }

    if (matches[1].rm_so == -1 || matches[2].rm_so == -1 || matches[3].rm_so == -1) {
        goto cleanup_regex;
    }

    year_len = matches[1].rm_eo - matches[1].rm_so;
    month_len = matches[2].rm_eo - matches[2].rm_so;
    day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len == 0 || month_len == 0 || day_len == 0) {
        goto cleanup_regex;
    }

    if (year_len > 4 || month_len > 2 || day_len > 2) {
        goto cleanup_regex;
    }

    memcpy(year_str, url + matches[1].rm_so, year_len);
    year_str[year_len] = '\0';

    memcpy(month_str, url + matches[2].rm_so, month_len);
    month_str[month_len] = '\0';

    memcpy(day_str, url + matches[3].rm_so, day_len);
    day_str[day_len] = '\0';

    errno = 0;
    val = strtol(year_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 9999) {
        goto cleanup_regex;
    }
    *year = (int)val;

    errno = 0;
    val = strtol(month_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 12) {
        goto cleanup_regex;
    }
    *month = (int)val;

    errno = 0;
    val = strtol(day_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 31) {
        goto cleanup_regex;
    }
    *day = (int)val;

    result = 0;

cleanup_regex:
    regfree(&regex);
    return result;
}

int main(void) {
    const char *url1 = "https://example.com/2023/12/25/article";
    const char *url2 = "https://example.com/2023/1/5/";
    const char *url3 = "https://example.com/no-date";
    int year, month, day;

    if (extract_date_from_url(url1, &year, &month, &day) == 0) {
        printf("%s -> %d-%02d-%02d\n", url1, year, month, day);
    } else {
        printf("%s -> no date found\n", url1);
    }

    if (extract_date_from_url(url2, &year, &month, &day) == 0) {
        printf("%s -> %d-%02d-%02d\n", url2, year, month, day);
    } else {
        printf("%s -> no date found\n", url2);
    }

    if (extract_date_from_url(url3, &year, &month, &day) == 0) {
        printf("%s -> %d-%02d-%02d\n", url3, year, month, day);
    } else {
        printf("%s -> no date found\n", url3);
    }

    return 0;
}
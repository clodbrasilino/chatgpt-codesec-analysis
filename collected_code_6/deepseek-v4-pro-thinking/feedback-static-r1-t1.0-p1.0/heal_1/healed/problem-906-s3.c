#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    char year_str[5];
    char month_str[3];
    char day_str[3];
    char *endptr;
    long y, m, d;
    size_t year_len, month_len, day_len;
    int ret;
    const char *pattern;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return 0;
    }

    pattern = "([0-9]{4})[-/]([0-9]{2})[-/]([0-9]{2})";
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return 0;
    }

    if (matches[1].rm_so < 0 || matches[2].rm_so < 0 || matches[3].rm_so < 0) {
        regfree(&regex);
        return 0;
    }

    year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);

    if (year_len >= sizeof(year_str) || month_len >= sizeof(month_str) || day_len >= sizeof(day_str)) {
        regfree(&regex);
        return 0;
    }

    snprintf(year_str, sizeof(year_str), "%.*s", (int)year_len, url + matches[1].rm_so);
    snprintf(month_str, sizeof(month_str), "%.*s", (int)month_len, url + matches[2].rm_so);
    snprintf(day_str, sizeof(day_str), "%.*s", (int)day_len, url + matches[3].rm_so);

    y = strtol(year_str, &endptr, 10);
    if (*endptr != '\0') {
        regfree(&regex);
        return 0;
    }
    m = strtol(month_str, &endptr, 10);
    if (*endptr != '\0') {
        regfree(&regex);
        return 0;
    }
    d = strtol(day_str, &endptr, 10);
    if (*endptr != '\0') {
        regfree(&regex);
        return 0;
    }

    if (y < 1 || y > 9999 || m < 1 || m > 12 || d < 1 || d > 31) {
        regfree(&regex);
        return 0;
    }

    *year = (int)y;
    *month = (int)m;
    *day = (int)d;

    regfree(&regex);
    return 1;
}

int main(void) {
    const char *url = "https://example.com/news/2024/12/25/headline";
    int year = 0;
    int month = 0;
    int day = 0;

    if (extract_date_from_url(url, &year, &month, &day)) {
        printf("%04d-%02d-%02d\n", year, month, day);
    } else {
        printf("No date found\n");
    }

    return 0;
}
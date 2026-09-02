#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})(/|$)";
    int ret;
    char year_str[5];
    char month_str[3];
    char day_str[3];

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    if (matches[1].rm_so == -1 || matches[2].rm_so == -1 || matches[3].rm_so == -1) {
        regfree(&regex);
        return -1;
    }

    size_t year_len = matches[1].rm_eo - matches[1].rm_so;
    size_t month_len = matches[2].rm_eo - matches[2].rm_so;
    size_t day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len >= sizeof(year_str) || month_len >= sizeof(month_str) || day_len >= sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }

    memcpy(year_str, url + matches[1].rm_so, year_len);
    year_str[year_len] = '\0';
    memcpy(month_str, url + matches[2].rm_so, month_len);
    month_str[month_len] = '\0';
    memcpy(day_str, url + matches[3].rm_so, day_len);
    day_str[day_len] = '\0';

    *year = atoi(year_str);
    *month = atoi(month_str);
    *day = atoi(day_str);

    regfree(&regex);

    if (*month < 1 || *month > 12 || *day < 1 || *day > 31) {
        return -1;
    }

    return 0;
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
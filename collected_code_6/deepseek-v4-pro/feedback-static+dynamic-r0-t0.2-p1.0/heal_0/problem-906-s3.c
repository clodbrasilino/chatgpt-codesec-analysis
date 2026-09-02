#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
        return -1;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    char year_str[5] = {0};
    char month_str[3] = {0};
    char day_str[3] = {0};

    int year_len = matches[1].rm_eo - matches[1].rm_so;
    int month_len = matches[2].rm_eo - matches[2].rm_so;
    int day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len > 4 || month_len > 2 || day_len > 2) {
        regfree(&regex);
        return -1;
    }

    strncpy(year_str, url + matches[1].rm_so, year_len);
    strncpy(month_str, url + matches[2].rm_so, month_len);
    strncpy(day_str, url + matches[3].rm_so, day_len);

    year_str[year_len] = '\0';
    month_str[month_len] = '\0';
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
    const char *url1 = "https://example.com/2024/03/15/article";
    const char *url2 = "https://example.com/2023/12/01/post";
    const char *url3 = "https://example.com/no-date-here";
    int year, month, day;

    if (extract_date_from_url(url1, &year, &month, &day) == 0) {
        printf("URL1: %04d-%02d-%02d\n", year, month, day);
    } else {
        printf("URL1: No valid date found\n");
    }

    if (extract_date_from_url(url2, &year, &month, &day) == 0) {
        printf("URL2: %04d-%02d-%02d\n", year, month, day);
    } else {
        printf("URL2: No valid date found\n");
    }

    if (extract_date_from_url(url3, &year, &month, &day) == 0) {
        printf("URL3: %04d-%02d-%02d\n", year, month, day);
    } else {
        printf("URL3: No valid date found\n");
    }

    return 0;
}
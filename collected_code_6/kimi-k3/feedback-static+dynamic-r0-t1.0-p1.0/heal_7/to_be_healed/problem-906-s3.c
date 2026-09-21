#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

typedef struct {
    int year;
    int month;
    int day;
} DateComponents;

int extract_date_from_url(const char *url, DateComponents *date) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{2})/([0-9]{2})/";
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year_str[5];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month_str[3];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day_str[3];
    char *endptr;
    long year_val, month_val, day_val;
    regoff_t year_len, month_len, day_len;

    if (url == NULL || date == NULL) {
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

    year_len = matches[1].rm_eo - matches[1].rm_so;
    month_len = matches[2].rm_eo - matches[2].rm_so;
    day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len != 4 || month_len != 2 || day_len != 2) {
        regfree(&regex);
        return -1;
    }

    if ((size_t)year_len >= sizeof(year_str) || 
        (size_t)month_len >= sizeof(month_str) || 
        (size_t)day_len >= sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }

    if ((size_t)year_len < sizeof(year_str)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        if (memcpy(year_str, url + matches[1].rm_so, (size_t)year_len) == NULL) {
            regfree(&regex);
            return -1;
        }
        year_str[(size_t)year_len] = '\0';
    } else {
        regfree(&regex);
        return -1;
    }

    if ((size_t)month_len < sizeof(month_str)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        if (memcpy(month_str, url + matches[2].rm_so, (size_t)month_len) == NULL) {
            regfree(&regex);
            return -1;
        }
        month_str[(size_t)month_len] = '\0';
    } else {
        regfree(&regex);
        return -1;
    }

    if ((size_t)day_len < sizeof(day_str)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        if (memcpy(day_str, url + matches[3].rm_so, (size_t)day_len) == NULL) {
            regfree(&regex);
            return -1;
        }
        day_str[(size_t)day_len] = '\0';
    } else {
        regfree(&regex);
        return -1;
    }

    errno = 0;
    year_val = strtol(year_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || year_val < 0 || year_val > INT_MAX) {
        regfree(&regex);
        return -1;
    }

    errno = 0;
    month_val = strtol(month_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || month_val < 0 || month_val > INT_MAX) {
        regfree(&regex);
        return -1;
    }

    errno = 0;
    day_val = strtol(day_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || day_val < 0 || day_val > INT_MAX) {
        regfree(&regex);
        return -1;
    }

    date->year = (int)year_val;
    date->month = (int)month_val;
    date->day = (int)day_val;

    if (date->year < 1900 || date->year > 2100 ||
        date->month < 1 || date->month > 12 ||
        date->day < 1 || date->day > 31) {
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2024/01/15/article",
        "https://example.com/2023/12/25/news",
        "https://example.com/invalid/path",
        NULL
    };

    for (int i = 0; test_urls[i] != NULL; i++) {
        DateComponents date;
        int result = extract_date_from_url(test_urls[i], &date);

        if (result == 0) {
            printf("URL: %s\n", test_urls[i]);
            printf("Year: %d, Month: %d, Day: %d\n\n", date.year, date.month, date.day);
        } else {
            printf("URL: %s\n", test_urls[i]);
            printf("Failed to extract date\n\n");
        }
    }

    return 0;
}
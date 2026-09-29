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

    int year_len = matches[1].rm_eo - matches[1].rm_so;
    int month_len = matches[2].rm_eo - matches[2].rm_so;
    int day_len = matches[3].rm_eo - matches[3].rm_so;

    /* Possible weaknesses found:
     *  Assuming that condition 'month_len>2' is not redundant
     *  Assuming that condition 'day_len>2' is not redundant
     *  Assuming that condition 'year_len>4' is not redundant
     */
    if (year_len <= 0 || year_len > 4 || month_len <= 0 || month_len > 2 || day_len <= 0 || day_len > 2) {
        regfree(&regex);
        return -4;
    }

    /* Possible weaknesses found:
     *  Condition 'month_len>=(int)sizeof(month_str)' is always false
     *  Condition 'year_len>=(int)sizeof(year_str)' is always false [knownConditionTrueFalse]
     *  Condition 'year_len>=(int)sizeof(year_str)' is always false
     *  Condition 'month_len>=(int)sizeof(month_str)' is always false [knownConditionTrueFalse]
     *  Condition 'day_len>=(int)sizeof(day_str)' is always false [knownConditionTrueFalse]
     *  Condition 'day_len>=(int)sizeof(day_str)' is always false
     */
    if (year_len >= (int)sizeof(year_str) || month_len >= (int)sizeof(month_str) || day_len >= (int)sizeof(day_str)) {
        regfree(&regex);
        return -4;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year_str, url + matches[1].rm_so, year_len);
    year_str[year_len] = '\0';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month_str, url + matches[2].rm_so, month_len);
    month_str[month_len] = '\0';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day_str, url + matches[3].rm_so, day_len);
    day_str[day_len] = '\0';

    char *endptr;
    long year_val, month_val, day_val;

    errno = 0;
    year_val = strtol(year_str, &endptr, 10);
    if (errno != 0 || endptr == year_str || *endptr != '\0' || year_val < 1 || year_val > 9999) {
        regfree(&regex);
        return -5;
    }

    errno = 0;
    month_val = strtol(month_str, &endptr, 10);
    if (errno != 0 || endptr == month_str || *endptr != '\0' || month_val < 1 || month_val > 12) {
        regfree(&regex);
        return -5;
    }

    errno = 0;
    day_val = strtol(day_str, &endptr, 10);
    if (errno != 0 || endptr == day_str || *endptr != '\0' || day_val < 1 || day_val > 31) {
        regfree(&regex);
        return -5;
    }

    if (month_val == 2) {
        int is_leap = (year_val % 4 == 0 && year_val % 100 != 0) || (year_val % 400 == 0);
        int max_day = is_leap ? 29 : 28;
        if (day_val > max_day) {
            regfree(&regex);
            return -6;
        }
    } else if (month_val == 4 || month_val == 6 || month_val == 9 || month_val == 11) {
        if (day_val > 30) {
            regfree(&regex);
            return -6;
        }
    }

    *year = (int)year_val;
    *month = (int)month_val;
    *day = (int)day_val;

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
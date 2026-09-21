#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

static long safe_strtol(const char *str, int min_val, int max_val, int *valid) {
    char *endptr;
    long val;
    
    if (str == NULL || *str == '\0') {
        *valid = 0;
        return 0;
    }
    
    errno = 0;
    val = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || endptr == str || *endptr != '\0') {
        *valid = 0;
        return 0;
    }
    
    if (val < min_val || val > max_val) {
        *valid = 0;
        return 0;
    }
    
    *valid = 1;
    return val;
}

int extract_ymd(const char *url, int *year, int *month, int *day) {
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})(/|$)";
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
    size_t len;
    int valid;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(url) > 2048) {
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

    len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    if (len >= sizeof(year_str) || len == 0) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year_str, url + matches[1].rm_so, len);
    year_str[len] = '\0';

    len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    if (len >= sizeof(month_str) || len == 0) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month_str, url + matches[2].rm_so, len);
    month_str[len] = '\0';

    len = (size_t)(matches[3].rm_eo - matches[3].rm_so);
    if (len >= sizeof(day_str) || len == 0) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day_str, url + matches[3].rm_so, len);
    day_str[len] = '\0';

    long tmp_year = safe_strtol(year_str, 1, 9999, &valid);
    if (!valid) {
        regfree(&regex);
        return -1;
    }
    *year = (int)tmp_year;

    long tmp_month = safe_strtol(month_str, 1, 12, &valid);
    if (!valid) {
        regfree(&regex);
        return -1;
    }
    *month = (int)tmp_month;

    long tmp_day = safe_strtol(day_str, 1, 31, &valid);
    if (!valid) {
        regfree(&regex);
        return -1;
    }
    *day = (int)tmp_day;

    if (tmp_day > 31) {
        regfree(&regex);
        return -1;
    }
    if ((tmp_month == 4 || tmp_month == 6 || tmp_month == 9 || tmp_month == 11) && tmp_day > 30) {
        regfree(&regex);
        return -1;
    }
    if (tmp_month == 2) {
        int is_leap = ((tmp_year % 4 == 0 && tmp_year % 100 != 0) || (tmp_year % 400 == 0));
        if (is_leap && tmp_day > 29) {
            regfree(&regex);
            return -1;
        }
        if (!is_leap && tmp_day > 28) {
            regfree(&regex);
            return -1;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2023/10/05/article",
        "http://test.org/2024/1/9",
        "https://nodate.com/path",
        "https://invalid.com/2023/13/01",
        "https://invalid.com/2023/02/29",
        "https://valid.com/2024/02/29",
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
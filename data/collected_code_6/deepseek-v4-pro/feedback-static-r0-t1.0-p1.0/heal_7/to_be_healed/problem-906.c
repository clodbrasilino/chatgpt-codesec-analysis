#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

#define YEAR_STR_SIZE 5
#define MONTH_STR_SIZE 3
#define DAY_STR_SIZE 3

static int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int validate_date(int year, int month, int day) {
    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2) {
        days_in_month[2] = is_leap_year(year) ? 29 : 28;
    }

    if (day > days_in_month[month]) return 0;

    return 1;
}

static int safe_copy_substring(const char *url, size_t url_len, regoff_t start, regoff_t end,
                                char *dest, size_t dest_size) {
    if (start < 0 || end < 0) return -1;
    if ((size_t)end > url_len) return -1;
    if (end <= start) return -1;

    size_t len = (size_t)(end - start);
    if (len >= dest_size) return -1;

    if (len + 1 > dest_size) return -1;

    memmove(dest, url + start, len);
    dest[len] = '\0';
    return 0;
}

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t url_len = strlen(url);
    if (url_len == 0) {
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

    if (matches[1].rm_so == -1 || matches[2].rm_so == -1 || matches[3].rm_so == -1) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year_str[YEAR_STR_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month_str[MONTH_STR_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day_str[DAY_STR_SIZE];

    if (safe_copy_substring(url, url_len, matches[1].rm_so, matches[1].rm_eo,
                            year_str, YEAR_STR_SIZE) != 0) {
        regfree(&regex);
        return -1;
    }

    if (safe_copy_substring(url, url_len, matches[2].rm_so, matches[2].rm_eo,
                            month_str, MONTH_STR_SIZE) != 0) {
        regfree(&regex);
        return -1;
    }

    if (safe_copy_substring(url, url_len, matches[3].rm_so, matches[3].rm_eo,
                            day_str, DAY_STR_SIZE) != 0) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t year_len = strlen(year_str);
    if (year_len != 4) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t month_len = strlen(month_str);
    if (month_len == 0 || month_len > 2) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t day_len = strlen(day_str);
    if (day_len == 0 || day_len > 2) {
        regfree(&regex);
        return -1;
    }

    char *endptr;
    long val;

    val = strtol(year_str, &endptr, 10);
    if (endptr == year_str || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        regfree(&regex);
        return -1;
    }
    int year_val = (int)val;

    val = strtol(month_str, &endptr, 10);
    if (endptr == month_str || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        regfree(&regex);
        return -1;
    }
    int month_val = (int)val;

    val = strtol(day_str, &endptr, 10);
    if (endptr == day_str || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        regfree(&regex);
        return -1;
    }
    int day_val = (int)val;

    if (!validate_date(year_val, month_val, day_val)) {
        regfree(&regex);
        return -1;
    }

    *year = year_val;
    *month = month_val;
    *day = day_val;

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2023/12/25/article",
        "http://test.org/2024-02-29/news",
        "https://invalid.com/2023-13-01/test",
        "https://invalid.com/2023-02-30/test",
        "https://no-date.com/test",
        NULL
    };

    for (int i = 0; test_urls[i] != NULL; i++) {
        int year = 0, month = 0, day = 0;
        int result = extract_date_from_url(test_urls[i], &year, &month, &day);

        if (result == 0) {
            printf("URL: %s\nDate: %04d-%02d-%02d\n\n", test_urls[i], year, month, day);
        } else {
            printf("URL: %s\nNo valid date found\n\n", test_urls[i]);
        }
    }

    return 0;
}
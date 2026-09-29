#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <errno.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
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
    long val;
    size_t year_len;
    size_t month_len;
    size_t day_len;
    char *endptr;
    size_t url_len;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    url_len = strlen(url);

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

    if (year_len >= sizeof(year_str) || month_len >= sizeof(month_str) || day_len >= sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }

    if (matches[1].rm_so + year_len > url_len ||
        matches[2].rm_so + month_len > url_len ||
        matches[3].rm_so + day_len > url_len) {
        regfree(&regex);
        return -1;
    }

    if (year_len + 1 > sizeof(year_str) || month_len + 1 > sizeof(month_str) || day_len + 1 > sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }

    if (year_len < sizeof(year_str)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(year_str, url + matches[1].rm_so, year_len);
        year_str[year_len] = '\0';
    } else {
        regfree(&regex);
        return -1;
    }

    if (month_len < sizeof(month_str)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(month_str, url + matches[2].rm_so, month_len);
        month_str[month_len] = '\0';
    } else {
        regfree(&regex);
        return -1;
    }

    if (day_len < sizeof(day_str)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(day_str, url + matches[3].rm_so, day_len);
        day_str[day_len] = '\0';
    } else {
        regfree(&regex);
        return -1;
    }

    errno = 0;
    val = strtol(year_str, &endptr, 10);
    if (errno != 0 || endptr == year_str || *endptr != '\0' || val < 1 || val > INT_MAX) {
        regfree(&regex);
        return -1;
    }
    *year = (int)val;

    errno = 0;
    val = strtol(month_str, &endptr, 10);
    if (errno != 0 || endptr == month_str || *endptr != '\0' || val < 1 || val > 12) {
        regfree(&regex);
        return -1;
    }
    *month = (int)val;

    errno = 0;
    val = strtol(day_str, &endptr, 10);
    if (errno != 0 || endptr == day_str || *endptr != '\0' || val < 1 || val > 31) {
        regfree(&regex);
        return -1;
    }
    *day = (int)val;

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *url = "https://example.com/2024/03/15/article";
    int year, month, day;

    if (extract_date_from_url(url, &year, &month, &day) == 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("No date found in URL\n");
    }

    return 0;
}
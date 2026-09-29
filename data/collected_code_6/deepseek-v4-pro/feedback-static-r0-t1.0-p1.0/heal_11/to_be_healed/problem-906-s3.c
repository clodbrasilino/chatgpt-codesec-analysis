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

    if (matches[1].rm_so == -1 || matches[2].rm_so == -1 || matches[3].rm_so == -1) {
        regfree(&regex);
        return -4;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t url_len = strlen(url);
    size_t year_so = (size_t)matches[1].rm_so;
    size_t year_eo = (size_t)matches[1].rm_eo;
    size_t month_so = (size_t)matches[2].rm_so;
    size_t month_eo = (size_t)matches[2].rm_eo;
    size_t day_so = (size_t)matches[3].rm_so;
    size_t day_eo = (size_t)matches[3].rm_eo;

    /* Possible weaknesses found:
     *  Assuming that condition 'year_so>=year_eo' is not redundant
     */
    if (year_so >= year_eo || year_eo > url_len ||
        /* Possible weaknesses found:
         *  Assuming that condition 'month_so>=month_eo' is not redundant
         */
        month_so >= month_eo || month_eo > url_len ||
        /* Possible weaknesses found:
         *  Assuming that condition 'day_so>=day_eo' is not redundant
         */
        day_so >= day_eo || day_eo > url_len) {
        regfree(&regex);
        return -4;
    }

    /* Possible weaknesses found:
     *  Assignment 'year_len=year_eo-year_so', assigned value is greater than 0
     */
    size_t year_len = year_eo - year_so;
    /* Possible weaknesses found:
     *  Assignment 'month_len=month_eo-month_so', assigned value is greater than 0
     */
    size_t month_len = month_eo - month_so;
    /* Possible weaknesses found:
     *  Assignment 'day_len=day_eo-day_so', assigned value is greater than 0
     */
    size_t day_len = day_eo - day_so;

    /* Possible weaknesses found:
     *  Assuming that condition 'day_len>2' is not redundant
     *  Condition 'day_len<1' is always false
     *  Condition 'day_len<1' is always false [knownConditionTrueFalse]
     *  Condition 'year_len<1' is always false
     *  Condition 'month_len<1' is always false [knownConditionTrueFalse]
     *  Assuming that condition 'year_len>4' is not redundant
     *  Condition 'month_len<1' is always false
     *  Assuming that condition 'month_len>2' is not redundant
     *  Condition 'year_len<1' is always false [knownConditionTrueFalse]
     */
    if (year_len < 1 || year_len > 4 || month_len < 1 || month_len > 2 || day_len < 1 || day_len > 2) {
        regfree(&regex);
        return -4;
    }

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (year_len > SIZE_MAX - 1 || month_len > SIZE_MAX - 1 || day_len > SIZE_MAX - 1) {
        regfree(&regex);
        return -4;
    }

    /* Possible weaknesses found:
     *  Assignment 'year_buf_size=year_len+1', assigned value is less than 6
     */
    size_t year_buf_size = year_len + 1;
    /* Possible weaknesses found:
     *  Assignment 'month_buf_size=month_len+1', assigned value is less than 4
     */
    size_t month_buf_size = month_len + 1;
    /* Possible weaknesses found:
     *  Assignment 'day_buf_size=day_len+1', assigned value is less than 4
     */
    size_t day_buf_size = day_len + 1;

    /* Possible weaknesses found:
     *  Condition 'day_buf_size>4096' is always false
     *  Condition 'month_buf_size>4096' is always false [knownConditionTrueFalse]
     *  Condition 'year_buf_size>4096' is always false
     *  Condition 'day_buf_size>4096' is always false [knownConditionTrueFalse]
     *  Condition 'month_buf_size>4096' is always false
     *  Condition 'year_buf_size>4096' is always false [knownConditionTrueFalse]
     */
    if (year_buf_size > 4096 || month_buf_size > 4096 || day_buf_size > 4096) {
        regfree(&regex);
        return -4;
    }

    char *year_str = malloc(year_buf_size);
    char *month_str = malloc(month_buf_size);
    char *day_str = malloc(day_buf_size);

    if (year_str == NULL || month_str == NULL || day_str == NULL) {
        free(year_str);
        free(month_str);
        free(day_str);
        regfree(&regex);
        return -4;
    }

    if (year_len >= year_buf_size || month_len >= month_buf_size || day_len >= day_buf_size) {
        free(year_str);
        free(month_str);
        free(day_str);
        regfree(&regex);
        return -4;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year_str, url + year_so, year_len);
    year_str[year_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month_str, url + month_so, month_len);
    month_str[month_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day_str, url + day_so, day_len);
    day_str[day_len] = '\0';

    char *endptr;
    long val;

    errno = 0;
    val = strtol(year_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 9999) {
        free(year_str);
        free(month_str);
        free(day_str);
        regfree(&regex);
        return -5;
    }
    *year = (int)val;

    errno = 0;
    val = strtol(month_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 12) {
        free(year_str);
        free(month_str);
        free(day_str);
        regfree(&regex);
        return -5;
    }
    *month = (int)val;

    errno = 0;
    val = strtol(day_str, &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 1 || val > 31) {
        free(year_str);
        free(month_str);
        free(day_str);
        regfree(&regex);
        return -5;
    }
    *day = (int)val;

    free(year_str);
    free(month_str);
    free(day_str);
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
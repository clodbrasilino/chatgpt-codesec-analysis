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
    long val;
    char *endptr;

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

    if (matches[1].rm_eo - matches[1].rm_so != 4 ||
        matches[2].rm_eo - matches[2].rm_so < 1 ||
        matches[2].rm_eo - matches[2].rm_so > 2 ||
        matches[3].rm_eo - matches[3].rm_so < 1 ||
        matches[3].rm_eo - matches[3].rm_so > 2) {
        regfree(&regex);
        return -1;
    }

    len = matches[1].rm_eo - matches[1].rm_so;
    if (len >= sizeof(year_str)) {
        regfree(&regex);
        return -1;
    }
    if (len + 1 > sizeof(year_str)) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(year_str, url + matches[1].rm_so, len);
    year_str[len] = '\0';
    
    len = matches[2].rm_eo - matches[2].rm_so;
    if (len >= sizeof(month_str)) {
        regfree(&regex);
        return -1;
    }
    if (len + 1 > sizeof(month_str)) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(month_str, url + matches[2].rm_so, len);
    month_str[len] = '\0';
    
    len = matches[3].rm_eo - matches[3].rm_so;
    if (len >= sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }
    if (len + 1 > sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(day_str, url + matches[3].rm_so, len);
    day_str[len] = '\0';

    errno = 0;
    val = strtol(year_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val < 0 || val > INT_MAX) {
        regfree(&regex);
        return -1;
    }
    *year = (int)val;

    errno = 0;
    val = strtol(month_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val < 1 || val > 12) {
        regfree(&regex);
        return -1;
    }
    *month = (int)val;

    errno = 0;
    val = strtol(day_str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val < 1 || val > 31) {
        regfree(&regex);
        return -1;
    }
    *day = (int)val;

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2024/03/15/article",
        "http://test.org/2023/12/1",
        "https://site.com/2024/1/05/post",
        "https://invalid.com/2024/13/45",
        "https://nodate.com/path",
        NULL
    };
    
    int year, month, day;
    int i;
    
    for (i = 0; test_urls[i] != NULL; i++) {
        printf("URL: %s\n", test_urls[i]);
        if (extract_date_from_url(test_urls[i], &year, &month, &day) == 0) {
            printf("Extracted: Year=%d, Month=%d, Day=%d\n", year, month, day);
        } else {
            printf("No valid date found\n");
        }
        printf("\n");
    }
    
    return 0;
}
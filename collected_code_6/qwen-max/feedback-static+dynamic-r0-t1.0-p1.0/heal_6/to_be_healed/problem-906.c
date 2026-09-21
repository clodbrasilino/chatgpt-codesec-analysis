#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>
#include <string.h>

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];

    if (regcomp(&regex, "/(\\d{4})/(\\d{2})/(\\d{2})/", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex.\n");
        exit(EXIT_FAILURE);
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
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

        size_t year_len = matches[1].rm_eo - matches[1].rm_so;
        if (year_len < sizeof(year_str) - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(year_str, url + matches[1].rm_so, year_len);
            year_str[year_len] = '\0';
        }

        size_t month_len = matches[2].rm_eo - matches[2].rm_so;
        if (month_len < sizeof(month_str) - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(month_str, url + matches[2].rm_so, month_len);
            month_str[month_len] = '\0';
        }

        size_t day_len = matches[3].rm_eo - matches[3].rm_so;
        if (day_len < sizeof(day_str) - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(day_str, url + matches[3].rm_so, day_len);
            day_str[day_len] = '\0';
        }

        long year_val = strtol(year_str, NULL, 10);
        long month_val = strtol(month_str, NULL, 10);
        long day_val = strtol(day_str, NULL, 10);

        if (year_val >= INT_MIN && year_val <= INT_MAX) *year = (int)year_val;
        else *year = 0;

        if (month_val >= 1 && month_val <= 12) *month = (int)month_val;
        else *month = 0;

        if (day_val >= 1 && day_val <= 31) *day = (int)day_val;
        else *day = 0;
    } else {
        *year = 0;
        *month = 0;
        *day = 0;
    }

    regfree(&regex);
}

int main() {
    const char *url = "https://example.com/2023/08/15/some-article";
    int year, month, day;

    extract_date(url, &year, &month, &day);

    if (year != 0 && month != 0 && day != 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found.\n");
    }

    return 0;
}
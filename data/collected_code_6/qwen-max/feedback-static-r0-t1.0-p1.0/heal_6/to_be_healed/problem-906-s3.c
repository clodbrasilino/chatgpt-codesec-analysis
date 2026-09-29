#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <limits.h>

void extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t match[4];
    const char *pattern = "([0-9]{4})/([0-9]{2})/([0-9]{2})";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    if (regexec(&regex, url, 4, match, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t url_len = strlen(url);

        if (match[1].rm_so + 4 <= match[1].rm_eo && match[1].rm_eo <= (int)(url_len)) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char year_str[5];
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(year_str, url + match[1].rm_so, 4);
            year_str[4] = '\0';
            long year_val = strtol(year_str, NULL, 10);
            if (year_val >= INT_MIN && year_val <= INT_MAX) {
                *year = (int)year_val;
            } else {
                *year = -1;
            }
        } else {
            *year = -1;
        }

        if (match[2].rm_so + 2 <= match[2].rm_eo && match[2].rm_eo <= (int)(url_len)) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char month_str[3];
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(month_str, url + match[2].rm_so, 2);
            month_str[2] = '\0';
            long month_val = strtol(month_str, NULL, 10);
            if (month_val >= 1 && month_val <= 12) {
                *month = (int)month_val;
            } else {
                *month = -1;
            }
        } else {
            *month = -1;
        }

        if (match[3].rm_so + 2 <= match[3].rm_eo && match[3].rm_eo <= (int)(url_len)) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char day_str[3];
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(day_str, url + match[3].rm_so, 2);
            day_str[2] = '\0';
            long day_val = strtol(day_str, NULL, 10);
            if (day_val >= 1 && day_val <= 31) {
                *day = (int)day_val;
            } else {
                *day = -1;
            }
        } else {
            *day = -1;
        }
    } else {
        *year = -1;
        *month = -1;
        *day = -1;
    }

    regfree(&regex);
}

int main() {
    const char *url = "https://example.com/2023/10/05/some-article";
    int year, month, day;

    extract_date_from_url(url, &year, &month, &day);

    if (year != -1 && month != -1 && day != -1) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <limits.h>

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = ".*\\/([0-9]{4})\\/([0-9]{2})\\/([0-9]{2}).*";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        *year = 0;
        *month = 0;
        *day = 0;
        return;
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        size_t year_len = matches[1].rm_eo - matches[1].rm_so;
        if (year_len == 4) {
            long year_val = strtol(url + matches[1].rm_so, NULL, 10);
            *year = (year_val > INT_MAX || year_val < 0) ? 0 : (int)year_val;
        } else {
            *year = 0;
        }

        size_t month_len = matches[2].rm_eo - matches[2].rm_so;
        if (month_len == 2) {
            long month_val = strtol(url + matches[2].rm_so, NULL, 10);
            *month = (month_val < 1 || month_val > 12) ? 0 : (int)month_val;
        } else {
            *month = 0;
        }

        size_t day_len = matches[3].rm_eo - matches[3].rm_so;
        if (day_len == 2) {
            long day_val = strtol(url + matches[3].rm_so, NULL, 10);
            *day = (day_val < 1 || day_val > 31) ? 0 : (int)day_val;
        } else {
            *day = 0;
        }
    } else {
        *year = 0;
        *month = 0;
        *day = 0;
    }

    regfree(&regex);
}

int main() {
    const char *url = "http://example.com/2023/10/01";
    int year = 0, month = 0, day = 0;

    extract_date(url, &year, &month, &day);

    if (year && month && day) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
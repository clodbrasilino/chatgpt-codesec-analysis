#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <limits.h>

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = ".*\\/([0-9]{4})\\/([0-9]{2})\\/([0-9]{2}).*";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        size_t year_len = matches[1].rm_eo - matches[1].rm_so;
        size_t month_len = matches[2].rm_eo - matches[2].rm_so;
        size_t day_len = matches[3].rm_eo - matches[3].rm_so;

        if (year_len == 4 && year_len < sizeof(char[5])) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char year_str[5];
            memmove(year_str, url + matches[1].rm_so, year_len);
            year_str[year_len] = '\0';
            long y = strtol(year_str, NULL, 10);
            if (y >= INT_MIN && y <= INT_MAX) {
                *year = (int)y;
            } else {
                *year = 0;
            }
        } else {
            *year = 0;
        }

        if (month_len == 2 && month_len < sizeof(char[3])) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char month_str[3];
            memmove(month_str, url + matches[2].rm_so, month_len);
            month_str[month_len] = '\0';
            long m = strtol(month_str, NULL, 10);
            if (m >= 1 && m <= 12) {
                *month = (int)m;
            } else {
                *month = 0;
            }
        } else {
            *month = 0;
        }

        if (day_len == 2 && day_len < sizeof(char[3])) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char day_str[3];
            memmove(day_str, url + matches[3].rm_so, day_len);
            day_str[day_len] = '\0';
            long d = strtol(day_str, NULL, 10);
            if (d >= 1 && d <= 31) {
                *day = (int)d;
            } else {
                *day = 0;
            }
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
    const char *url = "http://example.com/2023/10/05";
    int year, month, day;

    extract_date(url, &year, &month, &day);

    if (year && month && day) {
        printf("Year: %d, Month: %02d, Day: %02d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
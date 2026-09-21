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

        if (year_len >= 5 || month_len >= 3 || day_len >= 3) {
            return;
        }

        char year_str[5], month_str[3], day_str[3];
        strncpy(year_str, url + matches[1].rm_so, year_len);
        year_str[year_len] = '\0';
        strncpy(month_str, url + matches[2].rm_so, month_len);
        month_str[month_len] = '\0';
        strncpy(day_str, url + matches[3].rm_so, day_len);
        day_str[day_len] = '\0';

        long year_l = strtol(year_str, NULL, 10);
        long month_l = strtol(month_str, NULL, 10);
        long day_l = strtol(day_str, NULL, 10);

        if (year_l >= INT_MIN && year_l <= INT_MAX && month_l >= 1 && month_l <= 12 && day_l >= 1 && day_l <= 31) {
            *year = (int)year_l;
            *month = (int)month_l;
            *day = (int)day_l;
        }
    }

    regfree(&regex);
}

int main() {
    const char *url = "http://example.com/2023/10/05";
    int year = 0, month = 0, day = 0;

    extract_date(url, &year, &month, &day);

    if (year != 0 && month != 0 && day != 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
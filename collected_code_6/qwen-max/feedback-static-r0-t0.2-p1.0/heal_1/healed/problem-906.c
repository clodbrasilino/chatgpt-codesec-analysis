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
        char year_str[5], month_str[3], day_str[3];
        strncpy(year_str, url + matches[1].rm_so, 4);
        year_str[4] = '\0';
        strncpy(month_str, url + matches[2].rm_so, 2);
        month_str[2] = '\0';
        strncpy(day_str, url + matches[3].rm_so, 2);
        day_str[2] = '\0';

        long y = strtol(year_str, NULL, 10);
        long m = strtol(month_str, NULL, 10);
        long d = strtol(day_str, NULL, 10);

        if (y >= INT_MIN && y <= INT_MAX && m >= 1 && m <= 12 && d >= 1 && d <= 31) {
            *year = (int)y;
            *month = (int)m;
            *day = (int)d;
        } else {
            *year = 0;
            *month = 0;
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
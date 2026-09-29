#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>
#include <string.h>

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];

    if (regcomp(&regex, "/(\\d{4})/(\\d{2})/(\\d{2})/", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex.\n");
        exit(EXIT_FAILURE);
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        char year_str[5] = {0};
        char month_str[3] = {0};
        char day_str[3] = {0};

        strncpy(year_str, url + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        year_str[4] = '\0';

        strncpy(month_str, url + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        month_str[2] = '\0';

        strncpy(day_str, url + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
        day_str[2] = '\0';

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
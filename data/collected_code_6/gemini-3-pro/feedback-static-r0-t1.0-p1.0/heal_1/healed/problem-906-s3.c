#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{2})/([0-9]{2})/";
    int reti;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return;
    }

    *year = 0;
    *month = 0;
    *day = 0;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return;
    }

    reti = regexec(&regex, url, 4, matches, 0);
    if (!reti) {
        long parsed_year = strtol(url + matches[1].rm_so, NULL, 10);
        long parsed_month = strtol(url + matches[2].rm_so, NULL, 10);
        long parsed_day = strtol(url + matches[3].rm_so, NULL, 10);

        if (parsed_year >= 1000 && parsed_year <= 9999) {
            *year = (int)parsed_year;
        }
        if (parsed_month >= 1 && parsed_month <= 12) {
            *month = (int)parsed_month;
        }
        if (parsed_day >= 1 && parsed_day <= 31) {
            *day = (int)parsed_day;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *url = "https://example.com/posts/2023/10/25/my-new-article";
    int year = 0;
    int month = 0;
    int day = 0;

    extract_date_from_url(url, &year, &month, &day);

    if (year != 0 && month != 0 && day != 0) {
        printf("Year: %d\n", year);
        printf("Month: %d\n", month);
        printf("Day: %d\n", day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <regex.h>

void extract_date(char *url, char *year, char *month, char *day) {
    regex_t regex;
    regmatch_t matches[4];
    regcomp(&regex, "\\b(\\d{4})/(\\d{2})/(\\d{2})\\b", REG_EXTENDED);

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        int year_length = matches[1].rm_eo - matches[1].rm_so;
        int month_length = matches[2].rm_eo - matches[2].rm_so;
        int day_length = matches[3].rm_eo - matches[3].rm_so;

        strncpy(year, url + matches[1].rm_so, year_length);
        year[year_length] = '\0';

        strncpy(month, url + matches[2].rm_so, month_length);
        month[month_length] = '\0';

        strncpy(day, url + matches[3].rm_so, day_length);
        day[day_length] = '\0';
    }

    regfree(&regex);
}

int main() {
    char url[] = "https://example.com/2022/03/15/some-page";
    char year[5], month[3], day[3];

    extract_date(url, year, month, day);

    printf("Year: %s\n", year);
    printf("Month: %s\n", month);
    printf("Day: %s\n", day);

    return 0;
}
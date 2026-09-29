#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <errno.h>

void extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = ".*\\/([0-9]{4})\\/([0-9]{2})\\/([0-9]{2}).*";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        char year_str[5], month_str[3], day_str[3];
        strncpy(year_str, url + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        year_str[matches[1].rm_eo - matches[1].rm_so] = '\0';
        *year = strtol(year_str, NULL, 10);

        strncpy(month_str, url + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        month_str[matches[2].rm_eo - matches[2].rm_so] = '\0';
        *month = strtol(month_str, NULL, 10);

        strncpy(day_str, url + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
        day_str[matches[3].rm_eo - matches[3].rm_so] = '\0';
        *day = strtol(day_str, NULL, 10);
    }

    regfree(&regex);
}

int main() {
    const char *url = "http://example.com/2023/10/01";
    int year, month, day;

    extract_date_from_url(url, &year, &month, &day);

    if (year > 0 && month > 0 && day > 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
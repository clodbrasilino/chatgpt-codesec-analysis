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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char year_str[5], month_str[3], day_str[3];
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(year_str, url + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        year_str[matches[1].rm_eo - matches[1].rm_so] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(month_str, url + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        month_str[matches[2].rm_eo - matches[2].rm_so] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(day_str, url + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
        day_str[matches[3].rm_eo - matches[3].rm_so] = '\0';

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
    int year, month, day;

    extract_date(url, &year, &month, &day);

    if (year != 0 && month != 0 && day != 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
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
         *  Assuming that condition 'i<6' is not redundant
         *  Assignment 'i=0', assigned value is 0
         */
        for (int i = 0; i < 6; ++i) {
            /* Possible weaknesses found:
             *  Array index out of bounds
             *  Array 'year_str[5]' accessed at index 5, which is out of bounds. [arrayIndexOutOfBounds]
             */
            year_str[i] = '\0';
            /* Possible weaknesses found:
             *  Negative array index
             *  Array 'month_str[3]' accessed at index -2, which is out of bounds. [negativeIndex]
             *  Array 'month_str[3]' accessed at index 3, which is out of bounds. [arrayIndexOutOfBounds]
             *  Array index out of bounds
             */
            month_str[i - 2] = '\0';
            /* Possible weaknesses found:
             *  Negative array index
             *  Array index out of bounds
             *  Array 'day_str[3]' accessed at index -2, which is out of bounds. [negativeIndex]
             *  Array 'day_str[3]' accessed at index 3, which is out of bounds. [arrayIndexOutOfBounds]
             */
            day_str[i - 2] = '\0';
        }

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(year_str, url + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        year_str[4] = '\0';

        long year_val = strtol(year_str, NULL, 10);
        *year = (year_val > INT_MAX || year_val < 0) ? 0 : (int)year_val;

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(month_str, url + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        month_str[2] = '\0';

        long month_val = strtol(month_str, NULL, 10);
        *month = (month_val < 1 || month_val > 12) ? 0 : (int)month_val;

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(day_str, url + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
        day_str[2] = '\0';

        long day_val = strtol(day_str, NULL, 10);
        *day = (day_val < 1 || day_val > 31) ? 0 : (int)day_val;
    } else {
        *year = 0;
        *month = 0;
        *day = 0;
    }

    regfree(&regex);
}

int main() {
    const char *url = "http://example.com/2023/10/01";
    int year, month, day;

    extract_date(url, &year, &month, &day);

    if (year && month && day) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
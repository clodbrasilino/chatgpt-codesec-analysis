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
        year_str[4] = '\0';
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *year = (strtol(year_str, NULL, 10) > INT_MAX || strtol(year_str, NULL, 10) < 0) ? 0 : atoi(year_str);

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(month_str, url + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        month_str[2] = '\0';
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *month = (strtol(month_str, NULL, 10) > 12 || strtol(month_str, NULL, 10) < 1) ? 0 : atoi(month_str);

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(day_str, url + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
        day_str[2] = '\0';
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *day = (strtol(day_str, NULL, 10) > 31 || strtol(day_str, NULL, 10) < 1) ? 0 : atoi(day_str);
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
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = ".*\\/([0-9]{4})\\/([0-9]{2})\\/([0-9]{2}).*";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        *year = 0;
        *month = 0;
        *day = 0;
        return;
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[5];

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (matches[1].rm_so + 4 <= strlen(url)) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(buffer, url + matches[1].rm_so, 4);
            buffer[4] = '\0';
            int y = strtol(buffer, NULL, 10);
            /* Possible weaknesses found:
             *  'INT_MAX' undeclared (first use in this function)
             *  use of undeclared identifier 'INT_MAX'
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if (y > 0 && y <= INT_MAX) *year = y;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (matches[2].rm_so + 2 <= strlen(url)) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(buffer, url + matches[2].rm_so, 2);
            buffer[2] = '\0';
            int m = strtol(buffer, NULL, 10);
            if (m > 0 && m <= 12) *month = m;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (matches[3].rm_so + 2 <= strlen(url)) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(buffer, url + matches[3].rm_so, 2);
            buffer[2] = '\0';
            int d = strtol(buffer, NULL, 10);
            if (d > 0 && d <= 31) *day = d;
        }
    } else {
        *year = 0;
        *month = 0;
        *day = 0;
    }

    regfree(&regex);
}

int main() {
    const char *url = "http://example.com/2023/05/15";
    int year, month, day;

    extract_date(url, &year, &month, &day);

    if (year > 0 && month > 0 && day > 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
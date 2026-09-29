#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncpy'
  */

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = ".*\\/([0-9]{4})\\/([0-9]{2})\\/([0-9]{2}).*";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[5];
        int y, m, d;

        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'strncpy'
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strncpy' with type 'char *(char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        strncpy(buffer, url + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        buffer[matches[1].rm_eo - matches[1].rm_so] = '\0';
        y = strtol(buffer, NULL, 10);
        if (y <= 0 || y > INT_MAX) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(buffer, url + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        buffer[matches[2].rm_eo - matches[2].rm_so] = '\0';
        m = strtol(buffer, NULL, 10);
        if (m <= 0 || m > 12) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(buffer, url + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
        buffer[matches[3].rm_eo - matches[3].rm_so] = '\0';
        d = strtol(buffer, NULL, 10);
        if (d <= 0 || d > 31) {
            goto cleanup;
        }

        *year = y;
        *month = m;
        *day = d;
    } else {
        *year = 0;
        *month = 0;
        *day = 0;
    }

cleanup:
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
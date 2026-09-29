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

    if (regcomp(&regex, "/(\\d{4})/(\\d{2})/(\\d{2})/", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex.\n");
        exit(EXIT_FAILURE);
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char year_str[5] = {0};
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char month_str[3] = {0};
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char day_str[3] = {0};

        /* Possible weaknesses found:
         *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strncpy' with type 'char *(char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         *  include the header <string.h> or explicitly provide a declaration for 'strncpy'
         */
        strncpy(year_str, url + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(month_str, url + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(day_str, url + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);

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
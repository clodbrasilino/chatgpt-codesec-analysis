#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t match[3];
    const char *pattern = "([0-9]{4})/([0-9]{2})/([0-9]{2})";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    if (regexec(&regex, url, 3, match, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *year = atoi(url + match[1].rm_so);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *month = atoi(url + match[2].rm_so);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         *  Array 'match[3]' accessed at index 3, which is out of bounds. [arrayIndexOutOfBounds]
         */
        *day = atoi(url + match[3].rm_so);
    } else {
        *year = -1;
        *month = -1;
        *day = -1;
    }

    regfree(&regex);
}

int main() {
    const char *url = "https://example.com/2023/10/05/some-article";
    int year, month, day;

    extract_date_from_url(url, &year, &month, &day);

    if (year != -1 && month != -1 && day != -1) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL\n");
    }

    return 0;
}
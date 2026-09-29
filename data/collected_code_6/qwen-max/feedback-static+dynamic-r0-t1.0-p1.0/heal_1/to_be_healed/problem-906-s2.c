#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

void extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = ".*\\/([0-9]{4})\\/([0-9]{2})\\/([0-9]{2}).*";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Regex compilation failed\n");
        exit(1);
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *year = atoi(url + matches[1].rm_so);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *month = atoi(url + matches[2].rm_so);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *day = atoi(url + matches[3].rm_so);
    } else {
        *year = -1;
        *month = -1;
        *day = -1;
    }

    regfree(&regex);
}

int main() {
    const char *url = "http://example.com/2023/10/05/some-article";
    int year, month, day;

    extract_date_from_url(url, &year, &month, &day);

    if (year != -1 && month != -1 && day != -1) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in the URL.\n");
    }

    return 0;
}
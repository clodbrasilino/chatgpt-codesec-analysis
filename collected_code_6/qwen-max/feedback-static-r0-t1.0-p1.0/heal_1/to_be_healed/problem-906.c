#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[3];
    
    if (regcomp(&regex, "/(\\d{4})/(\\d{2})/(\\d{2})/", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex.\n");
        exit(EXIT_FAILURE);
    }
    
    if (regexec(&regex, url, 3, matches, 0) == 0) {
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
         *  Array 'matches[3]' accessed at index 3, which is out of bounds. [arrayIndexOutOfBounds]
         */
        *day = atoi(url + matches[3].rm_so);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{2})/([0-9]{2})/";
    int reti;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return;
    }

    *year = 0;
    *month = 0;
    *day = 0;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return;
    }

    reti = regexec(&regex, url, 4, matches, 0);
    if (!reti) {
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

        snprintf(year_str, sizeof(year_str), "%.*s", 
                 (int)(matches[1].rm_eo - matches[1].rm_so), url + matches[1].rm_so);
        snprintf(month_str, sizeof(month_str), "%.*s", 
                 (int)(matches[2].rm_eo - matches[2].rm_so), url + matches[2].rm_so);
        snprintf(day_str, sizeof(day_str), "%.*s", 
                 (int)(matches[3].rm_eo - matches[3].rm_so), url + matches[3].rm_so);

        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *year = atoi(year_str);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *month = atoi(month_str);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *day = atoi(day_str);
    }

    regfree(&regex);
}

int main(void) {
    const char *url = "https://example.com/posts/2023/10/25/my-new-article";
    int year = 0;
    int month = 0;
    int day = 0;

    extract_date_from_url(url, &year, &month, &day);

    if (year != 0 && month != 0 && day != 0) {
        printf("Year: %d\n", year);
        printf("Month: %d\n", month);
        printf("Day: %d\n", day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
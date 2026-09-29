#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>

int valid_date(int year, int month, int day) {
    if (year < 2000 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) {
        return 0;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) {
        return 0;
    }
    if (month == 2) {
        if (day > 29 || (day == 29 && (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0)))) {
            return 0;
        }
    }
    return 1;
}

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
        char str_year[5], str_month[3], str_day[3];
        for (int i = 0; i < 4; ++i) {
            str_year[i] = url[matches[1].rm_so + i];
        }
        str_year[4] = '\0';
        for (int i = 0; i < 2; ++i) {
            str_month[i] = url[matches[2].rm_so + i];
        }
        str_month[2] = '\0';
        for (int i = 0; i < 2; ++i) {
            str_day[i] = url[matches[3].rm_so + i];
        }
        str_day[2] = '\0';

        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *year = atoi(str_year);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *month = atoi(str_month);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        *day = atoi(str_day);

        if (!valid_date(*year, *month, *day)) {
            *year = 0;
            *month = 0;
            *day = 0;
        }
    }

    regfree(&regex);
}

int main() {
    const char *url = "http://example.com/2023/10/05";
    int year, month, day;

    extract_date(url, &year, &month, &day);

    if (year && month && day) {
        printf("Year: %d, Month: %02d, Day: %02d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
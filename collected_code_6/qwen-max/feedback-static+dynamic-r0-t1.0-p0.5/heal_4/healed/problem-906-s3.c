#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = ".*\\/([0-9]{4})\\/([0-9]{2})\\/([0-9]{2}).*";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        if (matches[1].rm_eo - matches[1].rm_so != 4 || matches[2].rm_eo - matches[2].rm_so != 2 || matches[3].rm_eo - matches[3].rm_so != 2) {
            regfree(&regex);
            return;
        }

        long y, m, d;
        y = strtol(url + matches[1].rm_so, NULL, 10);
        m = strtol(url + matches[2].rm_so, NULL, 10);
        d = strtol(url + matches[3].rm_so, NULL, 10);

        if (y > 0 && y <= INT_MAX && m >= 1 && m <= 12 && d >= 1 && d <= 31) {
            *year = (int)y;
            *month = (int)m;
            *day = (int)d;
        }
    }

    regfree(&regex);
}

int main() {
    const char *url = "http://example.com/2023/10/05/some-article";
    int year, month, day;

    extract_date(url, &year, &month, &day);

    if (year > 0 && month > 0 && day > 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found in URL.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = ".*\\/([0-9]{4})\\/([0-9]{2})\\/([0-9]{2}).*";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        char buffer[5];
        int y, m, d;

        strncpy(buffer, url + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        buffer[matches[1].rm_eo - matches[1].rm_so] = '\0';
        y = strtol(buffer, NULL, 10);
        if (y <= 0 || y > INT_MAX) {
            goto cleanup;
        }

        strncpy(buffer, url + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        buffer[matches[2].rm_eo - matches[2].rm_so] = '\0';
        m = strtol(buffer, NULL, 10);
        if (m <= 0 || m > 12) {
            goto cleanup;
        }

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
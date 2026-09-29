#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_date_from_url(const char *url, char **year, char **month, char **day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{2})/([0-9]{2})/";
    
    *year = NULL;
    *month = NULL;
    *day = NULL;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        int year_len = matches[1].rm_eo - matches[1].rm_so;
        int month_len = matches[2].rm_eo - matches[2].rm_so;
        int day_len = matches[3].rm_eo - matches[3].rm_so;

        *year = malloc(year_len + 1);
        *month = malloc(month_len + 1);
        *day = malloc(day_len + 1);

        if (*year && *month && *day) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(*year, url + matches[1].rm_so, year_len);
            (*year)[year_len] = '\0';

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(*month, url + matches[2].rm_so, month_len);
            (*month)[month_len] = '\0';

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(*day, url + matches[3].rm_so, day_len);
            (*day)[day_len] = '\0';
        } else {
            free(*year);
            free(*month);
            free(*day);
            *year = NULL;
            *month = NULL;
            *day = NULL;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *url = "https://example.com/blog/2023/10/25/my-post";
    char *year = NULL;
    char *month = NULL;
    char *day = NULL;

    extract_date_from_url(url, &year, &month, &day);

    if (year && month && day) {
        printf("Year: %s\n", year);
        printf("Month: %s\n", month);
        printf("Day: %s\n", day);
    } else {
        printf("Date not found or memory allocation failed.\n");
    }

    free(year);
    free(month);
    free(day);

    return 0;
}
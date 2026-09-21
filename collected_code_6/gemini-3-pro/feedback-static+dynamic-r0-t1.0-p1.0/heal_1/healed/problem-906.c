#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_date_from_url(const char *url, char **year, char **month, char **day) {
    if (!url || !year || !month || !day) {
        return;
    }

    *year = NULL;
    *month = NULL;
    *day = NULL;

    regex_t regex;
    const char *pattern = "/(19|20[0-9]{2})/(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/";
    regmatch_t pmatch[4];

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    if (regexec(&regex, url, 4, pmatch, 0) == 0) {
        size_t year_len = pmatch[1].rm_eo - pmatch[1].rm_so;
        size_t month_len = pmatch[2].rm_eo - pmatch[2].rm_so;
        size_t day_len = pmatch[3].rm_eo - pmatch[3].rm_so;

        *year = (char *)malloc(year_len + 1);
        *month = (char *)malloc(month_len + 1);
        *day = (char *)malloc(day_len + 1);

        if (*year && *month && *day) {
            memcpy(*year, url + pmatch[1].rm_so, year_len);
            (*year)[year_len] = '\0';

            memcpy(*month, url + pmatch[2].rm_so, month_len);
            (*month)[month_len] = '\0';

            memcpy(*day, url + pmatch[3].rm_so, day_len);
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
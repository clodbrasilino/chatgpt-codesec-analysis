#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_date_from_url(const char *url, char **year, char **month, char **day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{2})/([0-9]{2})/";
    int reti;

    *year = NULL;
    *month = NULL;
    *day = NULL;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return;
    }

    reti = regexec(&regex, url, 4, matches, 0);
    if (!reti) {
        if (matches[1].rm_so != -1 && matches[2].rm_so != -1 && matches[3].rm_so != -1) {
            size_t year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
            size_t month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
            size_t day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);

            if (year_len == 4 && month_len == 2 && day_len == 2) {
                *year = malloc(year_len + 1);
                *month = malloc(month_len + 1);
                *day = malloc(day_len + 1);

                if (*year && *month && *day) {
                    snprintf(*year, year_len + 1, "%.*s", (int)year_len, url + matches[1].rm_so);
                    snprintf(*month, month_len + 1, "%.*s", (int)month_len, url + matches[2].rm_so);
                    snprintf(*day, day_len + 1, "%.*s", (int)day_len, url + matches[3].rm_so);
                } else {
                    free(*year);
                    free(*month);
                    free(*day);
                    *year = NULL;
                    *month = NULL;
                    *day = NULL;
                }
            }
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
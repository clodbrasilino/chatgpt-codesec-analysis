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
    regmatch_t pmatch[4];
    const char *pattern = "/([0-9]{4})/([0-9]{2})/([0-9]{2})/";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    if (regexec(&regex, url, 4, pmatch, 0) == 0) {
        if (pmatch[1].rm_so != -1 && pmatch[1].rm_eo != -1) {
            size_t len = pmatch[1].rm_eo - pmatch[1].rm_so;
            *year = malloc(len + 1);
            if (*year) {
                snprintf(*year, len + 1, "%.*s", (int)len, url + pmatch[1].rm_so);
            }
        }
        if (pmatch[2].rm_so != -1 && pmatch[2].rm_eo != -1) {
            size_t len = pmatch[2].rm_eo - pmatch[2].rm_so;
            *month = malloc(len + 1);
            if (*month) {
                snprintf(*month, len + 1, "%.*s", (int)len, url + pmatch[2].rm_so);
            }
        }
        if (pmatch[3].rm_so != -1 && pmatch[3].rm_eo != -1) {
            size_t len = pmatch[3].rm_eo - pmatch[3].rm_so;
            *day = malloc(len + 1);
            if (*day) {
                snprintf(*day, len + 1, "%.*s", (int)len, url + pmatch[3].rm_so);
            }
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *url = "https://example.com/blog/2023/10/25/my-article";
    char *year = NULL;
    char *month = NULL;
    char *day = NULL;

    extract_date_from_url(url, &year, &month, &day);

    if (year) {
        printf("Year: %s\n", year);
        free(year);
    }
    if (month) {
        printf("Month: %s\n", month);
        free(month);
    }
    if (day) {
        printf("Day: %s\n", day);
        free(day);
    }

    return 0;
}
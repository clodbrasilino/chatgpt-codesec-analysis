#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int extract_date_from_url(const char *url, char *year, size_t year_sz, char *month, size_t month_sz, char *day, size_t day_sz) {
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    if (year_sz < 5 || month_sz < 3 || day_sz < 3) {
        return -1;
    }

    regex_t regex;
    const char *pattern = "([0-9]{4})[-/]([0-9]{2})[-/]([0-9]{2})";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    regmatch_t matches[4];
    int status = regexec(&regex, url, 4, matches, 0);
    
    if (status == 0) {
        int year_len = matches[1].rm_eo - matches[1].rm_so;
        int month_len = matches[2].rm_eo - matches[2].rm_so;
        int day_len = matches[3].rm_eo - matches[3].rm_so;

        if (year_len >= (int)year_sz || month_len >= (int)month_sz || day_len >= (int)day_sz) {
            regfree(&regex);
            return -1;
        }

        snprintf(year, year_sz, "%.*s", year_len, url + matches[1].rm_so);
        snprintf(month, month_sz, "%.*s", month_len, url + matches[2].rm_so);
        snprintf(day, day_sz, "%.*s", day_len, url + matches[3].rm_so);
    }

    regfree(&regex);

    return (status == 0) ? 0 : -1;
}

int main(void) {
    const char *url = "https://example.com/blog/2023/10/25/new-release";
    
    size_t year_sz = 32;
    size_t month_sz = 16;
    size_t day_sz = 16;
    
    char *year = calloc(year_sz, sizeof(char));
    char *month = calloc(month_sz, sizeof(char));
    char *day = calloc(day_sz, sizeof(char));

    if (year == NULL || month == NULL || day == NULL) {
        free(year);
        free(month);
        free(day);
        return EXIT_FAILURE;
    }

    int result = extract_date_from_url(url, year, year_sz, month, month_sz, day, day_sz);

    if (result == 0) {
        printf("Year: %s\n", year);
        printf("Month: %s\n", month);
        printf("Day: %s\n", day);
    } else {
        printf("Failed to extract date from URL.\n");
    }

    free(year);
    free(month);
    free(day);

    return (result == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
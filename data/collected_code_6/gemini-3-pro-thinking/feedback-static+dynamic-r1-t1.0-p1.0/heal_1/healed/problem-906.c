#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int parse_matched_int(const char *url, regmatch_t match) {
    int val = 0;
    for (regoff_t i = match.rm_so; i < match.rm_eo; i++) {
        val = val * 10 + (url[i] - '0');
    }
    return val;
}

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    int status;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    status = regcomp(&regex, "([0-9]{4})[-/]([0-9]{2})[-/]([0-9]{2})", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, url, 4, matches, 0);
    if (status != 0) {
        regfree(&regex);
        return -1;
    }

    *year = parse_matched_int(url, matches[1]);
    *month = parse_matched_int(url, matches[2]);
    *day = parse_matched_int(url, matches[3]);

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2023/10/24/article-name",
        "https://example.com/news/2022-01-05/index.html",
        "https://example.com/no-date-here",
        NULL
    };

    for (int i = 0; test_urls[i] != NULL; i++) {
        int year = 0;
        int month = 0;
        int day = 0;
        
        int result = extract_date_from_url(test_urls[i], &year, &month, &day);
        
        if (result == 0) {
            printf("URL: %s\nYear: %d, Month: %d, Day: %d\n\n", test_urls[i], year, month, day);
        } else {
            printf("URL: %s\nNo valid date found.\n\n", test_urls[i]);
        }
    }

    return 0;
}
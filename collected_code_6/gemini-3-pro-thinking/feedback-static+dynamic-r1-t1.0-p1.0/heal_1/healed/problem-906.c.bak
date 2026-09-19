#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    regex_t regex;
    if (regcomp(&regex, "([0-9]{4})[-/]([0-9]{2})[-/]([0-9]{2})", REG_EXTENDED) != 0) {
        return -1;
    }

    regmatch_t matches[4];
    if (regexec(&regex, url, 4, matches, 0) != 0) {
        regfree(&regex);
        return -1;
    }

    char buffer[5];

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(matches[1].rm_eo - matches[1].rm_so), url + matches[1].rm_so);
    *year = (int)strtol(buffer, NULL, 10);

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(matches[2].rm_eo - matches[2].rm_so), url + matches[2].rm_so);
    *month = (int)strtol(buffer, NULL, 10);

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(matches[3].rm_eo - matches[3].rm_so), url + matches[3].rm_so);
    *day = (int)strtol(buffer, NULL, 10);

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
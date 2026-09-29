#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int extract_date_from_url(const char *url, char *year, size_t year_sz, char *month, size_t month_sz, char *day, size_t day_sz) {
    if (!url || !year || !month || !day || year_sz < 5 || month_sz < 3 || day_sz < 3) {
        return -1;
    }

    regex_t regex;
    const char *pattern = "([0-9]{4})[-/]([0-9]{2})[-/]([0-9]{2})";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    regmatch_t matches[4];
    if (regexec(&regex, url, 4, matches, 0) != 0) {
        regfree(&regex);
        return -1;
    }

    size_t y_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    size_t m_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    size_t d_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);

    if (y_len >= year_sz || m_len >= month_sz || d_len >= day_sz) {
        regfree(&regex);
        return -1;
    }

    memcpy(year, url + matches[1].rm_so, y_len);
    year[y_len] = '\0';

    memcpy(month, url + matches[2].rm_so, m_len);
    month[m_len] = '\0';

    memcpy(day, url + matches[3].rm_so, d_len);
    day[d_len] = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *url = "https://example.com/articles/2023/10/27/secure-coding";
    char year[5];
    char month[3];
    char day[3];

    if (extract_date_from_url(url, year, sizeof(year), month, sizeof(month), day, sizeof(day)) == 0) {
        printf("%s-%s-%s\n", year, month, day);
    } else {
        fprintf(stderr, "Failed to extract date from URL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
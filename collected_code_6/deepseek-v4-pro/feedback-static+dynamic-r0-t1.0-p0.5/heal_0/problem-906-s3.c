#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "/([0-9]{4})/([0-9]{1,2})/([0-9]{1,2})(/|$)";
    int ret;
    char year_str[5];
    char month_str[3];
    char day_str[3];

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    if (matches[1].rm_so == -1 || matches[2].rm_so == -1 || matches[3].rm_so == -1) {
        regfree(&regex);
        return -1;
    }

    size_t year_len = matches[1].rm_eo - matches[1].rm_so;
    size_t month_len = matches[2].rm_eo - matches[2].rm_so;
    size_t day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len >= sizeof(year_str) || month_len >= sizeof(month_str) || day_len >= sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }

    memcpy(year_str, url + matches[1].rm_so, year_len);
    year_str[year_len] = '\0';
    memcpy(month_str, url + matches[2].rm_so, month_len);
    month_str[month_len] = '\0';
    memcpy(day_str, url + matches[3].rm_so, day_len);
    day_str[day_len] = '\0';

    *year = atoi(year_str);
    *month = atoi(month_str);
    *day = atoi(day_str);

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *url = "https://example.com/2024/03/15/article";
    int year, month, day;

    if (extract_date_from_url(url, &year, &month, &day) == 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("No date found in URL\n");
    }

    return 0;
}
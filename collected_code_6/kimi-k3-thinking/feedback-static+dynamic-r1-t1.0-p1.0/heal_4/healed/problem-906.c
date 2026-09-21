#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define YEAR_REQUIRED_SIZE 5
#define MONTH_REQUIRED_SIZE 3
#define DAY_REQUIRED_SIZE 3
#define MAX_MATCHES 4

int extract_date_from_url(const char *url, char *year, size_t year_size,
                          char *month, size_t month_size,
                          char *day, size_t day_size)
{
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    const char *pattern = "([0-9]{4})/([0-9]{2})/([0-9]{2})";
    int status;
    size_t len;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    if (year_size < YEAR_REQUIRED_SIZE || month_size < MONTH_REQUIRED_SIZE ||
        day_size < DAY_REQUIRED_SIZE) {
        return -1;
    }

    year[0] = '\0';
    month[0] = '\0';
    day[0] = '\0';

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, url, MAX_MATCHES, matches, 0);
    if (status != 0) {
        regfree(&regex);
        return -1;
    }

    if (matches[1].rm_so < 0 || matches[1].rm_eo <= matches[1].rm_so ||
        matches[2].rm_so < 0 || matches[2].rm_eo <= matches[2].rm_so ||
        matches[3].rm_so < 0 || matches[3].rm_eo <= matches[3].rm_so) {
        regfree(&regex);
        return -1;
    }

    len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    if (len != 4 || len + 1 > year_size) {
        regfree(&regex);
        return -1;
    }
    memcpy(year, url + matches[1].rm_so, len);
    year[len] = '\0';

    len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    if (len != 2 || len + 1 > month_size) {
        regfree(&regex);
        return -1;
    }
    memcpy(month, url + matches[2].rm_so, len);
    month[len] = '\0';

    len = (size_t)(matches[3].rm_eo - matches[3].rm_so);
    if (len != 2 || len + 1 > day_size) {
        regfree(&regex);
        return -1;
    }
    memcpy(day, url + matches[3].rm_so, len);
    day[len] = '\0';

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *url = "https://example.com/2024/01/15/article";
    char year[YEAR_REQUIRED_SIZE] = {0};
    char month[MONTH_REQUIRED_SIZE] = {0};
    char day[DAY_REQUIRED_SIZE] = {0};

    if (extract_date_from_url(url, year, sizeof(year),
                              month, sizeof(month),
                              day, sizeof(day)) == 0) {
        printf("Year: %s\n", year);
        printf("Month: %s\n", month);
        printf("Day: %s\n", day);
    } else {
        fprintf(stderr, "Failed to extract date from URL\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
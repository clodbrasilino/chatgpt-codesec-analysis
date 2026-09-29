#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define YEAR_SIZE 5
#define MONTH_SIZE 3
#define DAY_SIZE 3
#define MAX_MATCHES 4
#define MAX_URL_LENGTH 2048

int extract_date_from_url(const char *url, char *year, size_t year_size,
                          char *month, size_t month_size,
                          char *day, size_t day_size)
{
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    const char *pattern = "([0-9]{4})/([0-9]{2})/([0-9]{2})";
    int status;
    size_t len;
    size_t url_len;
    int written;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    if (year_size < YEAR_SIZE || month_size < MONTH_SIZE || day_size < DAY_SIZE) {
        return -1;
    }

    url_len = strnlen(url, MAX_URL_LENGTH);
    if (url_len == 0 || url_len >= MAX_URL_LENGTH) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, url, MAX_MATCHES, matches, 0);
    if (status != 0) {
        regfree(&regex);
        return -1;
    }

    if (matches[1].rm_so < 0 || matches[2].rm_so < 0 || matches[3].rm_so < 0 ||
        matches[1].rm_eo < matches[1].rm_so ||
        matches[2].rm_eo < matches[2].rm_so ||
        matches[3].rm_eo < matches[3].rm_so ||
        (size_t)matches[1].rm_eo > url_len ||
        (size_t)matches[2].rm_eo > url_len ||
        (size_t)matches[3].rm_eo > url_len) {
        regfree(&regex);
        return -1;
    }

    len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    if (len == 0 || len + 1 > year_size) {
        regfree(&regex);
        return -1;
    }
    written = snprintf(year, year_size, "%.*s", (int)len, url + matches[1].rm_so);
    if (written < 0 || (size_t)written >= year_size) {
        regfree(&regex);
        return -1;
    }

    len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    if (len == 0 || len + 1 > month_size) {
        regfree(&regex);
        return -1;
    }
    written = snprintf(month, month_size, "%.*s", (int)len, url + matches[2].rm_so);
    if (written < 0 || (size_t)written >= month_size) {
        regfree(&regex);
        return -1;
    }

    len = (size_t)(matches[3].rm_eo - matches[3].rm_so);
    if (len == 0 || len + 1 > day_size) {
        regfree(&regex);
        return -1;
    }
    written = snprintf(day, day_size, "%.*s", (int)len, url + matches[3].rm_so);
    if (written < 0 || (size_t)written >= day_size) {
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *url = "https://example.com/2024/01/15/article";
    char year[YEAR_SIZE] = {0};
    char month[MONTH_SIZE] = {0};
    char day[DAY_SIZE] = {0};

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <stdint.h>

#define DATE_PATTERN "[0-9]{4}-[0-9]{2}-[0-9]{2}"
#define MAX_URL_LEN 4096
#define DATE_STR_SIZE 16

int extract_date_from_url(const char *url, int *year, int *month, int *day)
{
    regex_t regex;
    regmatch_t matches[1];
    char date_str[DATE_STR_SIZE];
    int ret;
    size_t len;
    size_t url_len;
    size_t match_offset;
    int temp_year, temp_month, temp_day;

    if (url == NULL || year == NULL || month == NULL || day == NULL)
    {
        return -1;
    }

    url_len = strnlen(url, MAX_URL_LEN + 1);
    if (url_len == 0 || url_len > MAX_URL_LEN)
    {
        return -1;
    }

    ret = regcomp(&regex, DATE_PATTERN, REG_EXTENDED);
    if (ret != 0)
    {
        return -1;
    }

    ret = regexec(&regex, url, 1, matches, 0);
    if (ret != 0)
    {
        regfree(&regex);
        return -1;
    }

    if (matches[0].rm_so < 0 || matches[0].rm_eo < 0)
    {
        regfree(&regex);
        return -1;
    }

    if (matches[0].rm_eo <= matches[0].rm_so)
    {
        regfree(&regex);
        return -1;
    }

    match_offset = (size_t)matches[0].rm_so;
    if (match_offset >= url_len)
    {
        regfree(&regex);
        return -1;
    }

    len = (size_t)(matches[0].rm_eo - matches[0].rm_so);
    if (len != 10 || len >= DATE_STR_SIZE)
    {
        regfree(&regex);
        return -1;
    }

    if (match_offset + len > url_len)
    {
        regfree(&regex);
        return -1;
    }

    if (len >= sizeof(date_str))
    {
        regfree(&regex);
        return -1;
    }

    memcpy(date_str, url + match_offset, len);
    date_str[len] = '\0';

    if (sscanf(date_str, "%4d-%2d-%2d", &temp_year, &temp_month, &temp_day) != 3)
    {
        regfree(&regex);
        return -1;
    }

    if (temp_year < 1900 || temp_year > 2100 || 
        temp_month < 1 || temp_month > 12 || 
        temp_day < 1 || temp_day > 31)
    {
        regfree(&regex);
        return -1;
    }

    if ((temp_month == 4 || temp_month == 6 || temp_month == 9 || temp_month == 11) && temp_day > 30)
    {
        regfree(&regex);
        return -1;
    }

    if (temp_month == 2)
    {
        int is_leap = (temp_year % 4 == 0 && temp_year % 100 != 0) || (temp_year % 400 == 0);
        if (temp_day > (is_leap ? 29 : 28))
        {
            regfree(&regex);
            return -1;
        }
    }

    *year = temp_year;
    *month = temp_month;
    *day = temp_day;

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *url = "https://example.com/2024-01-15/article.html";
    int year = 0;
    int month = 0;
    int day = 0;

    if (extract_date_from_url(url, &year, &month, &day) == 0)
    {
        printf("Year: %d\n", year);
        printf("Month: %d\n", month);
        printf("Day: %d\n", day);
    }
    else
    {
        fprintf(stderr, "Failed to extract date from URL\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
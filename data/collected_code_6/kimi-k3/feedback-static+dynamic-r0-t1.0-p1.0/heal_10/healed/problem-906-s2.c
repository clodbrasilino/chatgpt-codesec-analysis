#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

#define MAX_URL_LEN 2048
#define MAX_MATCHES 4
#define YEAR_BUF_SIZE 8
#define MONTH_BUF_SIZE 4
#define DAY_BUF_SIZE 4

typedef struct {
    int year;
    int month;
    int day;
    int valid;
} DateComponents;

static int safe_str_to_int(const char *str, int *result) {
    char *endptr;
    long val;
    
    if (str == NULL || result == NULL) {
        return -1;
    }
    
    errno = 0;
    val = strtol(str, &endptr, 10);
    
    if (errno != 0 || endptr == str || *endptr != '\0') {
        return -1;
    }
    
    if (val > INT_MAX || val < INT_MIN) {
        return -1;
    }
    
    *result = (int)val;
    return 0;
}

static int safe_copy_substring(char *dest, size_t dest_size, const char *src, size_t len) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }
    
    if (len >= dest_size) {
        return -1;
    }
    
    if (len > 0) {
        memcpy(dest, src, len);
    }
    dest[len] = '\0';
    
    return 0;
}

static size_t safe_strnlen(const char *str, size_t maxlen) {
    size_t len = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    
    return len;
}

int extract_date_from_url(const char *url, DateComponents *date) {
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    const char *pattern = "([0-9]{4})[-/]([0-9]{1,2})[-/]([0-9]{1,2})";
    int ret;
    char year_str[YEAR_BUF_SIZE] = {0};
    char month_str[MONTH_BUF_SIZE] = {0};
    char day_str[DAY_BUF_SIZE] = {0};
    size_t year_len, month_len, day_len;
    size_t url_len;
    
    if (url == NULL || date == NULL) {
        return -1;
    }
    
    url_len = safe_strnlen(url, MAX_URL_LEN + 1);
    if (url_len > MAX_URL_LEN || url_len == 0) {
        return -1;
    }
    
    date->valid = 0;
    date->year = 0;
    date->month = 0;
    date->day = 0;
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }
    
    ret = regexec(&regex, url, MAX_MATCHES, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }
    
    if (matches[1].rm_so == -1 || matches[2].rm_so == -1 || matches[3].rm_so == -1) {
        regfree(&regex);
        return -1;
    }
    
    if (matches[1].rm_so < 0 || matches[1].rm_eo < 0 ||
        matches[2].rm_so < 0 || matches[2].rm_eo < 0 ||
        matches[3].rm_so < 0 || matches[3].rm_eo < 0) {
        regfree(&regex);
        return -1;
    }
    
    if ((size_t)matches[1].rm_eo > url_len ||
        (size_t)matches[2].rm_eo > url_len ||
        (size_t)matches[3].rm_eo > url_len) {
        regfree(&regex);
        return -1;
    }
    
    if (matches[1].rm_eo < matches[1].rm_so ||
        matches[2].rm_eo < matches[2].rm_so ||
        matches[3].rm_eo < matches[3].rm_so) {
        regfree(&regex);
        return -1;
    }
    
    year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);
    
    if (year_len != 4 || month_len < 1 || month_len > 2 || day_len < 1 || day_len > 2) {
        regfree(&regex);
        return -1;
    }
    
    if (year_len >= sizeof(year_str) || month_len >= sizeof(month_str) || day_len >= sizeof(day_str)) {
        regfree(&regex);
        return -1;
    }
    
    if (safe_copy_substring(year_str, sizeof(year_str), url + matches[1].rm_so, year_len) != 0 ||
        safe_copy_substring(month_str, sizeof(month_str), url + matches[2].rm_so, month_len) != 0 ||
        safe_copy_substring(day_str, sizeof(day_str), url + matches[3].rm_so, day_len) != 0) {
        regfree(&regex);
        return -1;
    }
    
    if (safe_str_to_int(year_str, &date->year) != 0 ||
        safe_str_to_int(month_str, &date->month) != 0 ||
        safe_str_to_int(day_str, &date->day) != 0) {
        regfree(&regex);
        return -1;
    }
    
    if (date->year < 1900 || date->year > 2100 ||
        date->month < 1 || date->month > 12 ||
        date->day < 1 || date->day > 31) {
        regfree(&regex);
        return -1;
    }
    
    date->valid = 1;
    regfree(&regex);
    return 0;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2024/01/15/article",
        "https://example.com/blog/2023-12-25/post",
        "https://example.com/invalid/path",
        "https://example.com/2024/13/45/invalid"
    };
    
    size_t num_urls = sizeof(test_urls) / sizeof(test_urls[0]);
    
    for (size_t i = 0; i < num_urls; i++) {
        DateComponents date = {0};
        
        if (extract_date_from_url(test_urls[i], &date) == 0 && date.valid) {
            printf("URL: %s\n", test_urls[i]);
            printf("Year: %d, Month: %d, Day: %d\n\n", 
                   date.year, date.month, date.day);
        } else {
            printf("URL: %s\n", test_urls[i]);
            printf("No valid date found\n\n");
        }
    }
    
    return 0;
}
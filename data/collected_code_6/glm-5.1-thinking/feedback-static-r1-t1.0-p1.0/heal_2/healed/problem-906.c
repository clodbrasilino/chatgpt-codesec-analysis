#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct {
    int year;
    int month;
    int day;
    int success;
} DateResult;

static int parse_match_int(const char *str, size_t len) {
    int val = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') break;
        val = val * 10 + (str[i] - '0');
    }
    return val;
}

DateResult extract_date_from_url(const char *url) {
    DateResult result = {0, 0, 0, 0};

    if (url == NULL) {
        return result;
    }

    regex_t regex;
    int ret;
    const char *pattern = "([0-9]{4})[-/]([0-9]{1,2})[-/]([0-9]{1,2})";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return result;
    }

    regmatch_t matches[4];

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return result;
    }

    if (matches[1].rm_so != -1) {
        size_t len = matches[1].rm_eo - matches[1].rm_so;
        result.year = parse_match_int(url + matches[1].rm_so, len);
    }

    if (matches[2].rm_so != -1) {
        size_t len = matches[2].rm_eo - matches[2].rm_so;
        result.month = parse_match_int(url + matches[2].rm_so, len);
    }

    if (matches[3].rm_so != -1) {
        size_t len = matches[3].rm_eo - matches[3].rm_so;
        result.day = parse_match_int(url + matches[3].rm_so, len);
    }

    regfree(&regex);
    result.success = 1;

    return result;
}

int main(void) {
    const char *url1 = "https://example.com/archive/2023/10/25/article.html";
    DateResult res1 = extract_date_from_url(url1);

    if (res1.success) {
        printf("Extracted: Year=%d, Month=%d, Day=%d\n", res1.year, res1.month, res1.day);
    } else {
        printf("Failed to extract date from url1.\n");
    }

    const char *url2 = "https://example.com/archive/no-date-here";
    DateResult res2 = extract_date_from_url(url2);

    if (res2.success) {
        printf("Extracted: Year=%d, Month=%d, Day=%d\n", res2.year, res2.month, res2.day);
    } else {
        printf("Failed to extract date from url2.\n");
    }

    DateResult res3 = extract_date_from_url(NULL);

    if (res3.success) {
        printf("Extracted: Year=%d, Month=%d, Day=%d\n", res3.year, res3.month, res3.day);
    } else {
        printf("Failed to extract date from NULL.\n");
    }

    return 0;
}
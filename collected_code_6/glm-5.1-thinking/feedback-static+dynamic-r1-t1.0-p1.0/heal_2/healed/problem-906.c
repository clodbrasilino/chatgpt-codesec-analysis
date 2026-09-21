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
        int val = 0;
        for (int i = matches[1].rm_so; i < matches[1].rm_eo; i++) {
            val = val * 10 + (url[i] - '0');
        }
        result.year = val;
    }

    if (matches[2].rm_so != -1) {
        int val = 0;
        for (int i = matches[2].rm_so; i < matches[2].rm_eo; i++) {
            val = val * 10 + (url[i] - '0');
        }
        result.month = val;
    }

    if (matches[3].rm_so != -1) {
        int val = 0;
        for (int i = matches[3].rm_so; i < matches[3].rm_eo; i++) {
            val = val * 10 + (url[i] - '0');
        }
        result.day = val;
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
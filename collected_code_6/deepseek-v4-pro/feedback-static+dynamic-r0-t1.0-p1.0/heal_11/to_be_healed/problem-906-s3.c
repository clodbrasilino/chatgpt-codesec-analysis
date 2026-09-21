#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int is_valid_date(int year, int month, int day) {
    if (month < 1 || month > 12) return 0;
    if (day < 1) return 0;

    const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_day = days_in_month[month - 1];

    if (month == 2 && is_leap_year(year)) {
        max_day = 29;
    }

    return day <= max_day;
}

static int parse_segment(const char *start, size_t len, long *result) {
    if (len == 0 || len > 4) return -1;

    char *buf = malloc(len + 1);
    if (buf == NULL) return -1;

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buf, start, len);
    buf[len] = '\0';

    char *endptr;
    errno = 0;
    *result = strtol(buf, &endptr, 10);

    int status = 0;
    if (errno != 0 || endptr == buf || *endptr != '\0') {
        status = -1;
    }

    free(buf);
    return status;
}

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    const char *p = url;

    while (*p != '\0' && *p != '/') p++;
    while (*p == '/') p++;

    while (*p != '\0') {
        const char *segment_start = p;
        while (*p != '\0' && *p != '/') p++;

        size_t seg_len = (size_t)(p - segment_start);

        long val;
        if (parse_segment(segment_start, seg_len, &val) != 0) {
            while (*p == '/') p++;
            continue;
        }

        if (val >= 1 && val <= 9999) {
            *year = (int)val;

            while (*p == '/') p++;
            const char *month_start = p;
            while (*p != '\0' && *p != '/') p++;
            size_t month_len = (size_t)(p - month_start);

            long month_val;
            if (parse_segment(month_start, month_len, &month_val) != 0 ||
                month_val < 1 || month_val > 12) {
                return -5;
            }

            while (*p == '/') p++;
            const char *day_start = p;
            while (*p != '\0' && *p != '/') p++;
            size_t day_len = (size_t)(p - day_start);

            long day_val;
            if (parse_segment(day_start, day_len, &day_val) != 0 ||
                day_val < 1 || day_val > 31) {
                return -5;
            }

            *month = (int)month_val;
            *day = (int)day_val;

            if (!is_valid_date(*year, *month, *day)) {
                return -6;
            }

            return 0;
        }

        while (*p == '/') p++;
    }

    return -3;
}

int main(void) {
    const char *test_urls[] = {
        "https://example.com/2024/03/15/article",
        "http://test.org/2023/12/01/post",
        "https://site.com/2022/7/5/news",
        "https://invalid.com/no/date/here",
        NULL
    };

    int year, month, day;

    for (int i = 0; test_urls[i] != NULL; i++) {
        printf("URL: %s\n", test_urls[i]);
        int result = extract_date_from_url(test_urls[i], &year, &month, &day);
        if (result == 0) {
            printf("Extracted date: %04d-%02d-%02d\n", year, month, day);
        } else {
            printf("Failed to extract date (error code: %d)\n", result);
        }
        printf("\n");
    }

    return 0;
}
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define YEAR_PART_LEN 4
#define MONTH_DAY_PART_MAX_LEN 2
#define NUM_MATCH_GROUPS 4

static int extract_date_from_url(const char *url, int *year, int *month, int *day)
{
    regex_t regex;
    regmatch_t matches[NUM_MATCH_GROUPS];
    const char *pattern = "([0-9]{4})[-/]([0-9]{1,2})[-/]([0-9]{1,2})";
    const size_t max_part_len[NUM_MATCH_GROUPS - 1] = {
        YEAR_PART_LEN, MONTH_DAY_PART_MAX_LEN, MONTH_DAY_PART_MAX_LEN
    };
    int values[NUM_MATCH_GROUPS - 1] = { 0, 0, 0 };
    int status = -1;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    if (regexec(&regex, url, NUM_MATCH_GROUPS, matches, 0) == 0) {
        int valid = 1;

        for (int i = 1; i < NUM_MATCH_GROUPS && valid; i++) {
            regoff_t start = matches[i].rm_so;
            regoff_t end = matches[i].rm_eo;
            char *buffer;
            size_t len;
            size_t max_len = max_part_len[i - 1];
            char *endptr = NULL;
            long value;
            int parse_ok;

            if (start < 0 || end < 0 || end <= start) {
                valid = 0;
                break;
            }

            len = (size_t)(end - start);
            if (len > max_len) {
                valid = 0;
                break;
            }

            buffer = malloc(len + 1);
            if (buffer == NULL) {
                valid = 0;
                break;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer, url + start, len);
            buffer[len] = '\0';

            errno = 0;
            value = strtol(buffer, &endptr, 10);
            parse_ok = (errno == 0 && endptr != buffer && *endptr == '\0' &&
                        value >= 0 && value <= INT_MAX);
            free(buffer);

            if (!parse_ok) {
                valid = 0;
                break;
            }

            values[i - 1] = (int)value;
        }

        if (valid &&
            values[0] >= 1900 && values[0] <= 2100 &&
            values[1] >= 1 && values[1] <= 12 &&
            values[2] >= 1 && values[2] <= 31) {
            *year = values[0];
            *month = values[1];
            *day = values[2];
            status = 0;
        }
    }

    regfree(&regex);
    return status;
}

int main(void)
{
    const char *url = "https://example.com/2023/05/15/sample-article";
    int year = 0;
    int month = 0;
    int day = 0;

    if (extract_date_from_url(url, &year, &month, &day) == 0) {
        printf("URL:   %s\n", url);
        printf("Year:  %d\n", year);
        printf("Month: %d\n", month);
        printf("Day:   %d\n", day);
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "Error: no valid date found in URL.\n");
    return EXIT_FAILURE;
}
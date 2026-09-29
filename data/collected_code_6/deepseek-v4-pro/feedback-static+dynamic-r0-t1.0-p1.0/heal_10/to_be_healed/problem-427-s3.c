#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>

static int validate_and_extract(const char *input, char *year, size_t year_size, char *month, size_t month_size, char *day, size_t day_size) {
    regex_t regex;
    regmatch_t matches[4];
    int ret;
    size_t input_len;
    size_t year_len, month_len, day_len;

    if (!input || !year || !month || !day) return -5;
    
    input_len = strnlen(input, 11);
    if (input_len == 0 || input_len > 10) return -5;
    
    if (year_size < 5 || month_size < 3 || day_size < 3) return -5;

    ret = regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED);
    if (ret) return -1;

    ret = regexec(&regex, input, 4, matches, 0);
    if (ret == REG_NOMATCH) {
        regfree(&regex);
        return -2;
    }
    if (ret != 0) {
        regfree(&regex);
        return -3;
    }

    if (matches[0].rm_so != 0 || matches[0].rm_eo != (regoff_t)input_len) {
        regfree(&regex);
        return -4;
    }

    year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);

    if (year_len >= year_size || month_len >= month_size || day_len >= day_size) {
        regfree(&regex);
        return -5;
    }

    if ((size_t)(matches[1].rm_so + year_len) > input_len || year_len == 0) {
        regfree(&regex);
        return -5;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(year, input + matches[1].rm_so, year_len);
    year[year_len] = '\0';

    if ((size_t)(matches[2].rm_so + month_len) > input_len || month_len == 0) {
        regfree(&regex);
        return -5;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(month, input + matches[2].rm_so, month_len);
    month[month_len] = '\0';

    if ((size_t)(matches[3].rm_so + day_len) > input_len || day_len == 0) {
        regfree(&regex);
        return -5;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(day, input + matches[3].rm_so, day_len);
    day[day_len] = '\0';

    regfree(&regex);
    return 0;
}

int convert_date_format(const char *input, char *output, size_t output_size) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char year[5];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[3];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char day[3];
    int ret;
    size_t input_len;
    int written;

    if (!input || !output || output_size == 0) {
        return -6;
    }

    input_len = strnlen(input, 11);
    if (input_len == 0 || input_len > 10) {
        return -7;
    }

    if (output_size < 11) {
        return -5;
    }

    memset(year, 0, sizeof(year));
    memset(month, 0, sizeof(month));
    memset(day, 0, sizeof(day));

    ret = validate_and_extract(input, year, sizeof(year), month, sizeof(month), day, sizeof(day));
    if (ret != 0) {
        return ret;
    }

    written = snprintf(output, output_size, "%s-%s-%s", day, month, year);
    if (written < 0 || (size_t)written >= output_size) {
        return -5;
    }

    return 0;
}

int main(void) {
    const char *input_dates[] = {
        "2023-12-25",
        "1999-01-01",
        "invalid-date",
        "2023-13-45",
        "2023-1-01"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[16];
    size_t i;
    size_t num_dates = sizeof(input_dates) / sizeof(input_dates[0]);

    for (i = 0; i < num_dates; i++) {
        int result = convert_date_format(input_dates[i], output, sizeof(output));
        if (result == 0) {
            printf("%s -> %s\n", input_dates[i], output);
        } else {
            printf("%s -> conversion failed (code %d)\n", input_dates[i], result);
        }
    }

    return EXIT_SUCCESS;
}
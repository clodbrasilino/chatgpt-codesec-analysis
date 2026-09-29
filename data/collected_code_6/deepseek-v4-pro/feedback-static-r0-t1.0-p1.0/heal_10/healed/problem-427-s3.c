#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    int ret;
    size_t len;

    if (input == NULL || output == NULL || output_size == 0) {
        return -6;
    }

    len = strnlen(input, 12);
    if (len == 0 || len > 10) {
        return -7;
    }

    if (output_size < 11) {
        return -5;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return -1;
    }

    ret = regexec(&regex, input, 4, matches, 0);
    if (ret == REG_NOMATCH) {
        regfree(&regex);
        return -2;
    }
    if (ret != 0) {
        regfree(&regex);
        return -3;
    }

    if (matches[0].rm_so != 0 || matches[0].rm_eo != (regoff_t)len) {
        regfree(&regex);
        return -4;
    }

    {
        size_t year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
        size_t month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
        size_t day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);
        const char *year_ptr = input + matches[1].rm_so;
        const char *month_ptr = input + matches[2].rm_so;
        const char *day_ptr = input + matches[3].rm_so;
        size_t needed;

        if (year_len > 4 || month_len > 2 || day_len > 2) {
            regfree(&regex);
            return -8;
        }

        needed = day_len + 1 + month_len + 1 + year_len + 1;
        if (needed > output_size) {
            regfree(&regex);
            return -5;
        }

        snprintf(output, output_size, "%.*s-%.*s-%.*s",
                 (int)day_len, day_ptr,
                 (int)month_len, month_ptr,
                 (int)year_len, year_ptr);
    }

    regfree(&regex);
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
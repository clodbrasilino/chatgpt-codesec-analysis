#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int validate_and_extract(const char *input, char *year, size_t year_size, char *month, size_t month_size, char *day, size_t day_size) {
    regex_t regex;
    regmatch_t matches[4];
    int ret;
    size_t input_len;

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

    snprintf(year, year_size, "%.*s", (int)(matches[1].rm_eo - matches[1].rm_so), input + matches[1].rm_so);
    snprintf(month, month_size, "%.*s", (int)(matches[2].rm_eo - matches[2].rm_so), input + matches[2].rm_so);
    snprintf(day, day_size, "%.*s", (int)(matches[3].rm_eo - matches[3].rm_so), input + matches[3].rm_so);

    regfree(&regex);
    return 0;
}

int convert_date_format(const char *input, char *output, size_t output_size) {
    char year[5] = {0};
    char month[3] = {0};
    char day[3] = {0};
    int ret;
    size_t input_len;

    if (!input || !output || output_size == 0) {
        return -6;
    }

    input_len = strnlen(input, 11);
    if (input_len == 0 || input_len > 10) {
        return -7;
    }

    ret = validate_and_extract(input, year, sizeof(year), month, sizeof(month), day, sizeof(day));
    if (ret != 0) {
        return ret;
    }

    if (output_size < 11) {
        return -5;
    }

    snprintf(output, output_size, "%s-%s-%s", day, month, year);
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